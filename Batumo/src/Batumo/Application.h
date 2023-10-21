#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Batumo/Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

#include "Window.h"
#include "Batumo/LayerStack.h"

#include "Batumo/Renderer/Shader.h"
#include "Batumo/Renderer/Buffer.h"
#include "Batumo/Renderer/VertexArray.h"

namespace Batumo {

	class BATUMO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		void OnEvent(Event& e);
		
	private:
		static Application* s_Instance;
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runnig = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	};

	Application* CreateApplication();

}
