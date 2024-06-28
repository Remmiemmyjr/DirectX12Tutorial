#include "pch.h"
#include "ComputeRootSignature.h"


namespace Engine {

	ComputeRootSignature::~ComputeRootSignature()
	{
		Release();
	}
	void ComputeRootSignature::Initialize(ID3D12Device* pDevice)
	{
		D3D12_ROOT_PARAMETER crParameter[4];

		// compute input (SRV)
		crParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
		crParameter[0].Descriptor.ShaderRegister = 0;
		crParameter[0].Descriptor.RegisterSpace = 0;
		crParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		// compute output (UAV)
		crParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV;
		crParameter[1].Descriptor.ShaderRegister = 1;
		crParameter[1].Descriptor.RegisterSpace = 0;
		crParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	


		D3D12_VERSIONED_ROOT_SIGNATURE_DESC crsDesc = { };
		crsDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_0;
		crsDesc.Desc_1_0.pParameters = crParameter;
		crsDesc.Desc_1_0.NumParameters = 2;
		crsDesc.Desc_1_0.NumStaticSamplers = 0;
		crsDesc.Desc_1_0.pStaticSamplers = 0;
		crsDesc.Desc_1_0.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;

		ID3DBlob* pSerializedRS = nullptr;
		ID3DBlob* pErrorBlob = nullptr;

		YT_EVAL_HR(D3D12SerializeVersionedRootSignature(&crsDesc, &pSerializedRS, &pErrorBlob), "Error serializing the compute root-signature");

		if (pErrorBlob) {

			PRINT_N("Compute root-signature serialization error: " << (const char*)pErrorBlob->GetBufferPointer());
		}

		YT_EVAL_HR(pDevice->CreateRootSignature(0, pSerializedRS->GetBufferPointer(), pSerializedRS->GetBufferSize(), IID_PPV_ARGS(GetAddressOf())), "Error creating the compute root-signature");
	}

	void ComputeRootSignature::Release()
	{
		if (Get()) {

			Reset();
		}
	}
}
