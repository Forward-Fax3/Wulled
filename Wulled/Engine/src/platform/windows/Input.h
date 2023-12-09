#pragma once

#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Input.h"

namespace WLD
{
	class WLD_API WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<LONG, LONG> GetMousePositionImpl() override;
		virtual double GetMouseXImpl() override;
		virtual double GetMouseYImpl() override;
	};
}