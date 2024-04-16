#pragma once

#include "SeaotterEngine/Common/pch.h"
#include <d3d11.h> // only declarations, need definitions in dlls 

class Renderer
{
	friend class Window;

public:
	Renderer();
	~Renderer() = default; // no need to call release for ComPtr

	void Update();
	void ClearBuffer(float red, float green, float blue);

private:
	void Init(HWND hWnd);
	const Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice() { return m_pDevice; }
	const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& GetDeviceConetxt() { return m_pDeviceContext; }

private:
	bool m_isInit;
	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
};