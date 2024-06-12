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

		// Buffer Uploader
		mBufferUploader.Initialize(mDevice.Get(), KBs(64));

		// Dynamic Vertex Buffer
		mVertexBuffer.Initialize(mDevice.Get(), KBs(8), D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_COMMON);
		mVertexBuffer.Get()->SetName(L"Vertex buffer");

#define G_BOX_VERTS 24
		// CUBE | VBO ****************************************************
		std::vector<Vertex> vertices;
		Vertex verticesBox[G_BOX_VERTS];
		verticesBox[0].position = { -1, 1, 1 };
		verticesBox[0].normal = { 0, 1, 0 };

		verticesBox[1].position = { -1, 1, -1 };
		verticesBox[1].normal = { 0, 1, 0 };

		verticesBox[2].position = { 1, 1, 1 };
		verticesBox[2].normal = { 0, 1, 0 };



		verticesBox[3].position = { -1, -1, -1 };
		verticesBox[3].normal = { 0, 0, -1 };

		verticesBox[4].position = { 1, -1, -1 };
		verticesBox[4].normal = { 0, 0, -1 };

		verticesBox[5].position = { -1, 1, -1 };
		verticesBox[5].normal = { 0, 0, -1 };



		verticesBox[6].position = { 1, -1, -1 };
		verticesBox[6].normal = { 1, 0, 0 };

		verticesBox[7].position = { 1, -1, 1 };
		verticesBox[7].normal = { 1, 0, 0 };

		verticesBox[8].position = { 1, 1, -1 };
		verticesBox[8].normal = { 1, 0, 0 };



		verticesBox[9].position = { 1, -1, 1 };
		verticesBox[9].normal = { 0, -1, 0 };

		verticesBox[10].position = { 1, -1, -1 };
		verticesBox[10].normal = { 0, -1, 0 };

		verticesBox[11].position = { -1, -1, 1 };
		verticesBox[11].normal = { 0, -1, 0 };



		verticesBox[12].position = { -1, -1, 1 };
		verticesBox[12].normal = { -1, 0, 0 };

		verticesBox[13].position = { -1, -1, -1 };
		verticesBox[13].normal = { -1, 0, 0 };

		verticesBox[14].position = { -1, 1, 1 };
		verticesBox[14].normal = { -1, 0, 0 };



		verticesBox[15].position = { 1, -1, 1 };
		verticesBox[15].normal = { 0, 0, 1 };

		verticesBox[16].position = { -1, -1, 1 };
		verticesBox[16].normal = { 0, 0, 1 };

		verticesBox[17].position = { 1, 1, 1 };
		verticesBox[17].normal = { 0, 0, 1 };



		// NEW VERTICES:
		verticesBox[18].position = { 1, 1, -1 };
		verticesBox[18].normal = { 0, 1, 0 };

		verticesBox[19].position = { 1, 1, -1 };
		verticesBox[19].normal = { 0, 0, -1 };

		verticesBox[20].position = { 1, 1, 1 };
		verticesBox[20].normal = { 1, 0, 0 };

		verticesBox[21].position = { -1, -1, -1 };
		verticesBox[21].normal = { 0, -1, 0 };

		verticesBox[22].position = { -1, 1, -1 };
		verticesBox[22].normal = { -1, 0, 0 };

		verticesBox[23].position = { -1, 1, 1 };
		verticesBox[23].normal = { 0, 0, -1 };



		// Test Buffer Uploader
		mBufferUploader.Upload((D12Resource*)mVertexBuffer.GetAddressOf(), verticesBox, sizeof(Vertex) * G_BOX_VERTS,
							   (D12CommandList*)mCommandList.GetAddressOf(), (D12CommandQueue*)mCommandQueue.GetAddressOf(), 
								D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);

		// Vertex Buffer Init
		//memcpy(mVertexBuffer.GetCPUMemory(), verticesBox, sizeof(Vertex) * G_BOX_VERTS);
		mVBView.BufferLocation = mVertexBuffer.Get()->GetGPUVirtualAddress();
		mVBView.StrideInBytes = sizeof(Vertex);
		mVBView.SizeInBytes = KBs(8);
		// ***************************************************************
		


