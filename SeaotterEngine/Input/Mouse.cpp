#include "Mouse.h"

#include "SeaotterEngine/Common/WindowsUtils.h"
#include "SeaotterEngine/Common/Common.h"

Mouse::Input Mouse::ReadFirstInput() {
	if (m_inputBuffer.size() > 0) {
		Input input = m_inputBuffer.front();
		m_inputBuffer.pop();
		return input;
	}

	return Input(Input::Type::Empty, Point2D());
}

void Mouse::PopInputBuffer() {
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

void Mouse::OnLButtonDown(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::LButtonDown, position));
	PopInputBuffer();
}

void Mouse::OnLButtonUp(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::LButtonUp, position));
	PopInputBuffer();
}

void Mouse::OnRButtonDown(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::RButtonDown, position));
	PopInputBuffer();
}

void Mouse::OnRButtonUp(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::RButtonUp, position));
	PopInputBuffer();
}

void Mouse::OnMButtonDown(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::MButtonDown, position));
	PopInputBuffer();
}

void Mouse::OnMButtonUp(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::MButtonUp, position));
	PopInputBuffer();
}

void Mouse::OnWheelScrolled(const Point2D& position, int delta) {
	m_wheelDelta += delta;
	while (m_wheelDelta >= WHEEL_DELTA) {
		m_wheelDelta -= WHEEL_DELTA;
		OnWheelUp(position);
	}
	while (m_wheelDelta <= -WHEEL_DELTA) {
		m_wheelDelta += WHEEL_DELTA;
		OnWheelDown(position);
	}
}

void Mouse::OnWheelUp(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::WheelUp, position));
	PopInputBuffer();
}

void Mouse::OnWheelDown(const Point2D& position) {
	m_inputBuffer.push(Input(Input::Type::WheelDown, position));
	PopInputBuffer();
}