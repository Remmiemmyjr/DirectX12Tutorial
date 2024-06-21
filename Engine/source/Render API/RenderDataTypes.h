#pragma once
#include "pch.h"


namespace Engine {

	struct Light {
		DirectX::XMFLOAT3 position = { 0.f, 0.f, 0.f };
		float strength = 0.f;
		DirectX::XMFLOAT3 direction = { 0.f, 0.f, 0.f };
		float padding = 0.f;
	};

	namespace Render {

		struct Vertex {
			DirectX::XMFLOAT3 position = { 0.0f,0.0f,0.0f };
			DirectX::XMFLOAT3 normal = {0.0f,0.0f,0.0f};
			//DirectX::XMFLOAT4 color = { 0.0f,1.0f,0.0f,1.0f };
		};

		struct MaterialCelShader {
			DirectX::XMFLOAT4 diffuseAlbedo = { 0.0f,1.0f,0.0f,1.0f };
		};

		struct ObjectData {
			DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();
		};

		struct PassData {
			DirectX::XMMATRIX viewProj = DirectX::XMMatrixIdentity();
			Light sceneLight;
		};

	}

}