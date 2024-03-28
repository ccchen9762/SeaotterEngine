#include "WindowClass.h"

WindowClass::WindowClass(const wchar_t windowClassName[], const wchar_t windowTitle[], unsigned int windowWidth, unsigned int windowHeight) :
    m_windowWidth(windowWidth), m_windowHeight(windowHeight) {

    // register window class
    WNDCLASSEX wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX); // structure size
    wcex.style = CS_OWNDC; // allow rendering multiple windows independently (unique device context for each window)
    wcex.lpfnWndProc = WindowProc; // pointer to awindow procedure
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
    clientSpace.left = 100;
    clientSpace.right = windowWidth + 100;
    clientSpace.top = 100;
    clientSpace.bottom = windowHeight + 100;
    AdjustWindowRect(&clientSpace, WS_OVERLAPPEDWINDOW, false);

    // create window instance
    m_hwnd = CreateWindowEx(WS_EX_ACCEPTFILES,
        windowClassName, windowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, // initial position 
        clientSpace.right - clientSpace.left, clientSpace.bottom - clientSpace.top, // size
        nullptr, // parent window
        nullptr, // menu
        GetModuleHandle(nullptr), 
        nullptr // additional application data, point to this for later use 
    );

    ShowWindow(m_hwnd, SW_SHOW);
}

WindowClass::~WindowClass() {
}

LRESULT CALLBACK WindowClass::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}