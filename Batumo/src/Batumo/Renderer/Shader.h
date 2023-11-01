#pragma once

#include <string>

#include "Batumo/Renderer/Camera.h"

namespace Batumo{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();
		void UploadUniformMat4(std::string name, glm::mat4 matrix);

	private:
		uint32_t m_RendererID;
	};
}