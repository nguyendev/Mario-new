#include "KeyBoard.h"




KeyBoard::KeyBoard(){};
KeyBoard::KeyBoard(HWND _hWnd, HINSTANCE _hInstance)
{
	HRESULT
		hr = DirectInput8Create
		(
		_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_di, NULL
		);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;



	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;


	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);


	hr = _Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size


	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;
	for (int i = 0; i < 256; i++){
		KeyPressState[i] = 0;
	}
}
void KeyBoard::_ProcessKeyBoard()
{
	_Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}
bool KeyBoard::KeyDown(int KeyCode)
{
	if (_KeyStates[KeyCode] & 0x80)
		return true;
	else
		return false;
}
bool KeyBoard::KeyUp(int KeyCode)
{
	if (_KeyStates[KeyCode] & 0x80)
		return false;
	else
		return true;
}

bool KeyBoard::KeyPress(int KeyCode)
{
	//check for keydown
	if (KeyDown(KeyCode)){
		KeyPressState[KeyCode] = 1;
	}
	if (KeyPressState[KeyCode] == 1){
		//check for key release
		if (KeyUp(KeyCode))
			KeyPressState[KeyCode] = 2;
	}

	//check if key has been pressed and released
	if (KeyPressState[KeyCode] == 2){
		//reset the key status
		KeyPressState[KeyCode] = 0;
		return true;
	}

	return false;
}

void KeyBoard::OnKeyUp(int KeyCode) {}
//int CGame::IsKeyUp(int KeyCode)
//{
//	return(_KeyStates[KeyCode] & 0x80) <0
//}
void KeyBoard::OnKeyDown(int KeyCode) { }

KeyBoard::~KeyBoard()
{
	if (_Keyboard)
	{
		_Keyboard->Unacquire();
		_Keyboard->Release();
	}

	if (_di) _di->Release();
}

