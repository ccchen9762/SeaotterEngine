#pragma once

#include "SeaotterEngine/RenderResource/Buffer/ConstantBuffer.h"

class Camera
{
private:
	struct CameraBuffer {
		DirectX::XMVECTOR position;
	};

public:
	Camera(const Microsoft::WRL::ComPtr<ID3D11Device>& device,
		const DirectX::XMVECTOR& position, const DirectX::XMVECTOR& orientation, const DirectX::XMVECTOR& up);
	~Camera() = default;

	// called every frame
	void Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext);

	void TranslateCamera(float translateX, float translateY);
	void TranslateCameraZ(int translateZ);
	void RotateCamera(float rotationY, float rotationX);
	void SetProjectionMatrix(float fov, float ratio, float nearZ, float farZ);

	const DirectX::XMMATRIX& GetViewMatrix() const { return m_viewMatrix; }
	const DirectX::XMMATRIX& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

private:
	void SetViewMatrix();

private:
	DirectX::XMVECTOR m_position;
	DirectX::XMVECTOR m_orientation;
	DirectX::XMVECTOR m_up;
	float m_speed;
	float m_angularSpeed;
	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;
	DirectX::XMMATRIX m_viewProjectionMatrix;
	std::unique_ptr<CameraBuffer> m_pCameraBuffer;
	ConstantBuffer m_constantBuffer;

	static int s_numCamera;
};