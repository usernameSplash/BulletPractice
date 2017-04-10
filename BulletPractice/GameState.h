#pragma once
#include "D3DClass.h"
#include "World1.h"
#include "Input.h"
#include "GameWindow.h"
#include "GameTimer.h"
#include <Windows.h>

class GameState
{
public:
	static D3DClass* graphics;
	static Input* gameInput;
	static GameWindow* window;
	static GameTimer* frameTimer;
	static World* world;

public:
	static void Initialize(HINSTANCE instanceHandle, int nShowCmd);
	static void Shutdown();
};