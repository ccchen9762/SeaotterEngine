#pragma once

#include "SeaotterEngine/WindowClass/WindowClass.h"

class Game {
public:
	Game();
	~Game();

	int start();

private:
	WindowClass m_wndClass;
	bool m_isAlive;
};