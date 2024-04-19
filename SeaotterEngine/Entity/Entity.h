#pragma once

#include <DirectXMath.h>
#include <vector>

#include "SeaotterEngine/RenderResource/RenderResource.h"

class Entity
{
public:
	Entity(DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 translation, DirectX::XMFLOAT3 revolution, DirectX::XMFLOAT3 scale,
		size_t indicesSize);
	virtual ~Entity() = default;

	virtual void Update();
	void Render(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext) const;

	DirectX::XMMATRIX GetTransformMatrix() const;

protected:
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_translation;
	DirectX::XMFLOAT3 m_revolution;
	DirectX::XMFLOAT3 m_scale;
	size_t m_indicesSize;

	std::vector<std::unique_ptr<RenderResource>> m_buffers;
	std::vector<std::unique_ptr<RenderResource>> m_renderResources;
};