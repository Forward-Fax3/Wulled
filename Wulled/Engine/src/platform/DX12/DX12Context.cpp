#include "wldpch.h"
#include "log.h"

#include "DX12Context.h"

#include "d3d12.h"


namespace WLD::Graphics::dx12
{
	DX12Context::DX12Context(HWND* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		WLD_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void DX12Context::Init()
	{
	}

	void DX12Context::SwapBuffers()
	{
	}

	void DX12Context::OnWindowResize(uint32_t width, uint32_t height)
	{
	}
}
