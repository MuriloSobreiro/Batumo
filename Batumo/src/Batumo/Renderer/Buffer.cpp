#include "btpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Plataform/OpenGL/OpenGLBuffer.h"

namespace Batumo {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}
		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BT_CORE_ASSERT(false, "RendererAPI::None is not suported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
