#pragma once

#include "SeaotterEngine/RenderResource/Buffer/ConstantBuffer.h"

class Camera
{
public:
	struct CameraBuffer {
		DirectX::XMVECTOR position;
	};

public:
	Camera(const Microsoft::WRL::ComPtr<ID3D11Device>& device,
		const DirectX::XMVECTOR& position, const DirectX::XMVECTOR& orientation, const DirectX::XMVECTOR& up);
	~Camera() = default;

	Camera(Camera&& move) = default; // for in-place construct in vector

	// called every frame
	void Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext);

	void TranslateCamera(float translateX, float translateY);
	void TranslateCameraZ(int translateZ);
	void RotateCamera(float rotationY, float rotationX);
	
	const DirectX::XMMATRIX& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

	void SetProjectionMatrix(float fov, float ratio, float nearZ, float farZ);

private:
	void SetViewMatrix();

private:
	DirectX::XMVECTOR m_position;
	DirectX::XMVECTOR m_orientation;
	DirectX::XMVECTOR m_up;
	
	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;
	DirectX::XMMATRIX m_viewProjectionMatrix;
	
	CameraBuffer m_pCameraBuffer;
	ConstantBuffer m_constantBuffer;
	
	float m_speed, m_angularSpeed;
};