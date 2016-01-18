#pragma warning(disable: 4244) // possible loss of data
#include <time.h>
#include <d3dx9.h>
#include "GameMario.h"
#include "utils.h"
#include "Goomba.h"
#include "Koopa.h"
#include <string>
#include <string.h>

#include "Writer.h"
#define MENU_MAX 170
#define MENU_MIN  149
#define MENU_INCREASE 17

KeyBoard* _keyboard = NULL;
CGameMario::CGameMario():CGame(){};
CGameMario::CGameMario(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) :
CGame(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	//Framework............................
	_camera = new Camera(0, 0, 800/ZOOM, 600/ZOOM);
	_keyboard = new KeyBoard(_hWnd, hInstance);
	//--------------------------------------
	for (int i = 0; i < 30; i++)
		_sprites[i] = NULL;
	_quadTree = NULL;
	_marioMenuY = MENU_MIN;
	_marioMenuX = 100;
	_life = 3;
	_coin = 0;
	_replay = 0;
	_score = 0;
	reX = 0;
	reY = 0;
	distanceMove = 0;
	isDrawEat = false;

}

void CGameMario::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	_audio = new Audio();
	_audio->initialize(_hWnd);
	srand((unsigned)time(NULL));
	D3DXCreateSprite(d3ddv, &_SpriteHandler);
	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);
	D3DXCreateFont(_d3ddv, 25, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Time New Roman"), &_font);
	LoadSprite();
	LoadAudio();

	_state = _curState = GS_MENU;
	wait1Sec = 0;

	//MenuGame
	_marioMenu = new CSprite(_SpriteHandler, "Image\\imgOptionCursor.png", 8, 8, 1, 1, 0.2);
	_marioReplay = new CSprite(_SpriteHandler, "Image\\imgSmallMario_Left.png", 16, 16, 8, 4, 0.2);
	_title = CreateSurface("Image\\imgbgMenu.png", d3ddv);


}

void CGameMario::UpdateWorld(float TPF)
{
	BaseObject* _obj;
	list<BaseObject*>::iterator i;
	switch (_state)
	{
	case GS_MENU:
		_life = 3;
		_coin = 0;
		break;
	case GS_PLAYING:
		_audio->PlaySoundA(_sound_Background);
		wait1Sec += TPF;
		if (wait1Sec > 1)
		{
			wait1Sec -= 1;
			_timeGame--;
		}
		for (i = staticObjs.begin(); i != staticObjs.end(); i++)
		{	
			_obj = *i; 
			if (_obj->getPosition().x < _camera->_cameraX - 10)
				_obj->_isNeedDelete = true;
			if (_obj->GetState("_isNeedDelete") == 1)
				_quadTree->DeleteObj(_obj, true);
		}
		for (i = dynamicObjs.begin(); i != dynamicObjs.end(); i++)
		{
			_obj = *i;
			if (_obj->GetState("_isNeedDelete") == 1)
				_quadTree->DeleteObj(_obj, false);
		}
		staticObjs.clear();
		dynamicObjs.clear();
		_quadTree->GetObjectsFromCamera(_camera->_rect, &staticObjs, &dynamicObjs);
		_camera->Update(_quadTree);
		for (i = staticObjs.begin(); i != staticObjs.end(); i++)
		{
			_obj = *i;
			if (_obj->getPosition().x>_camera->_cameraX - 10 && _obj->getPosition().x<_camera->_cameraX + WIDTH + 10)
				_obj->Update(TPF, &staticObjs, &dynamicObjs, _keyboard);
		}
		for (i = dynamicObjs.begin(); i != dynamicObjs.end(); i++)
		{
			_obj = *i;
			if (_obj->getPosition().x>_camera->_cameraX - WIDTH && _obj->getPosition().x<_camera->_cameraX + WIDTH + 100)
				_obj->Update(TPF, &staticObjs, &dynamicObjs, _keyboard);
		}
		_quadTree->Update(dynamicObjs);
		break;
	
	case GS_REPLAY:
		_replay += TPF;
		if (_replay > 2)
		{
			_replay = 0;

			ChangeMap(_Map);
		}
		
		break;
	case GS_NEXT_STAGE:				//Khi đổi màn
		ChangeMap(_Map + 1);
		break;
	case GS_GAMEOVER:
		_audio->PlaySound(_sound_GameOver);
		break;
	case GS_WIN:
		break;
	}
}

