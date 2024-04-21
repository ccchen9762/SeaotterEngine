#include "ConstantBuffer.h"

#include "SeaotterEngine/Entity/Entity.h"
#include "SeaotterEngine/Common/constant.h"

ConstantBufferXForm::ConstantBufferXForm(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Entity& parentEntity)
	: m_parentEntity(parentEntity) {

	// in Left Hand System (LH) Z axis direction is away from screen, RH toward screen
	// also matrix in shader code is default column major, need transpose
	// transpose on CPU side is faster than on GPU side

	const XFormBuffer xFormBuffer = {
		DirectX::XMMatrixTranspose(m_parentEntity.GetTransformMatrix()),
		DirectX::XMMatrixTranspose(m_parentEntity.GetTransformMatrix() * m_parentEntity.GetViewProjectionMatrix())
	};

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(xFormBuffer); // return total array size in bytes
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;	// to be able to update every frame
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // cpu need permission to update buffer
	constantBufferDesc.MiscFlags = 0u;
	constantBufferDesc.StructureByteStride = 0u; // only 1 element
	
	D3D11_SUBRESOURCE_DATA constantSubResourceData = {};
	constantSubResourceData.pSysMem = &xFormBuffer;

	DX::ThrowIfFailed(device->CreateBuffer(&constantBufferDesc, &constantSubResourceData, &m_pConstantBuffer));
}

void ConstantBufferXForm::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
	Update(deviceContext);
	deviceContext->VSSetConstantBuffers(0u, 1u, m_pConstantBuffer.GetAddressOf());
}

void ConstantBufferXForm::Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
	const XFormBuffer xFormBuffer = {
		DirectX::XMMatrixTranspose(m_parentEntity.GetTransformMatrix()),
		DirectX::XMMatrixTranspose(m_parentEntity.GetTransformMatrix() * m_parentEntity.GetViewProjectionMatrix())
	};

	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	deviceContext->Map(m_pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedSubResource);
	memcpy(mappedSubResource.pData, &xFormBuffer, sizeof(xFormBuffer));
	deviceContext->Unmap(m_pConstantBuffer.Get(), 0u);
}

// ========== ConstantBuffer ==========

ConstantBuffer::ConstantBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const void* bufferData, size_t bufferSize, Type type)
	: m_slot(static_cast<int>(type)) {

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = static_cast<UINT>(bufferSize); // return total array size in bytes
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;	// to be able to update every frame
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // cpu need permission to update buffer
	constantBufferDesc.MiscFlags = 0u;
	constantBufferDesc.StructureByteStride = 0u; // only single element

	D3D11_SUBRESOURCE_DATA constantSubResourceData = {};
	constantSubResourceData.pSysMem = bufferData;

	DX::ThrowIfFailed(device->CreateBuffer(&constantBufferDesc, &constantSubResourceData, &m_pConstantBuffer));
}

void ConstantBuffer::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {

	assert("Use ConstantBufferXForm for transformation" && m_slot != 0);

	// default bind to both shader for now
	deviceContext->VSSetConstantBuffers(m_slot, 1u, m_pConstantBuffer.GetAddressOf());
	deviceContext->PSSetConstantBuffers(m_slot, 1u, m_pConstantBuffer.GetAddressOf());
}

void ConstantBuffer::Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext, const void* bufferData, size_t bufferSize) const {
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	DX::ThrowIfFailed(deviceContext->Map(m_pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedSubResource));
	memcpy(mappedSubResource.pData, bufferData, bufferSize);
	deviceContext->Unmap(m_pConstantBuffer.Get(), 0u);
}