#include "KeyBoard.h"



KeyBoard::KeyBoard(){};
KeyBoard::KeyBoard(HWND hWnd, HINSTANCE hInstance)
{
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
	if FAILED(hr) isInitSuccess = false;

	//Create keyboard
	hr = dInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if FAILED(hr)
		isInitSuccess = false;
	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr)
		isInitSuccess = false;
	hr = keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if FAILED(hr)
		isInitSuccess = false;
	hr = keyboard->Acquire();
	if FAILED(hr)
		isInitSuccess = false;

	for (int i = 0; i < 256; i++){
		KeyPressState[i] = 0;
	}

	isInitSuccess = true;
}
void KeyBoard::GetKey()
{
	HRESULT hr = keyboard->GetDeviceState(sizeof(buffer), (LPVOID)&buffer);
	if FAILED(hr) keyboard->Acquire();
}

bool KeyBoard::KeyDown(int key)
{
	//check the state of the key
	if (buffer[key] & 0x80){
		return true;
	}
	else {
		return false;
	}
}
bool KeyBoard::KeyUp(int key)
{
	//check the state of the key
	if (buffer[key] & 0x80){
		return false;
	}
	else {
		return true;
	}
}
bool KeyBoard::KeyPress(int key)
{

	//check for keydown
	if (KeyDown(key)){
		KeyPressState[key] = 1;
	}
	//check for key reaching the keydown state
	if (KeyPressState[key] == 1){
		//check for key release
		if (KeyUp(key))
			KeyPressState[key] = 2;
	}

	//check if key has been pressed and released
	if (KeyPressState[key] == 2){
		//reset the key status
		KeyPressState[key] = 0;
		return true;
	}

	return false;
}

KeyBoard::~KeyBoard()
{
	keyboard->Unacquire();
	keyboard->Release();
	keyboard = NULL;
	dInput->Release();
	dInput = NULL;
}

