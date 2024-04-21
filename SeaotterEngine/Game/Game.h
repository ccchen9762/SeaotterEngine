#pragma once

#include "SeaotterEngine/Window/Window.h"
#include "SeaotterEngine/Camera/Camera.h"
#include "SeaotterEngine/Entity/Entity.h"
#include "SeaotterEngine/Imgui/ImguiHandler.h"

class Game {
public:
	Game();
	~Game();

	int Start();

	const DirectX::XMMATRIX& GetViewProjectionMatrix() const {
		assert(m_cameraList.size() > 0 && "No camera in the list");
		return m_cameraList[m_mainCamera].GetViewProjectionMatrix(); 
	}

private:
	void Update();
	void KeyboardHandling();
	void MouseHandling();

private:
	Window m_window;
	ImguiHandler m_imguiHandler;
	Renderer m_renderer;
	bool m_isAlive;

	std::vector<Camera> m_cameraList;
	unsigned int m_mainCamera;

	std::vector<std::unique_ptr<Entity>> m_renderList;
};