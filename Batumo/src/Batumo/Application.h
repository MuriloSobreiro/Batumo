#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Batumo/Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

#include "Batumo/Core/DeltaTime.h"

#include "Window.h"
#include "Batumo/LayerStack.h"

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
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runnig = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	};

	Application* CreateApplication();

}
