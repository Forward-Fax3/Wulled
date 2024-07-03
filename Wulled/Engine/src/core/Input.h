#pragma once
#include "Engine/src/core/EngineCore.h"


namespace WLD
{
	class WLD_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMousButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<int32_t, int32_t> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static double GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static double GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		 
		virtual bool IsMouseButtonPressedImpl(int buuton) = 0;
		virtual std::pair<int32_t, int32_t> GetMousePositionImpl() = 0;
		virtual double GetMouseXImpl() = 0;
		virtual double GetMouseYImpl() = 0;

	private:
		static std::unique_ptr<Input> s_Instance;
	};
}