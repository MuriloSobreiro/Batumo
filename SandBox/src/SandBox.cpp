#include "Batumo.h"

#include "Plataform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Batumo::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.0f, 1280, 720), m_CameraPosition(0,0,-3) {
		
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

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Batumo::Ref<Batumo::VertexBuffer> squareVB;
		squareVB.reset(Batumo::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Batumo::ShaderDataType::Float3, "a_Position" }
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

		m_Shader.reset(Batumo::Shader::Create(vertexSrc, fragmentSrc));

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

		m_BlueShader.reset(Batumo::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
		Batumo::Input::DisableMouse();
	}

	void OnUpdate(Batumo::DeltaTime dt) override {
		m_CameraPosition = { 0,0,0 };
		if (Batumo::Input::IsKeyPressed(BT_KEY_A))
			m_CameraPosition.x += m_CameraMoveSpeed * dt;
		if (Batumo::Input::IsKeyPressed(BT_KEY_D))
			m_CameraPosition.x -= m_CameraMoveSpeed * dt;
		if (Batumo::Input::IsKeyPressed(BT_KEY_W))
			m_CameraPosition.z += m_CameraMoveSpeed * dt;
		if (Batumo::Input::IsKeyPressed(BT_KEY_S))
			m_CameraPosition.z -= m_CameraMoveSpeed * dt;

		m_Camera.Move(m_CameraPosition);

		if (Batumo::Input::IsKeyPressed(BT_KEY_ESCAPE)) {
			if(m_Mouse)
				Batumo::Input::DisableMouse();
			else
				Batumo::Input::EnableMouse();
			m_Mouse = !m_Mouse;
		}
		if (!m_Mouse) {
			auto rotation = Batumo::Input::GetMouseDelta();
			m_Camera.RotateDegrees({ rotation.second * m_CameraRotationSpeed * dt, rotation.first * m_CameraRotationSpeed * dt, 0 });
		}

		

		Batumo::RenderCommand::SetClearColor({ 0.3,0.2,0.5,1.0 });
		Batumo::RenderCommand::Clear();

		Batumo::Renderer::BeginScene(m_Camera);

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

		Batumo::Renderer::Submit(m_Shader, m_VertexArray);

		Batumo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override{
	}

	void OnEvent(Batumo::Event& event) override {
	}

private:
	Batumo::PerspectiveCamera m_Camera;

	Batumo::Ref<Batumo::Shader> m_Shader;
	Batumo::Ref<Batumo::VertexArray> m_VertexArray;

	Batumo::Ref<Batumo::Shader> m_BlueShader;
	Batumo::Ref<Batumo::VertexArray> m_SquareVA;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 10.0f;
	float m_CameraRotationSpeed = 10.0f;
	bool m_Mouse = false;

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

