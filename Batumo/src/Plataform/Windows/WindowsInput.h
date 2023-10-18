#pragma once

#include "Batumo/Input.h"

namespace Batumo {
	class WindowsInput : public Input
	{
	protected:
		// Herdado por meio de Input
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

