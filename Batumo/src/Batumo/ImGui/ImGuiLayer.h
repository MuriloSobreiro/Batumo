#pragma once

#include "Batumo/Layer.h"

#include "Batumo/Events/MouseEvent.h"
#include "Batumo/Events/KeyEvent.h"
#include "Batumo/Events/ApplicationEvent.h"

namespace Batumo {
	class BATUMO_API ImGuiLayer: public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowsResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}


