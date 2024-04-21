#include "Mouse.h"

#include "SeaotterEngine/Common/pch.h"
#include <assert.h>

#include "SeaotterEngine/Common/constant.h"

Mouse::Mouse() : m_isInWindow(false), m_position({ 0, 0 }), m_wheelDelta(0), m_LButtonState(false), m_MButtonState(false), m_RButtonState(false) {
}

Mouse::Input Mouse::ReadFirstInput() {
	if (m_inputBuffer.size() > 0) {
		Input input = m_inputBuffer.front();
		m_inputBuffer.pop();
		return input;
	}

	return Input(Input::Type::Empty, Point2D());
}

inline void Mouse::PopInputBuffer() {
	while (m_inputBuffer.size() > kInputBufferLimit) {
		m_inputBuffer.pop();
	}
}

void Mouse::OnMouseEnter() {
	m_isInWindow = true;
	m_inputBuffer.push(Input(Input::Type::Enter, Point2D()));
	PopInputBuffer();
}

void Mouse::OnMouseLeave() {
	ClearInputBuffer();
	m_isInWindow = false;
	m_inputBuffer.push(Input(Input::Type::Leave, Point2D()));
	PopInputBuffer();
}

void Mouse::OnMouseMove(const Point2D& position) {
	m_position.x = position.x;
	m_position.y = position.y;

	m_inputBuffer.push(Input(Input::Type::Move, position));
	PopInputBuffer();
}

void Mouse::OnButtonDown(const Point2D& position, Input::Type type) {
	if (Input::Type::LButtonDown == type)
		m_LButtonState = true;
	else if (Input::Type::RButtonDown == type)
		m_RButtonState = true;
	else if (Input::Type::MButtonDown == type)
		m_MButtonState = true;
	else
		assert("Only accept ButtonDown input type");

	m_inputBuffer.push(Input(type, position));
	PopInputBuffer();
}

void Mouse::OnButtonUp(const Point2D& position, Input::Type type) {
	if (Input::Type::LButtonUp == type)
		m_LButtonState = false;
	else if (Input::Type::RButtonUp == type)
		m_RButtonState = false;
	else if (Input::Type::MButtonUp == type)
		m_MButtonState = false;
	else
		assert("Only accept ButtonUp input type");

	m_inputBuffer.push(Input(type, position));
	PopInputBuffer();
}

void Mouse::OnWheelScrolled(const Point2D& position, int delta) {
	m_wheelDelta += delta;
	while (m_wheelDelta >= WHEEL_DELTA) {
		m_wheelDelta -= WHEEL_DELTA;
		m_inputBuffer.push(Input(Input::Type::WheelUp, position));
		PopInputBuffer();
	}
	while (m_wheelDelta <= -WHEEL_DELTA) {
		m_wheelDelta += WHEEL_DELTA;
		m_inputBuffer.push(Input(Input::Type::WheelDown, position));
		PopInputBuffer();
	}
}