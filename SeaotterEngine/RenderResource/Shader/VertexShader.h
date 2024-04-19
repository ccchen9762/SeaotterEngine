#pragma once

#include <vector>

#include "SeaotterEngine/RenderResource/RenderResource.h"

class VertexShader : public RenderResource {
public:
	VertexShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const wchar_t* filename);
	~VertexShader() = default;

	const std::vector<uint8_t>& GetVertexShaderBlob() const { return m_vertexShaderBlob; }
	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	std::vector<uint8_t> m_vertexShaderBlob;
};