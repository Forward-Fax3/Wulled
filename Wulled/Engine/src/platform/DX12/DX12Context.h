#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/graphics/GraphicsContext.h"
#include <stdint.h>

#include <Windows.h>


namespace WLD::Graphics::dx12
{
	class WLD_API DX12Context : public Renderer::GraphicsContext
	{
	public:
		DX12Context(HWND* windowHandle);

		virtual void Init() override;
		virtual void Shutdown() override {};
		virtual void SwapBuffers() override;
		virtual void OnWindowResize(uint32_t width, uint32_t height) override;
		virtual void makeCurrent() override {};

	private:
		HWND* m_WindowHandle;
	};
}
