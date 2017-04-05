#include "Input.h"
#include "GameConstant.h"
#include <iterator>

Input::Input(HINSTANCE instanceHandle, HWND windowHandle) :
	m_Input(nullptr),
	m_Keyboard(nullptr),
	m_Mouse(nullptr),
	m_MousePosition({ 0.0f, 0.0f }),
	m_CurrKeyboardState(new unsigned char[256]),
	m_PrevKeyboardState(new unsigned char[256]),
	m_CurrMouseState(new DIMOUSESTATE()),
	m_PrevMouseState(new DIMOUSESTATE())
{
	HRESULT hr;

	hr = DirectInput8Create(instanceHandle, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void **>(&m_Input), nullptr);
	if (FAILED(hr))
	{
		throw "Create DirectInput Failed";
	}

	hr = m_Input->CreateDevice(GUID_SysKeyboard, &m_Keyboard, nullptr);
	if (FAILED(hr))
	{
		throw "Create Keyboard Device Failed";
	}

	hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		throw "Keyboard Data Set Failed";
	}

	hr = m_Keyboard->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
	{
		throw "Keyboard SetCooperativeLevel Failed";
	}

	hr = m_Keyboard->Acquire();
	if (FAILED(hr))
	{
		throw "Acquire Keyboard Failed";
	}

	hr = m_Input->CreateDevice(GUID_SysMouse, &m_Mouse, nullptr);
	if (FAILED(hr))
	{
		throw "Create Mouse Device Failed";
	}

	hr = m_Mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		throw "Mouse SetDataFormat Failed";
	}

	hr = m_Mouse->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
	{
		throw "Mouse SetCooperativeLevel Failed";
	}

	hr = m_Mouse->Acquire();
	if (FAILED(hr))
	{
		throw "Acquire Mouse Failed";
	}

	memset(static_cast<void *>(m_PrevKeyboardState), 0, sizeof(unsigned char) * 256);
	memset(static_cast<void *>(m_CurrKeyboardState), 0, sizeof(unsigned char) * 256);
}

Input::~Input()
{
	delete m_CurrKeyboardState;
	delete m_CurrMouseState;
	delete m_PrevKeyboardState;
	delete m_PrevMouseState;

	if (m_Mouse)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = nullptr;
	}
	if (m_Keyboard)
	{
		m_Keyboard->Unacquire();
		m_Keyboard->Release();
		m_Keyboard = nullptr;
	}
	if (m_Input)
	{
		m_Input->Release();
		m_Input = nullptr;
	}
}

void Input::PollInput()
{
	unsigned char* temp = m_CurrKeyboardState;
	m_CurrKeyboardState = m_PrevKeyboardState;
	m_PrevKeyboardState = temp;

	DIMOUSESTATE *mousetemp = m_CurrMouseState;
	m_CurrMouseState = m_PrevMouseState;
	m_PrevMouseState = mousetemp;

	readKeyboard();
	readMouse();

	m_MousePosition.x += m_CurrMouseState->lX;
	m_MousePosition.y -= m_CurrMouseState->lY;

	if (m_MousePosition.x < -GameConstant::GameWidth / 2) m_MousePosition.x = -GameConstant::GameWidth / 2;
	if (GameConstant::GameWidth / 2 < m_MousePosition.x) m_MousePosition.x = GameConstant::GameWidth / 2;
	if (m_MousePosition.y < -GameConstant::GameHeight / 2) m_MousePosition.y = -GameConstant::GameHeight / 2;
	if (GameConstant::GameHeight / 2 < m_MousePosition.y) m_MousePosition.y = GameConstant::GameHeight / 2;
}

XMFLOAT2 Input::getMousePosition()
{
	return m_MousePosition;
}

bool Input::getKeyPressed(int key)
{
	if (!(0 <= key && key < 256))
	{
		throw "Key code Error";
	}

	if (!(m_PrevKeyboardState[key] & 0x80) && (m_CurrKeyboardState[key] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getKeyReleased(int key)
{
	if (!(0 <= key && key < 256))
	{
		throw "Key code Error";
	}

	if ((m_PrevKeyboardState[key] & 0x80) && !(m_CurrKeyboardState[key] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getKeyRepeated(int key)
{
	if (!(0 <= key && key < 256))
	{
		throw "Key code Error";
	}

	if ((m_PrevKeyboardState[key] & 0x80) && (m_CurrKeyboardState[key] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getButtonPressed(int button)
{
	if (!(m_PrevMouseState->rgbButtons[button] & 0x80) && (m_CurrMouseState->rgbButtons[button] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getButtonReleased(int button)
{
	if ((m_PrevMouseState->rgbButtons[button] & 0x80) && !(m_CurrMouseState->rgbButtons[button] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getButtonRepeated(int button)
{
	if ((m_PrevMouseState->rgbButtons[button] & 0x80) && (m_CurrMouseState->rgbButtons[button] & 0x80))
	{
		return true;
	}
	else return false;
}

void Input::readKeyboard()
{
	HRESULT hr;

	hr = m_Keyboard->GetDeviceState(sizeof(unsigned char) * 256, reinterpret_cast<LPVOID>(m_CurrKeyboardState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_Keyboard->Acquire();
		}
		else
		{
			throw "Get KeyboardState Failed";
		}
	}
}

void Input::readMouse()
{
	HRESULT hr;

	hr = m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), reinterpret_cast<LPVOID *>(m_CurrMouseState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_Mouse->Acquire();
		}
		else
		{
			throw "Get MouseState Failed";
		}
	}
}

