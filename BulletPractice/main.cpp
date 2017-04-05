#include <Windows.h>

#include "Game.h"
#include "GameState.h"
#include "GameConstant.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, PSTR commandLine, int nShowCmd)
{
	bool running = true;

	try
	{
		//게임 클래스 객체 생성
		GameState::Initialize(instanceHandle, nShowCmd);

		Game::gameInit();
		//게임루프
		while (running)
		{
			running = Game::frame();
		}

	}
	catch(wchar_t* errTxt)
	{
		//에러처리
		MessageBox(0, errTxt, 0, 0);
		return 1;
	}
	catch (char* errTxt)
	{
		//에러처리
		MessageBoxA(0, errTxt, 0, 0);
		return 1;
	}

	return 0;
}