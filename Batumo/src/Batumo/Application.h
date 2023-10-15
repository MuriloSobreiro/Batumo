#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Batumo/Events/ApplicationEvent.h"

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

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Runnig = true;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();

}
