#include "Batumo.h"

#include "Plataform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Batumo::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f/ 720.0f, 45.0f){
		
		m_VertexArray.reset(Batumo::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.2f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.2f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Batumo::Ref<Batumo::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Batumo::VertexBuffer::Create(vertices, sizeof(vertices)));
		Batumo::BufferLayout layout = {
			{ Batumo::ShaderDataType::Float3, "a_Position" },
			{ Batumo::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		Batumo::Ref<Batumo::IndexBuffer> indexBuffer;
		indexBuffer.reset(Batumo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_SquareVA.reset(Batumo::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Batumo::Ref<Batumo::VertexBuffer> squareVB;
		squareVB.reset(Batumo::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Batumo::ShaderDataType::Float3, "a_Position" },
			{ Batumo::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Batumo::Ref<Batumo::IndexBuffer> squareIB;
		squareIB.reset(Batumo::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_Transform;
			uniform mat4 u_Model;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_Transform * u_Model * vec4(a_Position, 1.0f);

			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.6, 1.0f);
				color = v_Color;
			}
		)";

		m_Shader = Batumo::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_Transform;
			uniform mat4 u_Model;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_Transform * u_Model * vec4(a_Position, 1.0f);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader = Batumo::Shader::Create("blueShader", blueShaderVertexSrc, blueShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Batumo::Texture2D::Create("assets/textures/Grama.png");
		m_Shrek = Batumo::Texture2D::Create("assets/textures/Shrek.png");

		std::dynamic_pointer_cast<Batumo::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Batumo::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

		Batumo::Input::DisableMouse();
	}

	void OnUpdate(Batumo::DeltaTime dt) override {
		m_CameraController.OnUpdate(dt);

		Batumo::RenderCommand::SetClearColor({ 0.3,0.2,0.5,1.0 });
		Batumo::RenderCommand::Clear();

		Batumo::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.1f*(x+y));
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Batumo::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		Batumo::Renderer::Submit(m_Shader, m_VertexArray);
		m_Texture->Bind();
		Batumo::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_Shrek->Bind();
		Batumo::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Batumo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override{
	}

	void OnEvent(Batumo::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	Batumo::PerspectiveCameraController m_CameraController;

	Batumo::ShaderLibrary m_ShaderLibrary;
	Batumo::Ref<Batumo::Shader> m_Shader;
	Batumo::Ref<Batumo::VertexArray> m_VertexArray;

	Batumo::Ref<Batumo::Shader> m_BlueShader;
	Batumo::Ref<Batumo::VertexArray> m_SquareVA;

	Batumo::Ref<Batumo::Texture2D> m_Texture, m_Shrek;

};

class SandBox : public Batumo::Application {
public:
	SandBox() {
		PushLayer(new ExampleLayer());
	}
	~SandBox() {

	}

};

Batumo::Application* Batumo::CreateApplication() {
	return new SandBox();
}

