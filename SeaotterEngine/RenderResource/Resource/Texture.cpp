#include "Texture.h"

#include <directxtk/WICTextureLoader.h>

Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext,
    const wchar_t* path, Texture::Type slot)
    : m_slot(static_cast<unsigned int>(slot)) {

    if (path) {
        DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(
            device.Get(), deviceContext.Get(), path, nullptr, &m_pTexture));

        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC; // handle oblique surface better than D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.MaxAnisotropy = D3D11_MAX_MAXANISOTROPY; // max level, cost more GPU resource
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MinLOD = 0.0f;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

        DX::ThrowIfFailed(device->CreateSamplerState(&samplerDesc, m_pSampler.ReleaseAndGetAddressOf()));
    }
    else { // for model parts that don't have a specific texture
        m_pSampler = { nullptr };
        m_pTexture = { nullptr };
    }
}

void Texture::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
    deviceContext->PSSetSamplers(m_slot, 1u, m_pSampler.GetAddressOf());
    deviceContext->PSSetShaderResources(m_slot, 1u, m_pTexture.GetAddressOf());
}
