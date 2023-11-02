#include "btpch.h"
#include "Renderer.h"


namespace Batumo{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 model)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_Transform", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Model", model);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}