#define G_INDICES 39
		// INDEX BUFFER **************************************************
		UINT32 indices[G_INDICES];
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 3;
		indices[4] = 4;
		indices[5] = 5;

		indices[6] = 6;
		indices[7] = 7;
		indices[8] = 8;

		indices[9] = 9;
		indices[10] = 10;
		indices[11] = 11;

		indices[12] = 12;
		indices[13] = 13;
		indices[14] = 14;

		indices[15] = 15;
		indices[16] = 16;
		indices[17] = 17;

		indices[18] = 1;
		indices[19] = 18;
		indices[20] = 2;

		indices[21] = 4;
		indices[22] = 19;
		indices[23] = 5;

		indices[24] = 7;
		indices[25] = 20;
		indices[26] = 8;

		indices[27] = 10;
		indices[28] = 21;
		indices[29] = 11;

		indices[30] = 13;
		indices[31] = 22;
		indices[32] = 14;

		indices[33] = 16;
		indices[34] = 23;
		indices[35] = 17;

		indices[36] = 4;
		indices[37] = 0;
		indices[38] = 1;


		// Index Buffer Init
		mIndexBuffer.Initialize(mDevice.Get(), KBs(16), D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_COMMON);
		mIndexBuffer->SetName(L"Index Buffer");
		
		mBufferUploader.Upload((D12Resource*)mIndexBuffer.GetAddressOf(), indices, sizeof(UINT32)* G_INDICES,
			(D12CommandList*)mCommandList.GetAddressOf(), (D12CommandQueue*)mCommandQueue.GetAddressOf(),
			D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
		
		mIBView.BufferLocation = mIndexBuffer.Get()->GetGPUVirtualAddress();
		mIBView.Format = DXGI_FORMAT_R32_UINT;
		mIBView.SizeInBytes = KBs(16);

		// ***************************************************************

		mBasePipeline.Initialize(mDevice.Get());

		mDepthBuffer.InitializeAsDepthBuffer(mDevice.Get(), mWidth, mHeight);

		mDepthDescHeap.InitializeDepthHeap(mDevice.Get());

		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
		mDevice->CreateDepthStencilView(mDepthBuffer.Get(), &dsvDesc, mDepthDescHeap.Get()->GetCPUDescriptorHandleForHeapStart());

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


		// View Proj Matrix                                       // CAMERA
		DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH({ 2.f,2.f,-3.f,0.f }, { 0.f,0.f,0.f,0.f }, { 0.f,1.f,0.f,0.f });
		                                                                     // FOV         // Aspect //NP  // View Dist
		DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(1.2217304764f, 16.f/9.f, 1.f, 50.f);

		mViewProjectionMatrix = viewMatrix * projectionMatrix;


		// const buffer must always align to 255 bytes, must be multiples of this
		mCBPassData.Initialize(mDevice.Get(), Utils::CalculateConstantBufferAlignment(sizeof(PassData)), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);

		
		// Material Init
		mMaterialBuffer1.Initialize(mDevice.Get(), Utils::CalculateConstantBufferAlignment(sizeof(MaterialCelShader)), D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_COMMON);
		mMaterialBuffer1->SetName(L"Material Constant Buffer 1");

		MaterialCelShader material;
		material.diffuseAlbedo = { 1.f, 0.f, .2f, 1.f };

		mBufferUploader.Upload((D12Resource*)mMaterialBuffer1.GetAddressOf(), &material, sizeof(MaterialCelShader),
			(D12CommandList*)mCommandList.GetAddressOf(), (D12CommandQueue*)mCommandQueue.GetAddressOf(),
			D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);


		// Lights (overall directional light)
		mLights[0].direction = { 0.f, -1.f, 0.f };
		mLights[0].strength = 1.f;
	}

	void RenderAPI::UpdateDraw()
	{
		memcpy(mCBPassData.GetCPUMemory(), &mViewProjectionMatrix, sizeof(PassData::viewProj));
		memcpy((BYTE*)mCBPassData.GetCPUMemory() + sizeof(PassData::viewProj), &mLights[0], sizeof(Light));

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
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = mDepthDescHeap->GetCPUDescriptorHandleForHeapStart();

		mCommandList.GFXCmd()->ClearRenderTargetView(rtvHandle, clearColor, 0, 0);
		mCommandList.GFXCmd()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.f, 0, 0, 0);
		mCommandList.GFXCmd()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		mCommandList.GFXCmd()->RSSetViewports(1, &mViewport);
		mCommandList.GFXCmd()->RSSetScissorRects(1, &mSRRect);

		mCommandList.GFXCmd()->SetGraphicsRootSignature(mBasePipeline.GetRS());
		mCommandList.GFXCmd()->SetPipelineState(mBasePipeline.Get());
		mCommandList.GFXCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mCommandList.GFXCmd()->IASetVertexBuffers(0, 1, &mVBView);
		mCommandList.GFXCmd()->IASetIndexBuffer(&mIBView);

		mCommandList.GFXCmd()->SetGraphicsRootConstantBufferView(0, mCBPassData.Get()->GetGPUVirtualAddress());
		mCommandList.GFXCmd()->SetGraphicsRootConstantBufferView(1, mMaterialBuffer1.Get()->GetGPUVirtualAddress());

			
		// DRAWING STUFF HERE *******************************************************************
		//mCommandList.GFXCmd()->DrawInstanced(G_BOX_VERTS, 1, 0, 0);
		mCommandList.GFXCmd()->DrawIndexedInstanced(G_INDICES, 1, 0, 0, 0);
		
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
		mVertexBuffer.Release();

		mCommandQueue.FlushQueue();
	
		mSwapChain.Release();
		
		mCommandList.Release();

		mCommandQueue.Release();


		if (mDevice.Get()) {

			mDevice.Reset();

		}
	}

}