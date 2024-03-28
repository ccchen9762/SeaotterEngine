#include "Game.h"

#include "SeaotterEngine/Common/common.h"

Game::Game() :
	m_wndClass(kWindowClassName, kWindowTitle, kMainWindowWidth, kMainWindowHeight), m_isAlive(true){
}

Game::~Game() {
}

int Game::start() {

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
