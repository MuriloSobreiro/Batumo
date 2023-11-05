#include "btpch.h"
#include "Texture.h"

#include "Plataform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"

namespace Batumo {
	Ref<Texture2D> Texture2D::Create(const std::string& path, uint16_t type)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path, type);
		}
		return Ref<Texture2D>();
	}
}