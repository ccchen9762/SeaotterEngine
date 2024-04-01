#pragma once

#include <bitset>
#include <queue>

class Keyboard {

	friend class Window;

private:
	struct Input {
	public:
		enum class Type { Empty, KeyDown, KeyUp };

		Input(Type type, unsigned char keyCode) : m_type(type), m_keyCode(keyCode) {}
		~Input() = default;

		Type GetType() const { return m_type; }
		unsigned char GetKey() const { return m_keyCode; }

	private:
		Type m_type;
		unsigned char m_keyCode;
	};

public:
	Keyboard() = default;
	~Keyboard() = default;

	// check if buffers are empty
	bool IsKeyPressed(unsigned char keyCode) const { return m_keyState[keyCode]; }
	bool IsInputBufferEmpty() const { return m_inputBuffer.empty(); }
	bool IsCharBufferEmpty() const { return m_charBuffer.empty(); }

	Input ReadFirstInput();
	char ReadFirstChar();

	// pop buffers until reach kInputBufferLimit
	inline void PopKeyEventBuffer();
	inline void PopCharBuffer();

	// empty buffer
	void ClearKeyState() { m_keyState.reset(); }
	void ClearInputBuffer() { std::queue<Input> q; std::swap(m_inputBuffer, q); }
	void ClearCharBuffer() { std::queue<char> q; std::swap(m_charBuffer, q); }

private:
	// called by Window instance
	void OnKeyDown(unsigned char keyCode);
	void OnKeyUp(unsigned char keyCode);
	void OnCharEntered(unsigned char character);

private:
	std::bitset<256> m_keyState;
	std::queue<Input> m_inputBuffer;
	std::queue<char> m_charBuffer;
};
