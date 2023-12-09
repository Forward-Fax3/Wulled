#include "wldpch.h"
#include "log.h"

#include "DX12/Context.h"

#include "d3d12.h"
#include "dxgi1_6.h"


namespace WLD::Graphics::dx12
{
	DX12Context::DX12Context(HWND* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		WLD_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void DX12Context::CreateDevice()
	{
		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC1 sd;
		{
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = s_NumBackBuffers;
			sd.Width = 0;
			sd.Height = 0;
			sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			sd.Scaling = DXGI_SCALING_STRETCH;
			sd.Stereo = FALSE;
		}

		// [DEBUG] Enable debug interface
#ifdef DX12_ENABLE_DEBUG_LAYER
		ID3D12Debug* pdx12Debug = nullptr;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pdx12Debug))))
			pdx12Debug->EnableDebugLayer();
#endif

		// Create device
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_2;
		WLD_CORE_ASSERT(!D3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(&m_pd3dDevice)), "Failed to create device!");

		// [DEBUG] Setup debug interface to break on any warnings/errors
#ifdef DX12_ENABLE_DEBUG_LAYER
		if (pdx12Debug != nullptr)
		{
			ID3D12InfoQueue* pInfoQueue = nullptr;
			m_pd3dDevice->QueryInterface(IID_PPV_ARGS(&pInfoQueue));
			pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
			pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
			pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
			pInfoQueue->Release();
			pdx12Debug->Release();
		}
#endif

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc = {};
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			desc.NumDescriptors = 3;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			desc.NodeMask = 1;
			WLD_CORE_ASSERT(!m_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pd3dRtvDescHeap)), "Failed to create descriptor heap!");

			SIZE_T rtvDescriptorSize = m_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_pd3dRtvDescHeap->GetCPUDescriptorHandleForHeapStart();
			for (UINT i = 0; i < s_NumBackBuffers; i++)
			{
				m_mainRenderTargetDescriptor[i] = rtvHandle;
				rtvHandle.ptr += rtvDescriptorSize;
			}
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc = {};
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			desc.NumDescriptors = 1;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			WLD_CORE_ASSERT(!m_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pd3dSrvDescHeap)), "Failed to create descriptor heap!");
		}

		{
			D3D12_COMMAND_QUEUE_DESC desc = {};
			desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			desc.NodeMask = 1;
			WLD_CORE_ASSERT(!m_pd3dDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_pd3dCommandQueue)), "Failed to create command queue!");
		}

		for (UINT i = 0; i < s_NumFramesInFlight; i++)
			WLD_CORE_ASSERT(!m_pd3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_frameContext[i].CommandAllocator)), "Failed to create command allocator {0}!", i + 1);

		WLD_CORE_ASSERT(!m_pd3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_frameContext[0].CommandAllocator, nullptr, IID_PPV_ARGS(&m_pd3dCommandList)) != S_OK ||
			m_pd3dCommandList->Close() != S_OK, "Failed to create command list!");

		WLD_CORE_ASSERT(!m_pd3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)), "Failed to create fence!");

		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		WLD_CORE_ASSERT(m_fenceEvent, "Failed to create fence event!");

		{
			IDXGIFactory4* dxgiFactory = nullptr;
			IDXGISwapChain1* swapChain1 = nullptr;
			WLD_CORE_ASSERT(!CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)), "Failed to create DXGI factory!");
			WLD_CORE_ASSERT(!dxgiFactory->CreateSwapChainForHwnd(m_pd3dCommandQueue, *m_WindowHandle, &sd, nullptr, nullptr, &swapChain1), "Failed to create swap chain!");
			WLD_CORE_ASSERT(!swapChain1->QueryInterface(IID_PPV_ARGS(&m_pSwapChain)), "Failed to query swap chain!");
			swapChain1->Release();
			dxgiFactory->Release();
			m_pSwapChain->SetMaximumFrameLatency(s_NumBackBuffers);
			m_hSwapChainWaitableObject = m_pSwapChain->GetFrameLatencyWaitableObject();
		}

		CreateRenderTarget();
	}

	void DX12Context::SwapBuffers()
	{
	}

	void DX12Context::OnWindowResize(uint32_t width, uint32_t height)
	{
	}

	void DX12Context::CreateRenderTarget()
	{
		for (UINT i = 0; i < s_NumBackBuffers; i++)
		{
			ID3D12Resource* pBackBuffer = nullptr;
			m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
			m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_mainRenderTargetDescriptor[i]);
			m_mainRenderTargetResource[i] = pBackBuffer;
		}
	}
}
