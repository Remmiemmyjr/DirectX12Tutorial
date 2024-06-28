#pragma once
#include <wrl.h>

namespace Engine {
	class UAV : public Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>
	{
	public:
		UAV() = default;
		~UAV();

		void InitializeUAVResource(ID3D12Device* pDevice, ID3D12DescriptorHeap** uavHeap, ID3D12Resource** uavResource, UINT bufferElementCount);

		void Release();
	};
}