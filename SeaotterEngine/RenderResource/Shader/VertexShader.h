#pragma once

#include <vector>

#include "SeaotterEngine/RenderResource/RenderResource.h"

class VertexShader : RenderResource {
public:
	VertexShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const char* filename);
	~VertexShader() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	std::vector<uint8_t> m_vertexShaderBlob;
};