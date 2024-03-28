#pragma once

#include <windows.h>

class WindowClass {
public:
	WindowClass(const wchar_t windowClassName[], const wchar_t windowTitle[], unsigned int windowWidth, unsigned int windowHeight);
	~WindowClass();

private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hwnd;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
};