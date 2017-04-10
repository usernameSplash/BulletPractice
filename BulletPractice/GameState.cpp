#include "GameState.h"

World* GameState::world = nullptr;
Input* GameState::gameInput = nullptr;
D3DClass* GameState::graphics = nullptr;
GameTimer* GameState::frameTimer = nullptr;
GameWindow* GameState::window = nullptr;

void GameState::Initialize(HINSTANCE instanceHandle, int nShowCmd)
{
	window = new GameWindow(instanceHandle, nShowCmd);
	graphics = new D3DClass(window->getWindowHandle());
	frameTimer = new GameTimer();
	gameInput = new Input(instanceHandle, window->getWindowHandle());
	world = new World1(graphics->getDevice(), new DirectionalEnemy(graphics->getDevice(), new Texture(graphics->getDevice(),L"./res/Enemy.dds"), 
														0.0f, 0.0f, 0.0f, 0.0f, 500.0f, 0.0f, 1.0f));

	//타이머 초기화
	GameState::frameTimer->Reset();
}

void GameState::Shutdown()
{
	delete frameTimer;
	delete graphics;
	delete world;
	delete gameInput;
	delete window;
}