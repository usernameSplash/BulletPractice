#include "GameWindow.h"
#include "GameConstant.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

GameWindow::GameWindow(HINSTANCE instanceHandle, int show) :
	m_WindowHandle(nullptr),
	m_WindowSouldClose(false)
{
	WNDCLASS wc;

	//win32 √ ±‚»≠
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BasicWndClass";

	if (!RegisterClass(&wc))
	{
		throw L"RegisterClass Failed";
	}

	m_WindowHandle = CreateWindow(L"BasicWndClass", L"Dongjun & Kyeongmin's Game", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, GameConstant::GameWidth, GameConstant::GameHeight, 0, 0,
		instanceHandle, 0);

	if (m_WindowHandle == 0)
	{
		throw L"CreateWindow Failed";
	}

	ShowWindow(m_WindowHandle, show);
	UpdateWindow(m_WindowHandle);
}

GameWindow::~GameWindow()
{

}

void GameWindow::PollEvents()
{
	MSG msg = { 0 };
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			m_WindowSouldClose = true;
		}
	}
}

HWND GameWindow::getWindowHandle()
{
	return m_WindowHandle;
}

bool GameWindow::windowShouldClose()
{
	return m_WindowSouldClose;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}