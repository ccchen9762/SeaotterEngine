#include "DirectionalLight.h"

#include "SeaotterEngine/Game/Game.h"

void DirectionalLight::AddLight(const Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, 
	const DirectX::XMVECTOR& direction, const const DirectX::XMFLOAT4& color) {

	if (!m_init) {
		m_init = true;
		m_directionalBuffer = std::make_unique<ConstantBuffer>(pDevice, &m_lightBuffer, sizeof(LightBuffer), ConstantBuffer::Type::DirectionalLight);
	}

	m_lightBuffer.direction[m_lightBuffer.counter] = DirectX::XMVector3Normalize(direction);
	m_lightBuffer.ambient[m_lightBuffer.counter] = color;
	m_lightBuffer.diffuse[m_lightBuffer.counter] = color;
	m_lightBuffer.specular[m_lightBuffer.counter] = color;
	m_lightBuffer.intensity[m_lightBuffer.counter] = 1.0f;

	++m_lightBuffer.counter;
}

void DirectionalLight::Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext) {
	m_directionalBuffer->Update(pDeviceContext, &m_lightBuffer, sizeof(LightBuffer));
	m_directionalBuffer->Bind(pDeviceContext);
}