#include "PixelShader.h"

#include "SeaotterEngine/Common/readFile.h"

PixelShader::PixelShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const char* filename) {

    m_pixelShaderBlob = ReadCSO(filename);

    DX::ThrowIfFailed(device->CreatePixelShader(m_pixelShaderBlob.data(), m_pixelShaderBlob.size(),
        nullptr, m_pPixelShader.ReleaseAndGetAddressOf()));
}

void PixelShader::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
    deviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
}