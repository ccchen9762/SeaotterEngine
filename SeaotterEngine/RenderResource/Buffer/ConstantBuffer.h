#pragma once

#include "SeaotterEngine/RenderResource/RenderResource.h"

#include <DirectXMath.h>

class Entity;

class ConstantBufferXForm : public RenderResource
{
public:
	struct XFormBuffer {
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX modelViewProjection;
	};

public:
	ConstantBufferXForm(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Entity& parentEntity);
	~ConstantBufferXForm() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	void Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
	const Entity& m_parentEntity;
};

class ConstantBuffer : public RenderResource
{
public:
	enum class Type {
		Transformation = 0, Camera = 1, LightDirectional = 2, LightPoint = 3, Attributes = 4
	};

public:
	ConstantBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const void* bufferData, size_t bufferSize, Type type);
	~ConstantBuffer() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;
	void Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext, const void* bufferData, size_t bufferSize) const;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
	unsigned int m_slot;
};