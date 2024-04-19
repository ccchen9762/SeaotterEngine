#pragma once

#include "SeaotterEngine/Window/Window.h"
#include "SeaotterEngine/Entity/Entity.h"
#include "SeaotterEngine/Imgui/ImguiHandler.h"

class Game {
public:
	Game();
	~Game();

	int Start();

private:
	void Update();
	void KeyboardHandling();
	void MouseHandling();

private:
	Window m_window;
	ImguiHandler m_imguiHandler;
	Renderer m_renderer;
	
	bool m_isAlive;
	std::vector<std::unique_ptr<Entity>> m_renderList;
};