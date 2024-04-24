#pragma once

#include "SeaotterEngine/Scene/Camera/Camera.h"
#include "SeaotterEngine/Scene/Light/DirectionalLight.h"
#include "SeaotterEngine/Scene/Light/PointLight.h"
#include "SeaotterEngine/Scene/Entity/Entity.h"

class Scene {
public:
	Scene();
	~Scene() = default;

private:
	std::vector<Camera> m_cameraList;
	unsigned int m_mainCamera;

	DirectionalLight m_directionalLights;
	PointLight m_pointLights;

	std::vector<std::unique_ptr<Entity>> m_debugList;
	std::vector<std::unique_ptr<Entity>> m_renderList;
};