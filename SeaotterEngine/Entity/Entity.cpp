#include "Entity.h"

Entity::Entity(DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 translation, DirectX::XMFLOAT3 revolution, DirectX::XMFLOAT3 scale,
	size_t indicesSize) :
	m_rotation(rotation),
	m_translation(translation),
	m_revolution(revolution),
	m_scale(scale),
	m_indicesSize(indicesSize) {
}

void Entity::Update() {
	const float speed = 0.0003f;
	m_rotation.x += speed;
	m_rotation.y += speed;
	m_rotation.z += speed;
}

void Entity::Render(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext) const {
	// need to use reference for unique pointer
	for (const std::unique_ptr<RenderResource>& resource : m_buffers) {
		resource->Bind(pDeviceContext.Get());
	}

	for (const std::unique_ptr<RenderResource>& resource : m_renderResources) {
		resource->Bind(pDeviceContext.Get());
	}

	pDeviceContext->DrawIndexed(m_indicesSize, 0u, 0u); // draw with index buffer
}

DirectX::XMMATRIX Entity::GetTransformMatrix() const {

	return DirectX::XMMatrixRotationX(m_rotation.x) *
		DirectX::XMMatrixRotationY(m_rotation.y) *
		DirectX::XMMatrixRotationZ(m_rotation.z) *
		DirectX::XMMatrixTranslation(m_translation.x, m_translation.y, m_translation.z) *
		DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
}