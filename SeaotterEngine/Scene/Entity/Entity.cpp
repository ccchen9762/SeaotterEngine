#include "Entity.h"

#include "SeaotterEngine/Game/Game.h"

Entity::Entity(const Game& parentGame, DirectX::XMFLOAT3 translation, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 revolution,
	DirectX::XMFLOAT3 scale, size_t indicesSize) :
	m_parentGame(parentGame),
	m_translation(translation),
	m_rotation(rotation),
	m_revolution(revolution),
	m_scale(scale),
	m_indicesSize(indicesSize) {
}

void Entity::Update(double deltaTime) {
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

	return DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z) *
		DirectX::XMMatrixTranslation(m_translation.x, m_translation.y, m_translation.z);
}

const DirectX::XMMATRIX& Entity::GetViewProjectionMatrix() const {
	return m_parentGame.GetViewProjectionMatrix();
}
