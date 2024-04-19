#pragma once

#include "SeaotterEngine/RenderResource/RenderResource.h"

#include <vector>

class Texture : public RenderResource {
public:
	enum class Type {
		Diffuse = 0, Specular = 1, Normal = 2, RenderTarget = 3
	};

public:
	Texture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext, 
		const wchar_t* path, Texture::Type type);
	~Texture() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSampler;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pTexture;
	unsigned int m_slot;
};