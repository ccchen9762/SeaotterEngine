#include "Window.h"

#include "SeaotterEngine/Imgui/Resource/imgui.h"
#include "SeaotterEngine/Imgui/Resource/imgui_impl_win32.h"

#include "SeaotterEngine/Common/math.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window(const wchar_t windowClassName[], const wchar_t windowTitle[], const unsigned int windowWidth, const unsigned int windowHeight) :
    m_hInstance(GetModuleHandle(nullptr)), m_windowClassName(windowClassName), m_windowTitle(windowTitle), 
    m_windowWidth(windowWidth), m_windowHeight(windowHeight) {

    // register window class
    WNDCLASSEX wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX); // structure size
    wcex.style = CS_OWNDC; // allow rendering multiple windows independently (unique device context for each window)
    wcex.lpfnWndProc = PreWndProc; // pointer to awindow procedure
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(nullptr); // retrieve current executable module 
    wcex.hIcon = nullptr;
    wcex.hCursor = nullptr;
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = windowClassName;
    wcex.hIconSm = nullptr;

    RegisterClassEx(&wcex);

    // adjust client space
    RECT clientSpace = {};
    clientSpace.left = 0;
    clientSpace.right = windowWidth;
    clientSpace.top = 0;
    clientSpace.bottom = windowHeight;
    AdjustWindowRectEx(&clientSpace, WS_OVERLAPPEDWINDOW, false, 0);

    // create window instance
    m_hWnd = CreateWindowEx( 0,
        windowClassName, windowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, // initial position 
        clientSpace.right - clientSpace.left, clientSpace.bottom - clientSpace.top, // size
        nullptr, // parent window
        nullptr, // menu
        GetModuleHandle(nullptr), 
        this // additional application data, point to this to get it return from WM_NCCREATE
    );

    ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window() {
    UnregisterClass(m_windowClassName.c_str(), m_hInstance);
    DestroyWindow(m_hWnd);
}

LRESULT CALLBACK Window::PreWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // the very first message associate with window
    if (WM_NCCREATE == msg) {
        CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        // get this Window instance pointer from createstruct
        Window* pWindow = reinterpret_cast<Window*>(pCreateStruct->lpCreateParams);
        // store window instance pointer to userdata
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
        // switch window procedure to custom
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WndProc));
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWindow->MessageHandler(hWnd, msg, wParam, lParam);
}

LRESULT Window::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    // Imgui message handler
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    /* ========== Mouse messages ========== */
    case WM_MOUSEMOVE: {
        const POINTS mousePos = MAKEPOINTS(lParam);
        if (IsMouseInsideWindow(mousePos.x, mousePos.y)) {
            m_mouse.OnMouseMove(Point2D(mousePos.x, mousePos.y));
            if (GetForegroundWindow() == hWnd)
                SetCapture(hWnd);
            if (!m_mouse.IsInWindow())
                m_mouse.OnMouseEnter();
        }
        else if (wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON)) {
            m_mouse.OnMouseMove(Point2D(mousePos.x, mousePos.y));
        }
        else {
            ReleaseCapture();
            m_mouse.OnMouseLeave();
        }

        break;
    }
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN: {
        SetCapture(hWnd);

        const POINTS mousePos = MAKEPOINTS(lParam);
        if (WM_LBUTTONDOWN == msg)
            m_mouse.OnButtonUp(Point2D(mousePos.x, mousePos.y), Mouse::Input::Type::LButtonDown);
        else if (WM_MBUTTONDOWN == msg)
            m_mouse.OnButtonUp(Point2D(mousePos.x, mousePos.y), Mouse::Input::Type::MButtonDown);
        else if (WM_RBUTTONDOWN == msg)
            m_mouse.OnButtonUp(Point2D(mousePos.x, mousePos.y), Mouse::Input::Type::RButtonDown);
        break;
    }
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP: {
        const POINTS mousePos = MAKEPOINTS(lParam);
        if (WM_LBUTTONUP == msg)
            m_mouse.OnButtonUp(Point2D(mousePos.x, mousePos.y), Mouse::Input::Type::LButtonUp);
        else if (WM_MBUTTONUP == msg)
            m_mouse.OnButtonUp(Point2D(mousePos.x, mousePos.y), Mouse::Input::Type::MButtonUp);
        else if (WM_RBUTTONUP == msg)
            m_mouse.OnButtonUp(Point2D(mousePos.x, mousePos.y), Mouse::Input::Type::RButtonUp);

        if (!IsMouseInsideWindow(mousePos.x, mousePos.y)) {
            ReleaseCapture();
            m_mouse.OnMouseLeave();
        }
        break;
    }
    case WM_MOUSEWHEEL: {
        const POINTS mousePos = MAKEPOINTS(lParam);
        const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        m_mouse.OnWheelScrolled(Point2D(mousePos.x, mousePos.y), delta);
        break;
    }
        
    /* ========== Keyboard messages ========== */
    case WM_KILLFOCUS: {
        m_keyboard.ClearKeyState();
        break;
    }
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN: {
        m_keyboard.OnKeyDown(static_cast<unsigned char>(wParam));
        break;
    }
    case WM_KEYUP:
    case WM_SYSKEYUP: {
        m_keyboard.OnKeyUp(static_cast<unsigned char>(wParam));
        break;
    }
    case WM_CHAR: {
        m_keyboard.OnCharEntered(static_cast<unsigned char>(wParam));
        break;
    }

    /* ========== System messages ========== */
    case WM_SIZE: {
        m_windowWidth = LOWORD(lParam);
        m_windowHeight = HIWORD(lParam);
        break;
    }
    case WM_CLOSE: {
        PostQuitMessage(0);
        return 0;	// to prevent DefWindowProc destroy this instance, let destructor does it
        break;
    }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
