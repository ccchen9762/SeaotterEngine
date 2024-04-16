#pragma once

#include <queue>

#include "SeaotterEngine/Common/math.h"

class Mouse
{
	friend class Window;

public:
	class Input
	{
	public:
		enum class Type {
			Empty, Enter, Leave, Move,
			LButtonDown, LButtonUp,
			RButtonDown, RButtonUp,
			MButtonDown, MButtonUp,
			WheelUp, WheelDown
		};

	public:
		Input(Type type, const Point2D& position) : m_type(type), m_position(position) {}
		~Input() = default;

		Type GetType() const { return m_type; }
		Point2D GetPosition() const { return m_position; }

	private:
		Type m_type;
		Point2D m_position;
	};

public:
	Mouse();
	~Mouse() = default;

	bool IsInWindow() const { return m_isInWindow; }
	bool IsLButtonPressed() { return m_LButtonState; }
	bool IsMButtonPressed() { return m_MButtonState; }
	bool IsRButtonPressed() { return m_RButtonState; }
	bool IsInputBufferEmpty() const { return m_inputBuffer.empty(); }

	Input ReadFirstInput();

	// pop buffers until reach kInputBufferLimit
	inline void PopInputBuffer();
	// empty buffer
	void ClearInputBuffer() { std::queue<Input> q; std::swap(m_inputBuffer, q); }

private:
	// called by Window instance
	void OnMouseEnter();
	void OnMouseLeave();
	void OnMouseMove(const Point2D& position);
	void OnButtonDown(const Point2D& position, Input::Type type);
	void OnButtonUp(const Point2D& position, Input::Type type);
	void OnWheelScrolled(const Point2D& position, int delta);

private:
	std::queue<Input> m_inputBuffer;
	bool m_isInWindow;
	bool m_LButtonState;
	bool m_MButtonState;
	bool m_RButtonState;
	Point2D m_position;
	int m_wheelDelta;
};