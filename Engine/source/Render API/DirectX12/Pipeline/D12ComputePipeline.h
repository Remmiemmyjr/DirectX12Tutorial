#pragma once
#include <wrl.h>

#include "ComputeRootSignature.h"
#include "HLSLShader.h"

namespace Engine {
	class YT_API D12ComputePipeline : public Microsoft::WRL::ComPtr<ID3D12PipelineState>
	{
	public:
		D12ComputePipeline() = default;
		~D12ComputePipeline();

		void Initialize(ID3D12Device* pDevice);

		void Release();

		inline ID3D12RootSignature* GetRS() { return mRootSignature.Get(); }

	private:
		ComputeRootSignature mRootSignature;
		HLSLShader mShaders[1];
	};


}

