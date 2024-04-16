#include "Keyboard.h"

#include "SeaotterEngine/Common/common.h"

Keyboard::Input Keyboard::ReadFirstInput() {
	if (m_inputBuffer.size() > 0) {
		Input input = m_inputBuffer.front();
		m_inputBuffer.pop();
		return input;
	}

	return Input{ Input::Type::Empty, 0 };
}

char Keyboard::ReadFirstChar() {
	if (m_inputBuffer.size() > 0) {
		char keyEvent = m_charBuffer.front();
		m_charBuffer.pop();
		return keyEvent;
	}

	return 0;
}

inline void Keyboard::PopKeyEventBuffer() {
	while (m_inputBuffer.size() > kInputBufferLimit) {
		m_inputBuffer.pop();
	}
}

inline void Keyboard::PopCharBuffer() {
	while (m_charBuffer.size() > kInputBufferLimit) {
		m_charBuffer.pop();
	}
}

void Keyboard::OnKeyDown(unsigned char keyCode) {
	m_keyState[keyCode] = true;
	m_inputBuffer.push(Keyboard::Input(Keyboard::Input::Type::KeyDown, keyCode));
	PopKeyEventBuffer();
}

void Keyboard::OnKeyUp(unsigned char keyCode) {
	m_keyState[keyCode] = false;
	m_inputBuffer.push(Keyboard::Input(Keyboard::Input::Type::KeyUp, keyCode));
	PopKeyEventBuffer();
}

void Keyboard::OnCharEntered(unsigned char character) {
	m_charBuffer.push(character);
	PopCharBuffer();
}