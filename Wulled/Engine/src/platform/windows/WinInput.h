#pragma once

#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/Core/Input.h"

namespace WLD
{
	class WLD_API WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<int32_t, int32_t> GetMousePositionImpl() override;
		virtual double GetMouseXImpl() override;
		virtual double GetMouseYImpl() override;
	};
}