#include "btpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Plataform/OpenGL/OpenGLVertexArray.h"
namespace Batumo {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    BT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}

		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
}