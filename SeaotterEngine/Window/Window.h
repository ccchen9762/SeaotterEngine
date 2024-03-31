#pragma once

#include <string>

#include "SeaotterEngine/Common/WindowsUtils.h"
#include "SeaotterEngine/Input/Mouse.h"
#include "SeaotterEngine/Input/Keyboard.h"

class Window {
public:
	Window(const wchar_t windowClassName[], const wchar_t windowTitle[], const unsigned int windowWidth, const unsigned int windowHeight);
	~Window();

	void CaptureWindow() { SetCapture(m_hWnd); }
	void SetWindowTitle(const std::wstring& title) { SetWindowText(m_hWnd, title.c_str()); }

private:
	static LRESULT CALLBACK PreWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	inline bool IsMouseInsideWindow(int x, int y) const {
		return x >= 0 && x < static_cast<int>(m_windowWidth) &&
			y >= 0 && y < static_cast<int>(m_windowHeight);
	}

public:
	Mouse m_mouse;
	Keyboard m_keyboard;

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	std::wstring m_windowClassName;
	std::wstring m_windowTitle;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
};