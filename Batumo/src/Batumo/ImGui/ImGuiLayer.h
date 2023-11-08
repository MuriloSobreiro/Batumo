#pragma once

#include "Batumo/Core/Layer.h"

#include "Batumo/Events/MouseEvent.h"
#include "Batumo/Events/KeyEvent.h"
#include "Batumo/Events/ApplicationEvent.h"

namespace Batumo {
	class ImGuiLayer: public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}



