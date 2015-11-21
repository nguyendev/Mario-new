#ifndef _GAME_H
#define _GAME_H

#include <d3d9.h>
#include <d3dx9.h>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#include "Graphic.h"
#include "Sprite.h"
#include "Animation.h"
#include "Input.h"
#include "TimeManager.h"
#include "Camera.h"
#include <list>
#include "BaseObject.h"
using namespace std;

class Camera;
class BaseObject;
class Game
{
private:

	//Framework ----------------------
	Graphic		*g;
	float		TPF;					//Time per frame
	HWND		hWnd;
	HINSTANCE	hInstance;
	LPD3DXFONT	fontArial;
	Input* _input;
	TimeManager* _timeManager;
	void ProcessInput();
	void Update();
	void Render();
	//--------------------------------

	//Framework ----------------------
public:
	Sprite* _sprites[20];
	Game(HWND _hWnd, HINSTANCE _hInstance);
	~Game();
	void GameRun();
	
	Camera* _camera;
	list<BaseObject*>	_staticObjs;
	list<BaseObject*>	_dynamicObjs;



	IDirect3DSurface9* menu;	//Background state menu
	//IDirect3DSurface9* itemMenu;//Hiện phần new game, load game...
	IDirect3DSurface9* gameOver; //Background state gameOver
	IDirect3DSurface9* gameWin; //Background state gameWver
	IDirect3DSurface9* about;   //Background state about game
	IDirect3DSurface9* gameConfirm;//Background state game confirm: khi đang chơi mà player nhấn phím ESC thì sẽ hiện
	                               //ra thông báo để hỏi xem player có thực sự muốn thoát hay không?
	RECT menurect;//k
	int posymenu;//k
	int posymenuC;
	//-----------

};

#endif