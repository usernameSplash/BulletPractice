#pragma once
#include <Windows.h>

class GameWindow
{
public:
	GameWindow(HINSTANCE instanceHandle, int show);
	GameWindow(GameWindow&) = default;
	~GameWindow();

	void PollEvents();
	HWND getWindowHandle();
	bool windowShouldClose();
private:

private:
	HWND m_WindowHandle;
	bool m_WindowSouldClose;
};