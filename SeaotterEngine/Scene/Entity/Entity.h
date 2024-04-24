#pragma once

#include "SeaotterEngine/RenderResource/RenderResource.h"

#include <DirectXMath.h>
#include <vector>

class Game;

class Entity {
public:
	Entity(const Game& parentGame, DirectX::XMFLOAT3 translation, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 revolution,
		DirectX::XMFLOAT3 scale, size_t indicesSize);
	virtual ~Entity() = default;

	DirectX::XMMATRIX GetTransformMatrix() const;
	const DirectX::XMMATRIX& GetViewProjectionMatrix() const;

	virtual void Update(double deltaTime);
	void Render(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext) const;

	void Translate(DirectX::XMFLOAT3 translation) { m_translation = translation; }

protected:
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_translation;
	DirectX::XMFLOAT3 m_revolution;
	DirectX::XMFLOAT3 m_scale;
	size_t m_indicesSize;

	std::vector<std::unique_ptr<RenderResource>> m_renderResources;
	std::vector<std::unique_ptr<RenderResource>> m_buffers;

	const Game& m_parentGame;
};