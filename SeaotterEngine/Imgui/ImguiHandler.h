#pragma once

class ImguiHandler
{
	friend class Game;

public:
	ImguiHandler();
	~ImguiHandler();

	void Init();

private:
	bool& GetShowWindow() { return m_showWindow; }

private:
	bool m_showWindow;
};