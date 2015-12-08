#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#include <d3dx9.h>

#include "game.h"
#include "sprite.h"
#include "BaseObject.h"
#include "Collision.h"
#include "Camera.h"
#include "Audio.h"
#include "Writer.h"
#include "KeyBoard.h"


class CMarioSample: public CGame
{
public: 
	CMarioSample(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~CMarioSample();

	LPD3DXSPRITE _SpriteHandler;
	CSprite * _sprites[20];

	Collision* _col;
	BaseObject* _staticObjs[1000];
	BaseObject* mario;
	BaseObject* testBrick;
	BaseObject* testBrick2;
	Camera * _camera;
	Audio* _audio;
	Writer* _writer;
	LPD3DXFONT	_fontArial;
	int _countI = 0;
	KeyBoard* _keyboard;


	DWORD last_time;		// this is to control the animate rate of kitty
	int _state;
	float wait1Sec;
	int timegame;
	//LPDIRECT3DSURFACE9 Background;

protected:

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void UpdateWorld(int Delta);
	virtual void OnKeyDown(int KeyCode);

	void Update(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	void RenderBackground(int view_port_x, int view_port_y);
	
	void CollisionHanding();
	

	//Load Resource-----------
	CSound *_sound_1up, *_sound_Beep, *_sound_BigJump, *_sound_BowserDie, *_sound_Break, *_sound_Bump, *_sound_Coin;
	CSound *_sound_Die, *_sound_EnemyFire, *_sound_FireBall, *_sound_Flagpole, *_sound_GameOver, *_sound_Item, *_sound_Warp;
	CSound	*_sound_Jump, *_sound_Kick, *_sound_Pause, *_sound_Powerup, *_sound_Skid, *_sound_Squish, *_sound_Thwomp, *_sound_Vine;

	LPDIRECT3DSURFACE9 _title;
	void LoadAudio();
	void LoadSprite();
	void LoadMap();


	CSprite* _marioMenu;
	int _marioMenuX;
	int _marioMenuY;
	void RenderMenu(LPDIRECT3DDEVICE9);

};
#endif