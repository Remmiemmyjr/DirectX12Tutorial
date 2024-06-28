#pragma once
#include <wrl.h>

namespace Engine {
	class D12Resource : public Microsoft::WRL::ComPtr<ID3D12Resource>
	{

	public:
		D12Resource() = default;
		~D12Resource();
		void Initialize(ID3D12Device* pDevice, const unsigned int numBytes, D3D12_HEAP_TYPE heapType, D3D12_RESOURCE_STATES initialState);

		void InitializeAsDepthBuffer(ID3D12Device* pDevice, const unsigned int width, const unsigned int height);
		void InitializeAs2D(ID3D12Device* pDevice, const unsigned int width, const unsigned int height); // make sure its usabale as render target and an srv/texture 
		// use texture as render target for draw commands. 
		// create resource barrier command to convert this to read/write state. (first input for compute shader)
		// need UAV, similar to this 2d texture, set this as UAV
		// once youve run compute shader to write to uav, convert uav to read state (maybe). transition it to srv
		// copy into backbuffer

		void Release();
		void* GetCPUMemory();

	private:
		void* mMemory = nullptr; 
	};



}