void CGameMario::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float TPF)
{
	BaseObject* obj;
	list<BaseObject*>::iterator i;
	list<Score*>::iterator iScore;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	///_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_OBJECTSPACE);
	switch (_state)
	{
	case GS_MENU:
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
		_marioMenu->Render(_marioMenuX, _marioMenuY,_camera->_cameraX,_camera->_cameraY,0.1);
		staticObjs.clear();
		d3ddv->StretchRect(_title, NULL, _BackBuffer, NULL, D3DTEXF_NONE);
		break;
	case GS_PLAYING:
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
		DrawScore();
		DrawEat();
		test();
		for (i = staticObjs.begin(); i != staticObjs.end(); i++)
		{
			obj = *i;
			if (obj->getPosition().x>_camera->_cameraX - 10 && obj->getPosition().x<_camera->_cameraX + 350)
				obj->Render();
		}
		for (i = dynamicObjs.begin(); i != dynamicObjs.end(); i++)
		{
			obj = *i;
			if (obj->getPosition().x>_camera->_cameraX -10 && obj->getPosition().x<_camera->_cameraX + 350)
				obj->Render();
		}
		break;
	case GS_REPLAY:case GS_NEXT_STAGE:
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
		DrawScore();
		if (_Map == 1)
			DrawTxt(L"WORLD 1.1", 355, 250, _font);
		else if (_Map == 2)
			DrawTxt(L"WORLD 1.2", 355, 250, _font);
		else
			DrawTxt(L"WORLD", 355, 250, _font);
		_marioReplay->setIndex(0);
		_marioReplay->Render(370 / ZOOM, 310 / ZOOM);
		
		DrawTxt(L"X", 420, 300, _font);
		text = to_string(_life);
		StringToWString(ws, text);
		DrawTxt(ws, 455, 300, _font);
		break;
	case GS_GAMEOVER:
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
		DrawScore();
		DrawTxt(L"GAME OVER", 355, 250, _font);
		break;
	case GS_WIN:
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
		DrawScore();
		DrawTxt(L"YOU WIN", 355, 250, _font);
		break;
	}
	_SpriteHandler->End();
}

void CGameMario::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float TPF)
{
	_keyboard->_ProcessKeyBoard();

	switch (_state)
	{
	case GS_MENU:
		if (_keyboard->KeyPress(DIK_Q))
			PostQuitMessage(0);
		else if (_keyboard->KeyPress(DIK_DOWN))
		{
			_marioMenuY += MENU_INCREASE;
			if (_marioMenuY > MENU_MAX)
				_marioMenuY = MENU_MIN;
		}
		else if (_keyboard->KeyPress(DIK_UP))
		{
			_marioMenuY -= MENU_INCREASE;
			if (_marioMenuY < MENU_MIN)
				_marioMenuY = MENU_MAX;
		}
		else if (_keyboard->KeyPress(DIK_RETURN))
		{
			if (_marioMenuY == MENU_MIN)
			{
				_audio->PlaySound(_sound_Squish);
				ChangeMap(1);
				ChangeState(GS_REPLAY);
			}
			else
				ChangeState(GS_WIN);
		}
		break;

	case GS_PLAYING:
		if (_keyboard->KeyPress(DIK_Q))
			PostQuitMessage(0);
		break;
	case GS_WIN: case GS_GAMEOVER:
		if (_keyboard->KeyDown(DIK_RETURN) || _keyboard->KeyDown(DIK_ESCAPE))
			ChangeState(GS_MENU);
	}
}

