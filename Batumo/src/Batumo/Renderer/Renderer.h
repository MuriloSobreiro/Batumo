#pragma once

namespace Batumo{
	
	enum class RendererAPI {
		None = 0, OpenGL = 1, Vulkan = 2, DirectX = 3
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return m_RendererAPI; }
	private:
		static RendererAPI m_RendererAPI;
	};
}