#pragma once
#include "Engine/src/core/EngineCore.h"


namespace WLD
{
	class WLD_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
