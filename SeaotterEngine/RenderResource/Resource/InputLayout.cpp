#include "InputLayout.h"

// AlignedByteOffset can use D3D11_APPEND_ALIGNED_ELEMENT to automatically assign
// semantic should be named without number, e.g. no COLOR0
static const D3D11_INPUT_ELEMENT_DESC s_inputElementDescColored[] = {
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16u, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
};

static const D3D11_INPUT_ELEMENT_DESC s_inputElementDescTextured[] = {
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 16u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static const D3D11_INPUT_ELEMENT_DESC s_inputElementDescColoredShading[] = {
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 16u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 32u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static const D3D11_INPUT_ELEMENT_DESC s_inputElementDescTexturedShading[] = {
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 16u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 24u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static const D3D11_INPUT_ELEMENT_DESC s_inputElementDescNormalMapping[] = {
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 16u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 24u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		 1, DXGI_FORMAT_R32G32B32_FLOAT,	0, 36u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		 2, DXGI_FORMAT_R32G32B32_FLOAT,	0, 48u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

InputLayout::InputLayout(const Microsoft::WRL::ComPtr<ID3D11Device>& device, std::vector<uint8_t> vertexShaderBlob, LayoutType type) {
	switch (type) {
	case InputLayout::LayoutType::Colored: {
		DX::ThrowIfFailed(device->CreateInputLayout(s_inputElementDescColored, sizeof(s_inputElementDescColored) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			vertexShaderBlob.data(), vertexShaderBlob.size(), m_pInputLayout.ReleaseAndGetAddressOf()));
		break;
	}
	case InputLayout::LayoutType::Textured: {
		DX::ThrowIfFailed(device->CreateInputLayout(s_inputElementDescTextured, sizeof(s_inputElementDescTextured) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			vertexShaderBlob.data(), vertexShaderBlob.size(), m_pInputLayout.ReleaseAndGetAddressOf()));
		break;
	}
	case InputLayout::LayoutType::ColoredShading: {
		DX::ThrowIfFailed(device->CreateInputLayout(s_inputElementDescColoredShading, sizeof(s_inputElementDescColoredShading) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			vertexShaderBlob.data(), vertexShaderBlob.size(), m_pInputLayout.ReleaseAndGetAddressOf()));
		break;
	}
	case InputLayout::LayoutType::TexturedShading: {
		DX::ThrowIfFailed(device->CreateInputLayout(s_inputElementDescTexturedShading, sizeof(s_inputElementDescTexturedShading) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			vertexShaderBlob.data(), vertexShaderBlob.size(), m_pInputLayout.ReleaseAndGetAddressOf()));
		break;
	}
	case InputLayout::LayoutType::NormalMapping: {
		DX::ThrowIfFailed(device->CreateInputLayout(s_inputElementDescNormalMapping, sizeof(s_inputElementDescNormalMapping) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			vertexShaderBlob.data(), vertexShaderBlob.size(), m_pInputLayout.ReleaseAndGetAddressOf()));
		break;
	}
	}
}

void InputLayout::Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const {
	deviceContext->IASetInputLayout(m_pInputLayout.Get());
}
