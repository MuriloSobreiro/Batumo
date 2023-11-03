#include "btpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Plataform/OpenGL/OpenGLShader.h"

namespace Batumo {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		
		}
		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}


