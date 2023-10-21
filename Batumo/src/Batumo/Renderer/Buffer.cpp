#include "btpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Plataform/OpenGL/OpenGLBuffer.h"

namespace Batumo {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    BT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::Vulkan:  BT_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		case RendererAPI::DirectX: BT_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
		}
		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BT_CORE_ASSERT(false, "RendererAPI::None is not suported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		case RendererAPI::Vulkan: BT_CORE_ASSERT(false, "RendererAPI::Vulkan is not suported"); return nullptr;
		case RendererAPI::DirectX: BT_CORE_ASSERT(false, "RendererAPI::DirectX is not suported"); return nullptr;
		}
		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
