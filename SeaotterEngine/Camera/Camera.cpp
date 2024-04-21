#include "Camera.h"

#include <string>

#include "SeaotterEngine/Common/constant.h"

Camera::Camera(const Microsoft::WRL::ComPtr<ID3D11Device>& device,
	const DirectX::XMVECTOR& position, const DirectX::XMVECTOR& orientation, const DirectX::XMVECTOR& up) :
	m_position(position), m_orientation(orientation), m_up(up),
	m_viewMatrix(DirectX::XMMatrixLookToRH(m_position, m_orientation, m_up)),
	m_projectionMatrix(DirectX::XMMatrixPerspectiveFovRH(DirectX::XM_PIDIV4, kRenderRatio, kNearZ, kFarZ)),
	m_viewProjectionMatrix(m_viewMatrix * m_projectionMatrix),
	m_pCameraBuffer(std::make_unique<CameraBuffer>(position)),
	m_constantBuffer(device, m_pCameraBuffer.get(), sizeof(CameraBuffer), ConstantBuffer::Type::Camera),
	m_speed(0.02f), m_angularSpeed(0.1f) {
}

Camera::Camera(const Camera& copy) {
	m_position = copy.m_position;
	m_orientation = copy.m_orientation;
	m_up = copy.m_up;

	m_viewMatrix = copy.m_viewMatrix;
	m_projectionMatrix = copy.m_projectionMatrix;
	m_viewProjectionMatrix = copy.m_viewProjectionMatrix;

	m_pCameraBuffer = std::move(copy.m_pCameraBuffer);	// use pointer to fit in ConstantBuffer
	m_constantBuffer = copy.m_constantBuffer;

	m_speed = copy.m_speed;
	m_angularSpeed = copy.m_angularSpeed;
}

void Camera::Update(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& deviceContext) {
	// generate new viewProjectionMatrix
	SetViewMatrix();

	// update constant buffers
	m_pCameraBuffer->position = m_position;
	m_constantBuffer.Update(deviceContext, m_pCameraBuffer.get(), sizeof(CameraBuffer));

	m_constantBuffer.Bind(deviceContext);
}

void Camera::TranslateCamera(float translateX, float translateY) {
	m_position = DirectX::XMVectorAdd(m_position, DirectX::XMVectorScale(DirectX::XMVector3Cross(m_orientation, m_up), translateX * m_speed));
	m_position = DirectX::XMVectorSubtract(m_position, DirectX::XMVectorScale(m_up, translateY * m_speed));
}

void Camera::TranslateCameraZ(int translateZ) {
	m_position = DirectX::XMVectorAdd(m_position, DirectX::XMVectorScale(m_orientation, translateZ * m_speed));
}

void Camera::RotateCamera(float rotationY, float rotationX) {
	rotationX *= m_angularSpeed;
	rotationY *= m_angularSpeed;

	DirectX::XMVECTOR xAxis = DirectX::XMVector3Cross(m_orientation, m_up);
	DirectX::XMVector3Normalize(xAxis);

	m_orientation = DirectX::XMVector3Rotate(m_orientation, DirectX::XMQuaternionRotationAxis(xAxis, DirectX::XMConvertToRadians(rotationX)));
	m_orientation = DirectX::XMVector3Rotate(m_orientation, DirectX::XMQuaternionRotationAxis(m_up, DirectX::XMConvertToRadians(rotationY)));
}

void Camera::SetViewMatrix() {
	m_viewMatrix = DirectX::XMMatrixLookToRH(m_position, m_orientation, m_up);
	m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
}

void Camera::SetProjectionMatrix(float fov, float ratio, float nearZ, float farZ) {
	assert("near & far must be greater than 0" && nearZ > 0 && farZ > 0);
	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovRH(fov, ratio, nearZ, farZ);
	m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
}