#include "Game.h"

#include "SeaotterEngine/Common/constant.h"
#include "SeaotterEngine/Common/randomizer.h"
#include "SeaotterEngine/Entity/Debug/Cube.h"
#include "SeaotterEngine/Entity/Debug/Line.h"
#include "SeaotterEngine/Entity/Debug/Plane.h"

#include "SeaotterEngine/Imgui/Resource/imgui.h"
#include "SeaotterEngine/Imgui/Resource/imgui_impl_dx11.h"
#include "SeaotterEngine/Imgui/Resource/imgui_impl_win32.h"

Game::Game() : m_window(kWindowClassName, kWindowTitle, kMainWindowWidth, kMainWindowHeight), m_isAlive(true) {

    m_renderer.Init(m_window.GetHWnd(), kMainWindowWidth, kMainWindowHeight);

    ImGui_ImplWin32_Init(m_window.GetHWnd());
    ImGui_ImplDX11_Init(m_renderer.GetDevice().Get(), m_renderer.GetDeviceContext().Get());

    Randomizer::Init();

    m_cameraList.emplace_back(m_renderer.GetDevice(),
        DirectX::XMVectorSet(0.0f, 5.0f, 10.0f, 1.0f), DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
    m_mainCamera = 0;

    m_debugList.push_back(std::make_unique<Line>(
        *this,
        m_renderer.GetDevice(),
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f),
        DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
    ));
    m_debugList.push_back(std::make_unique<Line>(
        *this,
        m_renderer.GetDevice(),
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT3(0.0f, 0.0f, static_cast<float>(kPI / 2)),
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f),
        DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
    ));
    m_debugList.push_back(std::make_unique<Line>(
        *this,
        m_renderer.GetDevice(),
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT3(0.0f, static_cast<float>(-kPI / 2), 0.0f),
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f),
        DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
    ));

    for (int i = 0; i < 10; i++) {
        m_renderList.push_back(std::make_unique<Cube>(
            *this,
            m_renderer.GetDevice(),
            DirectX::XMFLOAT3(Randomizer::GetFloat(5.0f, -5.0f), Randomizer::GetFloat(10.0f, 0.0f), -20.0f),
            DirectX::XMFLOAT3(Randomizer::GetFloat(kPI), Randomizer::GetFloat(kPI), 0.0f),
            DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
            DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)
        ));
    }

    // floor
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_renderList.push_back(std::make_unique<Plane>(
                *this,
                m_renderer.GetDevice(),
                m_renderer.GetDeviceContext(),
                DirectX::XMFLOAT3(-14.0f + i * 4, 0.0f, -14.0f + j * 4),
                DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
                DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
                DirectX::XMFLOAT3(4.0f, 1.0f, 4.0f),
                L"Assets\\Texture\\wood.jpg"
            ));
        }
    }
}

Game::~Game() {
}

int Game::Start() {

    m_timer.Reset();

    // main message loop
    MSG msg = {};
    while (m_isAlive) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (WM_QUIT == msg.message)
                m_isAlive = false;
        }

        double deltaTime = m_timer.Update();
        KeyboardHandling(deltaTime);
        MouseHandling(deltaTime);
        Update(deltaTime);
    }

    // cleanup and release component object model(COM) resourses
    CoUninitialize();

    return static_cast<int>(msg.wParam);
}

void Game::Update(double deltaTime) {

    m_renderer.ClearBuffer(0.15f, 0.15f, 0.15f);

    m_cameraList[m_mainCamera].Update(m_renderer.GetDeviceContext());

    for (int i = 0; i < m_debugList.size(); i++) {
        m_debugList[i]->Update(deltaTime);
        m_debugList[i]->Render(m_renderer.GetDeviceContext());
    }

    for (int i = 0; i < m_renderList.size(); i++) {
        m_renderList[i]->Update(deltaTime);
        m_renderList[i]->Render(m_renderer.GetDeviceContext());
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (m_imguiHandler.GetShowWindow()) {
        ImGui::Begin("System Panel", &m_imguiHandler.GetShowWindow(), 0); // ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Spacing();
        //ImGui::Checkbox("Show Debug items", &game.showDebug);

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    m_renderer.Render();
}

void Game::KeyboardHandling(double deltaTime) {
    float speed = 3000.0f;

    if (m_window.m_keyboard.IsKeyPressed(VK_TAB)) {
        unsigned int result = MessageBox(nullptr, L"OK", L"OK", MB_OK);
        if (result == IDOK)
            m_window.CaptureWindow();
    }
    // W
    if (m_window.m_keyboard.IsKeyPressed(0x57)) {
        m_cameraList[m_mainCamera].TranslateCameraZ(deltaTime * speed);
    }
    // S
    if (m_window.m_keyboard.IsKeyPressed(0x53)) {
        m_cameraList[m_mainCamera].TranslateCameraZ(-deltaTime * speed);
    }
    // A
    if (m_window.m_keyboard.IsKeyPressed(0x41)) {
        m_cameraList[m_mainCamera].TranslateCamera(-deltaTime * speed, 0.0f);
    }
    // D
    if (m_window.m_keyboard.IsKeyPressed(0x44)) {
        m_cameraList[m_mainCamera].TranslateCamera(deltaTime * speed, 0.0f);
    }
    // space
    if (m_window.m_keyboard.IsKeyPressed(VK_SPACE)) {
        // minus goes up
        m_cameraList[m_mainCamera].TranslateCamera(0.0f, -deltaTime * speed);
    }
    // L Shift
    if (m_window.m_keyboard.IsKeyPressed(VK_CONTROL)) {
        m_cameraList[m_mainCamera].TranslateCamera(0.0f, deltaTime * speed);
    }
}

void Game::MouseHandling(double deltaTime) {
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

                static Point2D prevPosition = position;
                float translateX = position.x - prevPosition.x;
                float translateY = position.y - prevPosition.y;
                if (m_window.m_mouse.IsMButtonPressed()) {
                    m_cameraList[m_mainCamera].TranslateCamera(translateX, translateY);
                }
                if (m_window.m_mouse.IsRButtonPressed()) {
                    m_cameraList[m_mainCamera].RotateCamera(translateX, translateY);
                }
                prevPosition = position;

                break;
            }
            }
        }
    }
}
