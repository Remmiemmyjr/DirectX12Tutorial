#include "pch.h"
#include "UAV.h"
#include <d3dx12.h>
#include <DirectXMath.h>
using namespace DirectX;

namespace Engine {
	UAV::~UAV()
	{
		Release();
	}

	void UAV::InitializeUAVResource(ID3D12Device* pDevice, ID3D12DescriptorHeap** uavHeap, ID3D12Resource** uavResource, UINT bufferElementCount)
	{
		D3D12_RESOURCE_DESC uavResourceDesc = {};
		uavResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		uavResourceDesc.Alignment = 0;
		uavResourceDesc.Width = bufferElementCount * sizeof(XMFLOAT4); // Adjust size accordingly
		uavResourceDesc.Height = 1;
		uavResourceDesc.DepthOrArraySize = 1;
		uavResourceDesc.MipLevels = 1;
		uavResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavResourceDesc.SampleDesc.Count = 1;
		uavResourceDesc.SampleDesc.Quality = 0;
		uavResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		uavResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;


		ID3D12Resource* uavResource;
		/*pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &uavResourceDesc,
										D3D12_RESOURCE_STATE_UNORDERED_ACCESS, nullptr, IID_PPV_ARGS(&uavResource));*/


		D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = bufferElementCount; // Adjust element count accordingly
		uavDesc.Buffer.StructureByteStride = 0;
		uavDesc.Buffer.CounterOffsetInBytes = 0;
		uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

		//CD3DX12_CPU_DESCRIPTOR_HANDLE uavHandle((*uavHeap)->GetCPUDescriptorHandleForHeapStart());
		//YT_EVAL_HR(pDevice->CreateUnorderedAccessView(*uavResourceDesc, nullptr, &uavDesc, IID_PPV_ARGS(GetAddressOf())), "Error creating descriptor heap");
	}

	void UAV::Release()
	{
		if (Get())
		{
			Reset();
		}
	}
}