#pragma once
#include <dinput.h>
#include <Windows.h>
#include <xnamath.h>

class Input
{
public:
	Input(HINSTANCE instanceHandle, HWND windowHandle);
	~Input();

	void PollInput();

	XMFLOAT2 getMousePosition();
	bool getKeyPressed(int key);
	bool getKeyReleased(int key);
	bool getKeyRepeated(int key);
	bool getButtonPressed(int button);
	bool getButtonReleased(int button);
	bool getButtonRepeated(int button);

private:
	void readMouse();
	void readKeyboard();
private:
	IDirectInput8* m_Input;
	IDirectInputDevice8* m_Keyboard;
	IDirectInputDevice8* m_Mouse;
	int m_KeyboardStateNum;
	XMFLOAT2 m_MousePosition;
	unsigned char* m_CurrKeyboardState;
	unsigned char* m_PrevKeyboardState;
	DIMOUSESTATE* m_CurrMouseState;
	DIMOUSESTATE* m_PrevMouseState;
};