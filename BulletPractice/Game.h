#pragma once
#include <cstdio>
#include <Windows.h>

class Game
{
public:
	static void Initialize();
	static void Shutdown();

	static bool frame();

	static void gameInit();
	static void gameEnd();
private:
	static int m_FrameCounter;
	static bool m_IsGameSouldClose;
};