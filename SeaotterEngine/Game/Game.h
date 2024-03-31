#pragma once

#include "SeaotterEngine/Window/Window.h"

class Game {
public:
	Game();
	~Game();

	int Start();

private:
	void Update();

private:
	Window m_window;
	bool m_isAlive;
};