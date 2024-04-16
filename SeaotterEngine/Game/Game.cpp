#include "Game.h"

#include "SeaotterEngine/Common/common.h"

Game::Game() : m_window(kWindowClassName, kWindowTitle, kMainWindowWidth, kMainWindowHeight), m_isAlive(true) {
}

Game::~Game() {
}

int Game::Start() {

    // main message loop
    MSG msg = {};
    while (m_isAlive) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (m_window.m_keyboard.IsKeyPressed(VK_TAB)) {
                unsigned int result = MessageBox(nullptr, L"OK", L"OK", MB_OK);
                if (result == IDOK)
                    m_window.CaptureWindow();
            }

            while (!m_window.m_mouse.IsInputBufferEmpty()) {
                const Mouse::Input mouseInput = m_window.m_mouse.ReadFirstInput();

                static int test = 0;
                if (Mouse::Input::Type::Empty != mouseInput.GetType()) {
                    switch (mouseInput.GetType()) {
                    case Mouse::Input::Type::Leave:
                        m_window.SetWindowTitle(L"outside");
                        break;
                    case Mouse::Input::Type::WheelDown: {
                        --test;
                        const std::wstring title = std::to_wstring(test);
                        m_window.SetWindowTitle(title);
                        break;
                    }
                    case Mouse::Input::Type::WheelUp: {
                        ++test;
                        const std::wstring title = std::to_wstring(test);
                        m_window.SetWindowTitle(title);
                        break;
                    }
                    case Mouse::Input::Type::Move: {
                        Point2D position = mouseInput.GetPosition();
                        const std::wstring title = L"X: " + std::to_wstring(position.x) + L", Y: " + std::to_wstring(position.y);
                        m_window.SetWindowTitle(title);
                        break;
                    }
                    }
                }
            }

            if (WM_QUIT == msg.message)
                m_isAlive = false;
        }

        Update();
    }

    // cleanup and release component object model(COM) resourses
    CoUninitialize();

    return static_cast<int>(msg.wParam);
}

void Game::Update() {
    m_window.m_renderer.Update();
}