#pragma once

#include "SeaotterEngine/RenderResource/RenderResource.h"

#include <vector>

class InputLayout : public RenderResource {
public:
	enum class LayoutType {
		Colored, Textured, ColoredShading, TexturedShading, NormalMapping
	};

public:
	InputLayout(const Microsoft::WRL::ComPtr<ID3D11Device>& device, std::vector<uint8_t> vertexShaderBlob, LayoutType type);
	~InputLayout() = default;

	void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const override;

private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
};