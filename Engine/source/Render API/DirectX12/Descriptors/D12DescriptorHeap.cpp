#include "pch.h"
#include "D12DescriptorHeap.h"

namespace Engine {
	D12DescriptorHeap::~D12DescriptorHeap()
	{
		Release();
	}
	
	void D12DescriptorHeap::InitializeDepthHeap(ID3D12Device* pDevice)
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = 1;
		desc.NodeMask = 0;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

		YT_EVAL_HR(pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(GetAddressOf())), "Error creating descriptor heap");
	}

	void D12DescriptorHeap::InitializeTextureHeap(ID3D12Device* pDevice)
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = 10;
		desc.NodeMask = 0;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; //D3D12_DESCRIPTOR_HEAP_FLAG_NONE
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; //D3D12_DESCRIPTOR_HEAP_TYPE_DSV

		YT_EVAL_HR(pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(GetAddressOf())), "Error creating descriptor heap");
	}

	void D12DescriptorHeap::InitializeRTVHeap(ID3D12Device* pDevice)
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = 10;
		desc.NodeMask = 0;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; //D3D12_DESCRIPTOR_HEAP_FLAG_NONE
		desc.Type =D3D12_DESCRIPTOR_HEAP_TYPE_RTV; //D3D12_DESCRIPTOR_HEAP_TYPE_DSV

		YT_EVAL_HR(pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(GetAddressOf())), "Error creating descriptor heap");
	}

	void D12DescriptorHeap::Release()
	{
		if (Get())
		{
			Reset();
		}
	}
}