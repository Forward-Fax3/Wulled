#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/graphics/GraphicsContext.h"
#include <stdint.h>

#include <SDL.h>
#include "SDL_syswm.h"
#include <d3d12.h>
#include <dxgi1_6.h>


namespace WLD
{
	class WLD_API DX12Context : public GraphicsContext
	{
	public:
		DX12Context(WindowProps& props);
		~DX12Context();

		virtual void CreateDevice() override;
		virtual void Shutdown() override {};
		virtual void SwapBuffers() override;
		virtual void MakeCurrent() override {};
		virtual void SetVsync(const bool vsync) override {};
		virtual void ImGuiInit() override;
		virtual void ImGuiBegin() override;
		virtual void ImGuiEnd() override;
		virtual void ImGuiShutdown() override;
		virtual void Info() override {};

		virtual void OnWindowResize() override;

	private:
		void CreateRenderTarget();

	private:
		struct FrameContext
		{
			ID3D12CommandAllocator* CommandAllocator;
			UINT64                  FenceValue;
		};

		SDL_SysWMinfo m_wmInfo;

		static inline const int s_NumBackBuffers = 3;
		static inline const int s_NumFramesInFlight = 3;

		ID3D12Device* m_pd3dDevice;
		ID3D12DescriptorHeap* m_pd3dRtvDescHeap;
		ID3D12DescriptorHeap* m_pd3dSrvDescHeap;
		ID3D12CommandQueue* m_pd3dCommandQueue;
		ID3D12GraphicsCommandList* m_pd3dCommandList;
		ID3D12Fence* m_fence;
		HANDLE m_fenceEvent;
		IDXGISwapChain3* m_pSwapChain;
		HANDLE m_hSwapChainWaitableObject;
		D3D12_CPU_DESCRIPTOR_HANDLE  m_mainRenderTargetDescriptor[s_NumBackBuffers];
		ID3D12Resource* m_mainRenderTargetResource[s_NumBackBuffers];
		FrameContext m_frameContext[s_NumFramesInFlight];
	};
}
