#include <time.h>
#include <d3dx9.h>
#include "GameMario.h"
#include "utils.h"
#include "Brick.h"
#include <string>
#include <string.h>
#include "Global.h"
#include "Mario.h"
#include "Writer.h"
#define MENU_MAX 170
#define MENU_MIN  149
#define MENU_INCREASE 17
KeyBoard* _keyboard = NULL;

CGameMario::CGameMario(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate):
CGame(hInstance,Name,Mode,IsFullScreen, FrameRate)
{
	//Framework............................
	_audio = new Audio(_hWnd);
	_camera = new Camera();
	_keyboard = new KeyBoard(_hWnd, hInstance);
	//--------------------------------------
	for (int i = 0; i < 20; i++)
		_sprites[i] = NULL;
	
	_marioMenuY = MENU_MIN;
	_marioMenuX = 100;
	
}

CGameMario::~CGameMario()
{
	delete _audio;
	delete _camera;
}

void CGameMario::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));
	D3DXCreateSprite(d3ddv,&_SpriteHandler);
	HRESULT res = D3DXCreateSprite(_d3ddv,&_SpriteHandler);
	D3DXCreateFont(_d3ddv, 30, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("SuperMarioBros"), &_fontArial);
	
	LoadSprite();
	//LoadMap();
	LoadAudio();
	_state = _curState =  GS_MENU;
	wait1Sec = 0;

	//MenuGame
	_marioMenu = new CSprite(_SpriteHandler, "Image\\imgOptionCursor.png", 8, 8, 1, 1);
	_title = CreateSurface("Image\\imgbgMenu.png", d3ddv);

	_mario = new Mario(0, 180, _camera->_cameraX, _camera->_cameraY, 0, _sprites[S_SMARIO]);
	_testBrick2 = new Brick(180, 150, _camera->_cameraX, _camera->_cameraY, 5, _sprites[S_BRICK]);
	_testBrick = new Brick(180, 180, _camera->_cameraX, _camera->_cameraY, 5, _sprites[S_BRICK]);
	ReadMap("a", true, this);
}

void CGameMario::UpdateWorld(int t)
{
	switch (_state)
	{
		case GS_MENU:
			//if (isLoad == false)
				//ChangeMap(1,isLoad);
			break;
		case GS_PLAYING:

			wait1Sec += 0.05;
			if (wait1Sec>1)
			{
				wait1Sec -= 1;
				_timeGame--;
			}
			_mario->CollisionTemp(_testBrick);
			_mario->Update(t);
			break;
	}
		
}
void CGameMario::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	BaseObject* obj;
	list<BaseObject*>::iterator i;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (_state)
	{
		case GS_MENU:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
			_marioMenu->Render(_marioMenuX, _marioMenuY, _camera->_cameraX, _camera->_cameraY, 1);
			d3ddv->StretchRect(_title, NULL, _BackBuffer, NULL, D3DTEXF_NONE);
			break;
		case GS_PLAYING:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
			_audio->PlaySound(_sound_GameOver);
			_camera->Update(_mario);
			//_writer->DrawTextAdvanced(L"YOU WON !", 100, 300, 800, 200, D3DCOLOR_XRGB(255, 255, 255), _fontArial);
			DrawNumber(_sprites[S_NUMBER], _timeGame, 150, 20, 0, 0);
			for (i = staticObjs.begin(); i != staticObjs.end(); i++)
			{
				obj = *i;
				obj->Render();
			}
			_mario->Render();
			_testBrick->Render();
			_testBrick2->Render();
			break;
		case GS_GAMEOVER:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
			break;
	}
	_SpriteHandler->End();
}

void CGameMario::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
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
			if (_marioMenuY = MENU_MIN)
				_state = GS_PLAYING;
			else if (_marioMenuY = MENU_MAX)
				_state = GS_PLAYING;
		}
		break;

	case GS_PLAYING:
		_mario->ProcessInput(_keyboard);
		if (_keyboard->KeyPress(DIK_Q))
			PostQuitMessage(0);
		break;
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
}
void CGameMario::LoadSprite()
{
	_sprites[S_GOOMBA] = new CSprite(_SpriteHandler, GOOMBA_IMAGE, 16, 16, 6, 6);
	_sprites[S_BMARIO] = new CSprite(_SpriteHandler, BMARIO_IMAGE, 16, 32, 8, 8);
	_sprites[S_BRICK] = new CSprite(_SpriteHandler, BRICK_IMAGE, 16, 16, 1, 1);
	_sprites[S_EXPLOSION] = new CSprite(_SpriteHandler, S_EXPLOSION_IMAGE, 16, 16, 3, 3);
	_sprites[S_FIREBULLET] = new CSprite(_SpriteHandler, FIREBULLET_IMAGE, 8, 8, 4, 4);
	_sprites[S_FLAG] = new CSprite(_SpriteHandler, FLAG_IMAGE, 32, 32, 2, 2);
	_sprites[S_FLOWER] = new CSprite(_SpriteHandler, FLOWER_IMAGE, 16, 16, 4, 4);
	_sprites[S_FUNGI] = new CSprite(_SpriteHandler, FUNGI_IMAGE, 16, 16, 2, 2);
	_sprites[S_KOOPA] = new CSprite(_SpriteHandler, KOOPA_IMAGE, 16, 16, 4, 4);
	_sprites[S_MONEY] = new CSprite(_SpriteHandler, MONEY_IMAGE, 16, 16, 7, 7);
	_sprites[S_NUMBER] = new CSprite(_SpriteHandler, NUMBER_IMAGE, 16, 16, 10, 10);
	_sprites[S_PIPE] = new CSprite(_SpriteHandler, PIPE_IMAGE, 16, 16, 4, 4);
	_sprites[S_PIRHANA] = new CSprite(_SpriteHandler, PIRHANA_IMAGE, 16, 16, 2, 2);
	_sprites[S_SMARIO] = new CSprite(_SpriteHandler, SMARIO__IMAGE, 17, 16, 8, 8);
	_sprites[S_STAR] = new CSprite(_SpriteHandler, STAR_IMAGE, 16, 16, 4, 4);
}
void CGameMario::ChangeMap(int Map, bool sLoad)
{
	_timeGame = 300;
	_Map = Map;
	isLoad = sLoad;
	switch (_Map)
	{
	case 1:
		ReadMap("Map\\World1-1.mm", true, this);
		//ReadMap("Map\\Test.mm",true,this);
		break;
	case 2:
		ReadMap("Map\\World1-2.mm", false, this);
		break;
	case 3:
		ReadMap("Map\\World1-3.mm", true, this);
		break;
	}
	isLoad = false;
	//if (_Map<4)
	//	ChangeState(GS_PLAYING);
	//else ChangeState(GS_WIN);
}

