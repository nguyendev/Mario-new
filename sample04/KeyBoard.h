#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include  <Windows.h>
#include "Global.h"

class KeyBoard
{
private:
	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 
	char KeyPressState[256];
public:
	KeyBoard();
	~KeyBoard();
	LPDIRECTINPUT8 _di;
	LPDIRECTINPUTDEVICE8 _Keyboard;
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
	
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	void _ProcessKeyBoard();
	KeyBoard(HWND hWnd, HINSTANCE hInstance);
	void GetKey();
	bool KeyDown(int key);
	bool KeyUp(int key);
	bool KeyPress(int key);
};

#endif _KEYBOARD_H_