//Load Resources
void CGameMario::LoadAudio()
{
	_sound_1up = _audio->LoadSound("Sounds\\1up.wav");
	_sound_Beep = _audio->LoadSound("Sounds\\Beep.wav");
	_sound_BigJump = _audio->LoadSound("Sounds\\BigJump.wav");
	_sound_BowserDie = _audio->LoadSound("Sounds\\Bowser.wav");
	_sound_Break = _audio->LoadSound("Sounds\\Break.wav");
	_sound_Bump = _audio->LoadSound("Sounds\\Bump.wav");
	_sound_Coin = _audio->LoadSound("Sounds\\Coin.wav");
	_sound_Die = _audio->LoadSound("Sounds\\Die.wav");
	_sound_EnemyFire = _audio->LoadSound("Sounds\\EnemyFire.wav");
	_sound_FireBall = _audio->LoadSound("Sounds\\FireBall.wav");
	_sound_Flagpole = _audio->LoadSound("Sounds\\Flagpole.wav");
	_sound_GameOver = _audio->LoadSound("Sounds\\GameOver.wav");
	_sound_Item = _audio->LoadSound("Sounds\\Item.wav");
	_sound_Jump = _audio->LoadSound("Sounds\\Jump.wav");
	_sound_Kick = _audio->LoadSound("Sounds\\Kick.wav");
	_sound_Pause = _audio->LoadSound("Sounds\\Pause.wav");
	_sound_Powerup = _audio->LoadSound("Sounds\\Powerup.wav");
	_sound_Skid = _audio->LoadSound("Sounds\\Skid.wav");
	_sound_Squish = _audio->LoadSound("Sounds\\Squish.wav");
	_sound_Thwomp = _audio->LoadSound("Sounds\\Thwomp.wav");
	_sound_Vine = _audio->LoadSound("Sounds\\Vine.wav");
	_sound_Warp = _audio->LoadSound("Sounds\\Warp.wav");
	_sound_Background = _audio->LoadSound("Sounds\\Background.wav");
}
void CGameMario::LoadSprite()
{
	// Mario
	_sprites[S_BMARIO_LEFT] = new CSprite(_SpriteHandler, BMARIO_IMAGE_LEFT, 16, 32, 32, 8, TIMEPERIMAGE); // fixed
	_sprites[S_BMARIO_RIGHT] = new CSprite(_SpriteHandler, BMARIO_IMAGE_RIGHT, 16, 32, 32, 8, TIMEPERIMAGE);
	_sprites[S_SMARIO_RIGHT] = new CSprite(_SpriteHandler, SMARIO_IMAGE_RIGHT, 17, 16, 8, 8, TIMEPERIMAGE);
	_sprites[S_SMARIO_LEFT] = new CSprite(_SpriteHandler, SMARIO_IMAGE_LEFT, 17, 16, 8, 8, TIMEPERIMAGE);
	_sprites[S_EXPLOSION] = new CSprite(_SpriteHandler, S_EXPLOSION_IMAGE, 16, 16, 3, 3, TIMEPERIMAGE);
	_sprites[S_FIREBULLET] = new CSprite(_SpriteHandler, FIREBULLET_IMAGE, 8, 8, 4, 4, TIMEPERIMAGE);
	//Static Object
	_sprites[S_FLAG] = new CSprite(_SpriteHandler, FLAG_IMAGE, 16, 16, 4, 2, TIMEPERIMAGE);
	_sprites[S_BRICK] = new CSprite(_SpriteHandler, BRICK_IMAGE, 16, 16, 16, 4, TIMEPERIMAGE);
	_sprites[S_PIPE] = new CSprite(_SpriteHandler, PIPE_IMAGE, 16, 17, 8, 4, TIMEPERIMAGE);
	_sprites[S_CASTLE] = new CSprite(_SpriteHandler, CASTLE_IMAGE, 40, 40, 4, 2, TIMEPERIMAGE);
	_sprites[S_CLOUD] = new CSprite(_SpriteHandler, CLOUD_IMAGE, 8, 24, 4, 4, TIMEPERIMAGE);
	_sprites[S_GRASS] = new CSprite(_SpriteHandler, GRASS_IMAGE, 8, 16, 8, 4, TIMEPERIMAGE);
	_sprites[S_MOUNTAIN] = new CSprite(_SpriteHandler, MOUNTAIN_IMAGE, 40, 17.5, 4, 2, TIMEPERIMAGE);
	//Enemies
	_sprites[S_GOOMBA] = new CSprite(_SpriteHandler, GOOMBA_IMAGE, 16, 16, 6, 6, TIMEPERIMAGE);
	_sprites[S_KOOPA] = new CSprite(_SpriteHandler, KOOPA_IMAGE, 16, 24, 4, 4, TIMEPERIMAGE);
	_sprites[S_PIRHANA] = new CSprite(_SpriteHandler, PIRHANA_IMAGE, 16, 16, 2, 2, TIMEPERIMAGE);
	//Items
	_sprites[S_FLOWER] = new CSprite(_SpriteHandler, FLOWER_IMAGE, 16, 16, 4, 4, TIMEPERIMAGE);
	_sprites[S_FUNGI] = new CSprite(_SpriteHandler, FUNGI_IMAGE, 16, 16, 2, 2, TIMEPERIMAGE);
	_sprites[S_MONEY] = new CSprite(_SpriteHandler, MONEY_IMAGE, 16, 16, 7, 7, TIMEPERIMAGE);
	_sprites[S_NUMBER] = new CSprite(_SpriteHandler, NUMBER_IMAGE, 16, 16, 10, 10, TIMEPERIMAGE);
	//Others
	_sprites[S_STAR] = new CSprite(_SpriteHandler, STAR_IMAGE, 16, 16, 4, 4, 1);
}
void CGameMario::ChangeMap(int Map)
{
	_timeGame = 300;
	_Map = Map;
	switch (_Map)
	{
	case 1:
		ReadMap("Map\\MAP1.ptl", false , this);
		break;
	case 2:
		ReadMap("Map\\MAP2.ptl", false, this);
		break;
	}
	if (_Map<=2)
		ChangeState(GS_PLAYING);
	else ChangeState(GS_WIN);
}
void CGameMario::test()
{
	BaseObject* obj;
	list<BaseObject*>::iterator i;
	for (i = dynamicObjs.begin(); i != dynamicObjs.end(); i++)
	{
		obj = *i;
		if (obj->_ID == 1)
		{
			text = to_string(obj->getPosition().y);
			StringToWString(ws, text);
			DrawTxt(ws, 330, 300, _font);
		}
	}
	
}
void CGameMario::DrawScore()
{
	// Draw money
	DrawTxt(L"WORLD 1.", 450, 20, _font);
	text = to_string(_Map);
	StringToWString(ws, text);
	DrawTxt(ws, 552, 20, _font);
	DrawTxt(L"MONEY", 224, 20, _font);
	// draw Time
	if (_timeGame > 0)
		text = to_string(_timeGame);
	else
		text = "0";
	StringToWString(ws, text);
	DrawTxt(ws, 730, 20, _font);
	DrawTxt(L"TIME", 650, 20, _font);
	// draw score coin
	text = to_string(_coin);
	StringToWString(ws, text);
	DrawTxt(ws, 330, 20, _font);
	DrawTxt(L"MONEY", 224, 20, _font);

	// Draw life
	if (_life > 0)
		text = to_string(_life);
	else
		text = "0";
	StringToWString(ws, text);
	DrawTxt(ws, 95, 20, _font);
	DrawTxt(L"LIFE x", 24, 20, _font);
}
void CGameMario::ChangeState(char state)
{
	_state = state;
	switch (state)
	{
	case GS_PLAYING: 
		_camera->_cameraX = 0;
		staticObjs.clear();
		dynamicObjs.clear();
		break;
	case GS_WIN:
		break;
	}
}
void CGameMario::ReplayandStartGame(LPDIRECT3DDEVICE9 d3ddv)
{
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
	DrawScore();
	if (_Map == 1)
		DrawTxt(L"WORLD 1.1", 360, 300, _font);
	else if (_Map == 2)
		DrawTxt(L"WORLD 1.2", 360, 300, _font);
	else
		DrawTxt(L"WORLD", 360, 300, _font);
}
CGameMario::~CGameMario()
{
	delete _audio;
	delete _camera;
	if (_quadTree != NULL)
		delete _quadTree;
	for (int i = 0; i < 30; i++)
	if (_sprites[i] != NULL) delete _sprites[i];
}

void CGameMario::AddScore(int score, float _x, float _y)
{
	_score += score;
	isDrawEat = true;
	reX = _x;
	reY = _y;
}
void CGameMario::DrawEat()
{
	if (isDrawEat)
	{
		distanceMove -= 1;
		string text = to_string(_score);
		wstring ws;
		StringToWString(ws, text);
		DrawTxt(ws, reX, reY,_font);
		if (distanceMove < -100)
		{
			isDrawEat = false;
			distanceMove = 0;
		}
			
	}
}