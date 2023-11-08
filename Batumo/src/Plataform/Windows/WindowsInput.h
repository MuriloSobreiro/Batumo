#pragma once

#include "Batumo/Core/Input.h"

namespace Batumo {
	class WindowsInput : public Input
	{
	protected:
		// Herdado por meio de Input
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButonPressedImpl(int button) override;

		virtual bool DisableMouseImpl() override;
		virtual bool EnableMouseImpl() override;
		
		virtual std::pair<float, float> GetMouseDeltaImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

