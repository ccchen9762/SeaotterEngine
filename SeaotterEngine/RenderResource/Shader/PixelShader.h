#pragma once

#include <vector>

#include "SeaotterEngine/RenderResource/RenderResource.h"

class PixelShader : public RenderResource {
public:
	PixelShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const wchar_t* filename);
	~PixelShader() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	std::vector<uint8_t> m_pixelShaderBlob;
};