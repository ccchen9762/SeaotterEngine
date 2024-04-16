#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const void* verticesData,
    unsigned int offset, unsigned int stride, size_t size, Topology topology) 
    : m_offset(offset), m_stride(stride), m_topology(topology) {

    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.ByteWidth = stride * size; // return total array size in bytes
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0u;
    vertexBufferDesc.MiscFlags = 0u;
    vertexBufferDesc.StructureByteStride = m_stride;

    D3D11_SUBRESOURCE_DATA vertexSubResourceData = {};
    vertexSubResourceData.pSysMem = verticesData;

    DX::ThrowIfFailed(device->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, &m_pVertexBuffer));
}

void VertexBuffer::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
    deviceContext->IASetVertexBuffers(0u, 1u, m_pVertexBuffer.GetAddressOf(), &m_stride, &m_offset);

    switch (m_topology) {
    case VertexBuffer::Topology::Line: {
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        break;
    }
    case VertexBuffer::Topology::Triangle: {
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        break;
    }
    }
}