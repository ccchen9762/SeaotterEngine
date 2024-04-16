#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::vector<unsigned short>& indices) {

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(unsigned short) * indices.size(); // return total array size in bytes
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indexSubResourceData = {};
	indexSubResourceData.pSysMem = indices.data();

	DX::ThrowIfFailed(device->CreateBuffer(&indexBufferDesc, &indexSubResourceData, &m_pIndexBuffer));
}

void IndexBuffer::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
	deviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}
