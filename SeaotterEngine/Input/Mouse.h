#pragma once

#include <queue>

#include "SeaotterEngine/Common/Math.h"

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
	Mouse() : m_isInWindow(false), m_position({ 0, 0 }), m_wheelDelta(0) {}
	~Mouse() = default;

	bool IsInWindow() const { return m_isInWindow; }
	Input ReadFirstInput();
	bool InputBufferEmpty() const { return m_inputBuffer.empty(); }

	// pop buffers until reach kInputBufferLimit
	void PopInputBuffer();
	
	// empty buffer
	void ClearInputBuffer() { std::queue<Input> q; std::swap(m_inputBuffer, q); }

private:
	// called by Window instance
	void OnMouseEnter();
	void OnMouseLeave();
	void OnMouseMove(const Point2D& pos);
	void OnLButtonDown(const Point2D& pos);
	void OnLButtonUp(const Point2D& pos);
	void OnRButtonDown(const Point2D& pos);
	void OnRButtonUp(const Point2D& pos);
	void OnMButtonDown(const Point2D& pos);
	void OnMButtonUp(const Point2D& pos);
	void OnWheelScrolled(const Point2D& pos, int delta);
	void OnWheelUp(const Point2D& pos);
	void OnWheelDown(const Point2D& pos);

private:
	std::queue<Input> m_inputBuffer;
	bool m_isInWindow;
	Point2D m_position;
	int m_wheelDelta;
};