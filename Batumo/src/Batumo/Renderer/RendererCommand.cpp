#include "btpch.h"
#include "RendererCommand.h"

#include "Plataform/OpenGL/OpenGLRendererAPI.h"

namespace Batumo {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}