#pragma once

#include "SeaotterEngine/RenderResource/RenderResource.h"

#include <vector>

class IndexBuffer : public RenderResource {
public:
	IndexBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::vector<unsigned short>& indices);
	~IndexBuffer() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
};