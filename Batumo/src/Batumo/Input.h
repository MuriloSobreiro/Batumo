#pragma once

#include "Batumo/Core.h"

namespace Batumo {
	class BATUMO_API Input {
	public:
		static bool IsKeyPressed(int keycode) { return s_instance->IsKeyPressedImpl(keycode); }
		
		static bool IsMouseButonPressed(int button) { return s_instance->IsMouseButonPressedImpl(button); }

		static bool DisableMouse() { return s_instance->DisableMouseImpl(); }
		static bool EnableMouse() { return s_instance->EnableMouseImpl(); }
		
		static std::pair<float, float> GetMouseDelta() { return s_instance->GetMouseDeltaImpl(); }
		static std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButonPressedImpl(int button) = 0;
		virtual bool DisableMouseImpl() = 0;
		virtual bool EnableMouseImpl() = 0;
		virtual std::pair<float, float> GetMouseDeltaImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		std::pair<double, double> m_CurrentMousePos;
		std::pair<double, double> m_LastMousePos;

	private:
		static Input* s_instance;
	};
}
