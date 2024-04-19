#pragma once

#include "SeaotterEngine/RenderResource/RenderResource.h"

#include <DirectXMath.h>
#include <vector>

class VertexBuffer : public RenderResource {
public:
	enum class Topology {
		Line = 0, Triangle = 1
	};

public:
	VertexBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const void* verticesData,
		unsigned int offset, unsigned int stride, size_t size, Topology topology = Topology::Triangle);
	~VertexBuffer() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
	unsigned int m_offset;
	unsigned int m_stride;
	Topology m_topology;
};

/* ========= vertex struct definition ========== */

struct VertexColored {
	DirectX::XMVECTOR position;
	DirectX::XMFLOAT4 color;
};

struct VertexTextured {
	DirectX::XMVECTOR position;
	DirectX::XMFLOAT2 texcoord;
};

struct VertexColoredShading {
	DirectX::XMVECTOR position;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT3 normal;
};

struct VertexTexturedShading {
	DirectX::XMVECTOR position;
	DirectX::XMFLOAT2 texcoord;
	DirectX::XMFLOAT3 normal;
};

struct VertexNormalMapping {
	DirectX::XMVECTOR position;
	DirectX::XMFLOAT2 texcoord;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 tangent;
	DirectX::XMFLOAT3 bitangent;
};