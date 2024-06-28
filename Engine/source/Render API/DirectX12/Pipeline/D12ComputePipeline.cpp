#include "pch.h"
#include "D12ComputePipeline.h"


namespace Engine {

	D12ComputePipeline::~D12ComputePipeline()
	{
		Release();
	}

	void D12ComputePipeline::Initialize(ID3D12Device* pDevice)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> computeShader;
		//D3DCompileFromFile(L"ComputeShader.hlsl", nullptr, nullptr, "main", "cs_5_1", 0, 0, &computeShader, nullptr);
		mShaders[0].Initialize(L"shaders/ComputeShader.hlsl", HLSLShader::ShaderType::COMPUTE);

		D3D12_COMPUTE_PIPELINE_STATE_DESC computeDesc;
		computeDesc.pRootSignature = mRootSignature.Get();
		computeDesc.CS = { mShaders[0].GetByteBlob()->GetBufferPointer(), mShaders[0].GetByteBlob()->GetBufferSize()};
		computeDesc.NodeMask = 0;
		computeDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

		YT_EVAL_HR(pDevice->CreateComputePipelineState(&computeDesc, IID_PPV_ARGS(GetAddressOf())), "Error creating the compute pipeline state object");
	}


	void D12ComputePipeline::Release()
	{
		mRootSignature.Release();
		mShaders[0].Release();

		if (Get()) {
			Reset();
		}
	}
}