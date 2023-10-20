#pragma once

#include "Batumo/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Batumo {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		// Herdado por meio de GraphicsContext
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}