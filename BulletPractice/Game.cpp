#include "Game.h"
#include "GameState.h"
#include <dinput.h>

int Game::m_FrameCounter = 0;
bool Game::m_IsGameSouldClose = false;

void Game::Initialize()
{
	m_FrameCounter = 0;
	m_IsGameSouldClose = false;
}

void Game::Shutdown()
{
	
}

bool Game::frame()
{
	//프레임당 걸리는 시간과 초당 프레임 계산
	GameState::frameTimer->Tick();
	m_FrameCounter += 1;
	if (GameState::frameTimer->TotalTime() > 1.0)
	{
		//초당 프레임 수 출력
		char str[100];
		sprintf(str, "FPS : %d, mSPF : %lf\n",
			static_cast<int>(m_FrameCounter / GameState::frameTimer->TotalTime()),
			static_cast<double>(GameState::frameTimer->TotalTime()) * 1000 / m_FrameCounter);
		OutputDebugStringA(str);
		m_FrameCounter = 0;
		GameState::frameTimer->Reset();
	}

	GameState::window->PollEvents();
	GameState::gameInput->PollInput();

	float d = GameState::frameTimer->DeltaTime();
	if (d > 0.1) d = 0.1;
	GameState::world->update(d);

	GameState::graphics->render();

	if (GameState::window->windowShouldClose())
	{
		return false;
	}

	if (GameState::gameInput->getKeyPressed(DIK_LALT) || GameState::gameInput->getKeyRepeated(DIK_LALT))
	{
		if (GameState::gameInput->getKeyPressed(DIK_F4) || GameState::gameInput->getKeyRepeated(DIK_F4))
		{
			return false;
		}
	}

	if (m_IsGameSouldClose)
	{
		return false;
	}

	return true;
}

void Game::gameInit()
{
	m_IsGameSouldClose = false;
}

void Game::gameEnd()
{
	m_IsGameSouldClose = true;
}