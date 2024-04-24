#include "PointLight.h"

#include "SeaotterEngine/Game/Game.h"

void PointLight::AddLight(const Game& game, const Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
	const DirectX::XMVECTOR& position, const const DirectX::XMFLOAT4& color) {

	if (!m_init) {
		m_init = true;
		m_pointBuffer = std::make_unique<ConstantBuffer>(pDevice, &m_lightBuffer, sizeof(LightBuffer), ConstantBuffer::Type::PointLight);
	}

	m_lightBuffer.position[m_lightBuffer.counter] = position;
	m_lightBuffer.ambient[m_lightBuffer.counter] = color;
	m_lightBuffer.diffuse[m_lightBuffer.counter] = color;
	m_lightBuffer.specular[m_lightBuffer.counter] = color;
	m_lightBuffer.intensity[m_lightBuffer.counter] = 1.0f;

	++m_lightBuffer.counter;

	DirectX::XMFLOAT3 spherePosition;
	DirectX::XMStoreFloat3(&spherePosition, position);
	m_spheres.push_back(std::make_unique<Sphere>(game, pDevice, spherePosition, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(0.2f, 0.2f, 0.2f)));
}

void PointLight::Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext, double deltaTime) {
	m_pointBuffer->Update(pDeviceContext, &m_lightBuffer, sizeof(LightBuffer));
	m_pointBuffer->Bind(pDeviceContext);

	for (int i = 0; i < m_spheres.size(); i++) {
		DirectX::XMFLOAT3 spherePosition;
		DirectX::XMStoreFloat3(&spherePosition, m_lightBuffer.position[i]);
		m_spheres[i]->Translate(spherePosition);
		m_spheres[i]->Update(deltaTime);
	}
}

void PointLight::Render(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext) {
	for (int i = 0; i < m_spheres.size(); i++) {
		m_spheres[i]->Render(pDeviceContext);
	}
}
