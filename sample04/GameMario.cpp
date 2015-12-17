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

CGameMario::CGameMario(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate):
CGame(hInstance,Name,Mode,IsFullScreen, FrameRate)
{
	//Framework............................
	
	_camera = new Camera(0,0,800,600);
	_keyboard = new KeyBoard(_hWnd, hInstance);
	//--------------------------------------
	for (int i = 0; i < 20; i++)
		_sprites[i] = NULL;
	_quadTree = NULL;
	_marioMenuY = MENU_MIN;
	_marioMenuX = 100;
	_timeGame = 300;
}

void CGameMario::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	_audio = new Audio(_hWnd);
	srand((unsigned)time(NULL));
	D3DXCreateSprite(d3ddv,&_SpriteHandler);
	HRESULT res = D3DXCreateSprite(_d3ddv,&_SpriteHandler);
	D3DXCreateFont(_d3ddv, 30, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("SuperMarioBros"), &_fontArial);
	
	LoadSprite();
	LoadAudio();

	_state = _curState =  GS_MENU;
	wait1Sec = 0;
	
	//MenuGame
	_marioMenu = new CSprite(_SpriteHandler, "Image\\imgOptionCursor.png", 8, 8, 1, 1);
	_title = CreateSurface("Image\\imgbgMenu.png", d3ddv);
	_mario = new Mario(0, 0, _camera->_cameraX, _camera->_cameraY, 0, _sprites[S_SMARIO]);
	
	
	 //Example about Enemies
	//_dynamicObjs[0] = new Goomba(200, 180, _camera->_cameraX, _camera->_cameraY, 0, _sprites[S_GOOMBA]);
	//_dynamicObjs[1] = new Koopa(300, 180, _camera->_cameraX, _camera->_cameraY, 0, _sprites[S_KOOPA]);
}

void CGameMario::UpdateWorld(float TPF)
{
	BaseObject* _obj;
	list<BaseObject*>::iterator i;
	switch (_state)
	{
		case GS_PLAYING:
			
			wait1Sec += TPF;
			if (wait1Sec>1)
			{
				wait1Sec -= 1;
				_timeGame--;
			}
			staticObjs.clear();
			dynamicObjs.clear();
			_quadTree->GetBaseObjectsFromCamera(_camera->_rect, &staticObjs, &dynamicObjs);
			_camera->Update(_mario, _quadTree);
			_mario->Update(TPF, &staticObjs);
			break;
		case GS_GAMEOVER:
			_audio->PlaySound(_sound_GameOver);
	}
		
}
void CGameMario::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float TPF)
{
	BaseObject* obj;
	list<BaseObject*>::iterator i;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	switch (_state)
	{
		case GS_MENU:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
			_marioMenu->Render(_marioMenuX, _marioMenuY, _camera->_cameraX, _camera->_cameraY, 1);
			staticObjs.clear();
			d3ddv->StretchRect(_title, NULL, _BackBuffer, NULL, D3DTEXF_NONE);
			break;
		case GS_PLAYING:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
			////_writer->DrawTextAdvanced(L"YOU WON !", 100, 300, 800, 200, D3DCOLOR_XRGB(255, 255, 255), _fontArial);
			DrawNumber(_sprites[S_NUMBER], _timeGame, 150, 20, 0, 0);
			for (i = staticObjs.begin(); i != staticObjs.end(); i++)
			{
				obj = *i;
				if (obj->getPosition().x>_camera->_cameraX - 800 && obj->getPosition().x<_camera->_cameraX + WIDTH + 10)
					obj->Render();
			}

			//Render things
			//_dynamicObjs[0]->Render();
			//_dynamicObjs[1]->Render();
			_mario->Render();
			break;
		case GS_GAMEOVER:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
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
			_audio->PlaySound(_sound_Squish);
			ChangeMap(1);
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
	// Mario
	_sprites[S_BMARIO] = new CSprite(_SpriteHandler, BMARIO_IMAGE, 16, 32, 32, 8); // fixed
	_sprites[S_SMARIO] = new CSprite(_SpriteHandler, SMARIO__IMAGE, 17, 16, 8, 8);
	_sprites[S_EXPLOSION] = new CSprite(_SpriteHandler, S_EXPLOSION_IMAGE, 16, 16, 3, 3);
	_sprites[S_FIREBULLET] = new CSprite(_SpriteHandler, FIREBULLET_IMAGE, 8, 8, 4, 4);
	//Static Object
	_sprites[S_FLAG] = new CSprite(_SpriteHandler, FLAG_IMAGE, 32, 32, 2, 2);
	_sprites[S_BRICK] = new CSprite(_SpriteHandler, BRICK_IMAGE, 16, 16, 16, 4);
	_sprites[S_PIPE] = new CSprite(_SpriteHandler, PIPE_IMAGE, 16, 17, 8, 4);
	//Enemies
	_sprites[S_GOOMBA] = new CSprite(_SpriteHandler, GOOMBA_IMAGE, 16, 16, 6, 6);
	_sprites[S_KOOPA] = new CSprite(_SpriteHandler, KOOPA_IMAGE, 16, 24, 4, 4);
	_sprites[S_PIRHANA] = new CSprite(_SpriteHandler, PIRHANA_IMAGE, 16, 16, 2, 2);
	//Items
	_sprites[S_FLOWER] = new CSprite(_SpriteHandler, FLOWER_IMAGE, 16, 16, 4, 4);
	_sprites[S_FUNGI] = new CSprite(_SpriteHandler, FUNGI_IMAGE, 16, 16, 2, 2);
	_sprites[S_MONEY] = new CSprite(_SpriteHandler, MONEY_IMAGE, 16, 16, 7, 7);
	_sprites[S_NUMBER] = new CSprite(_SpriteHandler, NUMBER_IMAGE, 15, 16, 10, 10);
	//Others
	_sprites[S_STAR] = new CSprite(_SpriteHandler, STAR_IMAGE, 16, 16, 4, 4);
}
void CGameMario::ChangeMap(int Map)
{
	_timeGame = 300;
	_Map = Map;
	switch (_Map)
	{
	case 1:
		ReadMap("Map\\MAP1.ptl", true, this);
		//ReadMap("Map\\Test.mm",true,this);
		break;
	
	}
}

CGameMario::~CGameMario()
{
	delete _audio;
	delete _camera;
	if (_quadTree != NULL) 
		delete _quadTree;
	for (int i = 0; i<20; i++)
		if (_sprites[i] != NULL) delete _sprites[i];
}