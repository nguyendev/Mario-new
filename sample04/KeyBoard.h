#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include  <Windows.h>

bool InitKeyBoard(HINSTANCE, HWND);
class KeyBoard
{
private:
	char buffer[256];
	char KeyPressState[256];
	int width;
	int height;
public:
	KeyBoard();
	~KeyBoard();
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 keyboard;
	DIMOUSESTATE mouseState;
	bool isInitSuccess;
	int xMouse;
	int yMouse;
	KeyBoard(HWND hWnd, HINSTANCE hInstance);
	void GetKey();
	bool KeyDown(int key);
	bool KeyUp(int key);
	bool KeyPress(int key);
};

