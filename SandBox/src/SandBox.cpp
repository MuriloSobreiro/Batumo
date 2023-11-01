#include "Batumo.h"


class ExampleLayer : public Batumo::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.0f, 1280, 720), m_CameraPosition(0,0,-3), m_CameraRotation(0,0,0) {
		
		m_VertexArray.reset(Batumo::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.2f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.2f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Batumo::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Batumo::VertexBuffer::Create(vertices, sizeof(vertices)));
		Batumo::BufferLayout layout = {
			{ Batumo::ShaderDataType::Float3, "a_Position" },
			{ Batumo::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Batumo::IndexBuffer> indexBuffer;
		indexBuffer.reset(Batumo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_SquareVA.reset(Batumo::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Batumo::VertexBuffer> squareVB;
		squareVB.reset(Batumo::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Batumo::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Batumo::IndexBuffer> squareIB;
		squareIB.reset(Batumo::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = transform * vec4(a_Position, 1.0f);

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

		m_Shader.reset(new Batumo::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = transform * vec4(a_Position, 1.0f);
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

		m_BlueShader.reset(new Batumo::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override {
		if (Batumo::Input::IsKeyPressed(BT_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed;
		if (Batumo::Input::IsKeyPressed(BT_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		if (Batumo::Input::IsKeyPressed(BT_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		if (Batumo::Input::IsKeyPressed(BT_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		if(Batumo::Input::IsKeyPressed(BT_KEY_W))
			m_CameraRotation.x -= m_CameraRotationSpeed;
		if (Batumo::Input::IsKeyPressed(BT_KEY_S))
			m_CameraRotation.x += m_CameraRotationSpeed;
		if (Batumo::Input::IsKeyPressed(BT_KEY_A))
			m_CameraRotation.y += m_CameraRotationSpeed;
		if (Batumo::Input::IsKeyPressed(BT_KEY_D))
			m_CameraRotation.y -= m_CameraRotationSpeed;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Batumo::RenderCommand::SetClearColor({ 0.3,0.2,0.5,1.0 });
		Batumo::RenderCommand::Clear();

		Batumo::Renderer::BeginScene(m_Camera);

		Batumo::Renderer::Submit(m_BlueShader, m_SquareVA);
		Batumo::Renderer::Submit(m_Shader, m_VertexArray);

		Batumo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override{
	}

	void OnEvent(Batumo::Event& event) override {
	}

private:
	Batumo::PerspectiveCamera m_Camera;

	std::shared_ptr<Batumo::Shader> m_Shader;
	std::shared_ptr<Batumo::VertexArray> m_VertexArray;

	std::shared_ptr<Batumo::Shader> m_BlueShader;
	std::shared_ptr<Batumo::VertexArray> m_SquareVA;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	glm::vec3 m_CameraRotation;
	float m_CameraRotationSpeed = 1.0f;

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

