#include <wrl.h>


namespace Engine {
	class ComputeRootSignature : public Microsoft::WRL::ComPtr<ID3D12RootSignature>
	{

	public:
		ComputeRootSignature() = default;
		~ComputeRootSignature();


		void Initialize(ID3D12Device* pDevice);

		void Release();
	};
}



