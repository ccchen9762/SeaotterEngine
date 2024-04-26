#pragma once

#include "SeaotterEngine/Common/pch.h"
#include <d3d11.h>
#include <DirectXMath.h>

#include "SeaotterEngine/RenderResource/Buffer/ConstantBuffer.h"
#include "SeaotterEngine/Common/constant.h"

class Game;

class DirectionalLight {
	struct LightBuffer {
		DirectX::XMVECTOR direction[kMaxLight];
		DirectX::XMFLOAT4 ambient[kMaxLight];
		DirectX::XMFLOAT4 diffuse[kMaxLight];
		DirectX::XMFLOAT4 specular[kMaxLight];
		DirectX::XMFLOAT4 intensity[kMaxLight];
		unsigned int counter = 0u;
	};

public:
	DirectionalLight() : m_init(false) {}
	~DirectionalLight() = default;

	void AddLight(const Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
		const DirectX::XMVECTOR& direction, const DirectX::XMFLOAT4& ambient, const DirectX::XMFLOAT4& color);
	void Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext);

private:
	bool m_init;
	LightBuffer m_lightBuffer;
	std::unique_ptr<ConstantBuffer> m_directionalBuffer;
};