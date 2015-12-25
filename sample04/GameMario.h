#ifndef _GAME_MARIO_H_
#define _GAME_MARIO_H_

#include <d3dx9.h>

#include "game.h"
#include "sprite.h"
#include "Global.h"
// Objects
#include "BaseObject.h" 
//#include "Mario.h"
#include "Brick.h"


// Others
#include "Collision.h"
#include "Camera.h"
#include "Audio.h"
#include "QuadTree.h"

class CGameMario : public CGame
{
public:
	CGameMario();
	CGameMario(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~CGameMario();

	LPD3DXSPRITE _SpriteHandler;
	CSprite * _sprites[30];
	BaseObject* _staticObjs[1000];
	list<BaseObject*> staticObjs;
	list<BaseObject*> dynamicObjs;
	BaseObject* _dynamicObjs[40];
	BaseObject* _test;
	Camera * _camera;
	Audio* _audio;
	QuadTree* _quadTree;
	LPD3DXFONT	_font;

	int _countI = 0;
	int _live;
	CSprite * brick;

	DWORD last_time;		// this is to control the animate rate of kitty
	int _state;
	int _curState;
	float wait1Sec;
	int _timeGame;
	int _life;

protected:

	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float TPF);
	void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float TPF);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void UpdateWorld(float TPF);
	void RenderBackground(int view_port_x, int view_port_y);
	void DrawScore();
public:
	//Load Resource-----------
	CSound *_sound_1up, *_sound_Beep, *_sound_BigJump, *_sound_BowserDie, *_sound_Break, *_sound_Bump, *_sound_Coin, *_sound_Background;
	CSound *_sound_Die, *_sound_EnemyFire, *_sound_FireBall, *_sound_Flagpole, *_sound_GameOver, *_sound_Item, *_sound_Warp;
	CSound	*_sound_Jump, *_sound_Kick, *_sound_Pause, *_sound_Powerup, *_sound_Skid, *_sound_Squish, *_sound_Thwomp, *_sound_Vine;
	void LoadAudio();
	void LoadSprite();


	//-------------------------
	void ChangeMap(int Map);
	LPDIRECT3DSURFACE9 _title;
	int _marioMenuX;
	int _marioMenuY;
	CSprite* _marioMenu;
	bool isLoad = false;
	BaseObject* _mario;
	int _Map;
	void ChangeState(char* state);
};
#endif _GAME_MARIO_H_