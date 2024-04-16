#pragma once

#include "SeaotterEngine/Common/pch.h"
#include <d3d11.h>

class RenderResource
{
public:
	RenderResource() = default;
	virtual ~RenderResource() = default; // make sure derived class destructors are called properly

	virtual void Bind(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) const = 0;
};