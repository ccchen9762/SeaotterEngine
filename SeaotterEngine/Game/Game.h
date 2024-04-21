#pragma once

#include "SeaotterEngine/Window/Window.h"
#include "SeaotterEngine/Common/timer.h"
#include "SeaotterEngine/Camera/Camera.h"
#include "SeaotterEngine/Entity/Entity.h"
#include "SeaotterEngine/Imgui/ImguiHandler.h"

class Game {
public:
	Game();
	~Game();

	int Start();

	const DirectX::XMMATRIX& GetViewProjectionMatrix() const {
		assert("No camera in the list" && m_cameraList.size() > 0);
		return m_cameraList[m_mainCamera].GetViewProjectionMatrix(); 
	}

private:
	void KeyboardHandling(double deltaTime);
	void MouseHandling(double deltaTime);
	void Update(double deltaTime);

private:
	Window m_window;
	ImguiHandler m_imguiHandler;
	Renderer m_renderer;
	Timer m_timer;
	bool m_isAlive;

	std::vector<Camera> m_cameraList;
	unsigned int m_mainCamera;

	std::vector<std::unique_ptr<Entity>> m_debugList;
	std::vector<std::unique_ptr<Entity>> m_renderList;
};