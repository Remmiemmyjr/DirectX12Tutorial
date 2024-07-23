#pragma once
#include "pch.h"


#include "RenderDataTypes.h"

#include "DirectX12/DXGI/DXGISwapChain.h"

#include "DirectX12/Base/D12Device.h"
#include "DirectX12/Commands/D12CommandQueue.h"
#include "DirectX12/Commands/D12CommandList.h"
#include "DirectX12/Resource/D12Resource.h"

#include "DirectX12/Pipeline/D12PipelineState.h"
#include "DirectX12/Pipeline/D12ComputePipeline.h"
#include "DirectX12/Descriptors/D12DescriptorHeap.h"
#include "DirectX12/MemoryManagement/BufferUploader.h"


namespace Engine {

	class YT_API RenderAPI
	{

	public: 
		RenderAPI() = default;
		~RenderAPI();

		void Initialize(HWND hwnd, const UINT width, const UINT height);

		void UpdateDraw();

		void Release();

	private:

		D12Device mDevice;
		D12CommandQueue mCommandQueue;
		D12CommandList mCommandList;


		DXGISwapChain mSwapChain;


		// Pipeline essentials ******************
		D12PipelineState mBasePipeline;
		D12ComputePipeline mComputePipeline;
		D12Resource mDepthBuffer;

		D3D12_VIEWPORT mViewport;
		D3D12_RECT mSRRect;

		D12DescriptorHeap mDepthDescHeap;
		D12DescriptorHeap mTexDescHeap;
		D12DescriptorHeap mRTVDescHeap;
		D12DescriptorHeap mSRVHeap;
		BufferUploader mBufferUploader;

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;
		// **************************************


		D12Resource mVertexBuffer;
		D12Resource mIndexBuffer;
		D12Resource mMaterialBuffer1;
		D12Resource mTexture;


		D3D12_VERTEX_BUFFER_VIEW mVBView;
		D3D12_INDEX_BUFFER_VIEW mIBView;

		std::vector<D12Resource> mMaterialBuffers;
		std::vector<D12Resource> mObjTransforms;

		D12Resource mCBPassData;
		Light mLights[8];


		DirectX::XMMATRIX mViewProjectionMatrix;


	private: 
		UINT mWidth = 0;
		UINT mHeight = 0;

	private: //temp testvars
		UINT mCurentidx = 0;
	};
}


