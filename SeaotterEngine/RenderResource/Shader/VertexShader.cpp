#include "VertexShader.h"

#include "SeaotterEngine/Common/readFile.h"

VertexShader::VertexShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const char* filename) {

	m_vertexShaderBlob = ReadCSO(filename);

	DX::ThrowIfFailed(device->CreateVertexShader(m_vertexShaderBlob.data(), m_vertexShaderBlob.size(),
		nullptr, m_pVertexShader.ReleaseAndGetAddressOf()));
}

void VertexShader::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
	deviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
}
