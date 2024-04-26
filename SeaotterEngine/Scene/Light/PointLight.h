#pragma once

#include "SeaotterEngine/Common/pch.h"
#include <d3d11.h>
#include <DirectXMath.h>

#include "SeaotterEngine/RenderResource/Buffer/ConstantBuffer.h"
#include "SeaotterEngine/Scene/Entity/Debug/Sphere.h"
#include "SeaotterEngine/Common/constant.h"

class Game;

class PointLight {
	struct LightBuffer {
		DirectX::XMVECTOR position[kMaxLight];
		DirectX::XMFLOAT4 ambient[kMaxLight];
		DirectX::XMFLOAT4 diffuse[kMaxLight];
		DirectX::XMFLOAT4 specular[kMaxLight];
		DirectX::XMFLOAT4 intensity[kMaxLight];
		unsigned int counter = 0u;
		float constant = 1.0f;
		float linear = 0.007f;
		float quadratic = 0.0002f;
	};

public:
	PointLight() : m_init(false), m_pointBuffer(nullptr) {}
	~PointLight() = default;

	void AddLight(const Game& game, const Microsoft::WRL::ComPtr<ID3D11Device>& device, const DirectX::XMVECTOR& position, 
		const DirectX::XMFLOAT4& ambient, const DirectX::XMFLOAT4& color);
	void Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext, double deltaTime);
	void Render(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext);

private:
	bool m_init;
	LightBuffer m_lightBuffer;
	std::unique_ptr<ConstantBuffer> m_pointBuffer;
	std::vector<std::unique_ptr<Sphere>> m_spheres;
};