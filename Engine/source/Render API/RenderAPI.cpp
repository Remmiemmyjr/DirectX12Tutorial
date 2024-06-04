#include "pch.h"
#include "RenderAPI.h"

#include <vector>

#include "DirectX12/DXGI/DXGIFactory.h"
#include "DirectX12/DXGI/DXGIAdapter.h"

#include "Utilities/Utilities.h"


//#include "DirectX12/Debug/D12Debug.h"





namespace Engine {
	using namespace Render;


	RenderAPI::~RenderAPI()
	{
		Release();
	}

	void RenderAPI::Initialize(HWND hwnd, const UINT width, const UINT height)
	{
		mWidth = width;
		mHeight = height;

		//this could be disabled during non-debug-builds
		//D12Debug::Get().Enable();

		DXGIFactory factory;
		DXGIAdapter adapter = factory.GetAdapter();

		/* CONSOLE OUTPUT FOR DEBUGGING */
		{
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);
			PRINT_W_N("Selected device " << desc.Description);
		}
		/* END DEBUGGING OUTPUT */

		// Device
		mDevice.Init(adapter.Get());
		mDevice->SetName(L"Main virtual device");

		// Command Queue
		mCommandQueue.Initialize(mDevice.Get());
		mCommandList.Initialize(mDevice.Get());

		// Swap Chain
		mSwapChain.Initialize(mDevice.Get(), factory.Get(), mCommandQueue.Get(), hwnd, mWidth, mHeight);

		// Dynamic Vertex Buffer
		mDynamicVertexBuffer.Initialize(mDevice.Get(), KBs(16), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
		mDynamicVertexBuffer.Get()->SetName(L"Dynamic vertex buffer");

		
		//RIGHT NOW FOR SCREEN SPACE COORDINATES VERTICES ONLY HAVE X AND Y mapped to (-1,1) -> (1,-1)

		// TRIANGLE ************************************************
		std::vector<Vertex> vertices;

		for (int i = 0; i < 3; i++) {
			Vertex vertexData;
			
			if (i == 0) 
			{
				vertexData.color = { 1.0f,.5f,0.0f,1.0f };
				vertexData.position = { -.35f,-.5f,0.0f };
			}
			else if (i == 1) 
			{
				vertexData.color = { 1.0f,0.3f,0.6f,1.0f };
				vertexData.position = { 0.0f,.5f,0.0f };
			} 
			else 
			{
				vertexData.color = { 0.5f,1.0f,1.0f,1.0f };
				vertexData.position = { .35f,-.5f,0.0f };
			}
			vertices.push_back(vertexData);
		}
		// *********************************************************

		//void* destination = nullptr;

		//mDynamicVertexBuffer->Map(0, 0, &destination);
		memcpy(mDynamicVertexBuffer.GetCPUMemory(), vertices.data(), sizeof(Vertex) * vertices.size());
		//mDynamicVertexBuffer->Unmap(0, 0);

		mDynamicVBView.BufferLocation = mDynamicVertexBuffer.Get()->GetGPUVirtualAddress();
		mDynamicVBView.StrideInBytes = sizeof(Vertex);
		mDynamicVBView.SizeInBytes = KBs(16);


		/*
		//ONLY CPU = default ram / cache
		//ONLY GPU = default heap on GPU (VRAM)
		//Shared CPU and GPU = with read/write for all - it's stored on the GPU
		//Readback memory on GPU (With Read from the CPU)
		*/

	
		mBasePipeline.Initialize(mDevice.Get());

		// Viewport param init
		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
		mViewport.Width = mWidth;
		mViewport.Height = mHeight;
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;

		// Scissor Rect param init
		mSRRect.left = 0;
		mSRRect.right = mViewport.Width;
		mSRRect.top = 0;
		mSRRect.bottom = mViewport.Height;


		// View Proj Matrix
		DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH({ 0.f,1.f,-3.f,0.f }, { 0.f,0.f,0.f,0.f }, { 0.f,1.f,0.f,0.f });
		                                                                     // FOV         // Aspect //NP  // View Dist
		DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(1.2217304764f, 16.f/9.f, 1.f, 50.f);

		mViewProjectionMatrix = viewMatrix * projectionMatrix;


		// const buffer must always align to 255 bytes, must be multiples of this
		mCBPassData.Initialize(mDevice.Get(), Utils::CalculateConstantBufferAlignment(sizeof(PassData)), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);


	}

	void RenderAPI::UpdateDraw()
	{
		memcpy(mCBPassData.GetCPUMemory(), &mViewProjectionMatrix, sizeof(PassData));

		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = mSwapChain.GetCurrentRenderTarget();
		barrier.Transition.Subresource = 0;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		mCommandList.GFXCmd()->ResourceBarrier(1, &barrier);

		const float clearColor[] = {  0.0f,0.0f,0.0f,1.0f };
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = mSwapChain.GetCurrentRTVHandle();
		mCommandList.GFXCmd()->ClearRenderTargetView(rtvHandle, clearColor, 0, 0);
		mCommandList.GFXCmd()->OMSetRenderTargets(1, &rtvHandle, false, 0);

		mCommandList.GFXCmd()->RSSetViewports(1, &mViewport);
		mCommandList.GFXCmd()->RSSetScissorRects(1, &mSRRect);

		mCommandList.GFXCmd()->SetGraphicsRootSignature(mBasePipeline.GetRS());
		mCommandList.GFXCmd()->SetPipelineState(mBasePipeline.Get());
		mCommandList.GFXCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mCommandList.GFXCmd()->IASetVertexBuffers(0, 1, &mDynamicVBView);

		mCommandList.GFXCmd()->SetGraphicsRootConstantBufferView(0, mCBPassData.Get()->GetGPUVirtualAddress());

			
		// DRAWING STUFF HERE *******************************************************************
		mCommandList.GFXCmd()->DrawInstanced(3, 1, 0, 0);
		
		
		// **************************************************************************************


		barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = mSwapChain.GetCurrentRenderTarget();
		barrier.Transition.Subresource = 0;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

		mCommandList.GFXCmd()->ResourceBarrier(1, &barrier);


		mCommandList.GFXCmd()->Close();
		mCommandQueue.M_ExecuteCommandList(mCommandList.Get());

		mSwapChain.Present();

		while (mCommandQueue.GetFence()->GetCompletedValue() < mCommandQueue.M_GetCurrentFenceValue()) {

			_mm_pause();
		}

		mCommandList.ResetCommandList();
	}

	void RenderAPI::Release()
	{
		mDynamicVertexBuffer.Release();

		mCommandQueue.FlushQueue();
	
		mSwapChain.Release();
		
		mCommandList.Release();

		mCommandQueue.Release();


		if (mDevice.Get()) {

			mDevice.Reset();

		}
	}

}