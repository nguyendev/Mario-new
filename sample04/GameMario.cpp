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
	_camera = new Camera(0, 0, 800, 600);
	_keyboard = new KeyBoard(_hWnd, hInstance);
	//--------------------------------------
	for (int i = 0; i < 30; i++)
		_sprites[i] = NULL;
	_quadTree = NULL;
	_marioMenuY = MENU_MIN;
	_marioMenuX = 100;
	_life = 3;
	_coin = 120;
	_replay = 0;
}

void CGameMario::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	_audio = new Audio();
	_audio->initialize(_hWnd);
	srand((unsigned)time(NULL));
	D3DXCreateSprite(d3ddv, &_SpriteHandler);
	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);
	D3DXCreateFont(_d3ddv, 25, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Time New Roman"), &_font);
	LoadSprite();
	LoadAudio();

	_state = _curState = GS_MENU;
	wait1Sec = 0;

	//MenuGame
	_marioMenu = new CSprite(_SpriteHandler, "Image\\imgOptionCursor.png", 8, 8, 1, 1, 0.2);
	_title = CreateSurface("Image\\imgbgMenu.png", d3ddv);


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
		_audio->PlaySoundA(_sound_Background);
		wait1Sec += TPF;
		if (wait1Sec>1)
		{
			wait1Sec -= 1;
			_timeGame--;
		}
		for (i = staticObjs.begin(); i != staticObjs.end(); i++)
		{
			_obj = *i;
			//if (_obj->getPosition().x->x - 10 && obj->x<camera->x + WIDTH + 10)
			_obj->Update(TPF, &staticObjs, &dynamicObjs, _keyboard);
			/*if (_obj->getStatusOBject() == StatusObject::DEAD)
				_quadTree->DeleteObj(_obj, true);*/
		}
		for (i = dynamicObjs.begin(); i != dynamicObjs.end(); i++)
		{
			_obj = *i;
			_obj->Update(TPF, &staticObjs, &dynamicObjs, _keyboard);
			/*if (_obj->getStatusOBject() == StatusObject::DEAD)
				_quadTree->DeleteObj(_obj, true);*/
		}
		
		staticObjs.clear();
		dynamicObjs.clear();
		_quadTree->GetBaseObjectsFromCamera(_camera->_rect, &staticObjs, &dynamicObjs);
		_camera->Update(_quadTree);
		break;
	case GS_NEXT_STAGE:				//Khi đổi màn
		ChangeMap(_Map + 1);
		break;
	case GS_REPLAY:	
		_replay += TPF;
		if (_replay > 2)
		{
			_replay = 0;
			
			ChangeMap(_Map);
		}
		break;
	case GS_GAMEOVER:
		_audio->PlaySound(_sound_GameOver);
	}
	if (_timeGame == 0);
		

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
		DrawScore();
		for (i = staticObjs.begin(); i != staticObjs.end(); i++)
		{
			obj = *i;
			if (obj->getPosition().x>_camera->_cameraX - 800 && obj->getPosition().x<_camera->_cameraX + WIDTH + 10)
				obj->Render();
		}
		for (i = dynamicObjs.begin(); i != dynamicObjs.end(); i++)
		{
			obj = *i;
			if (obj->getPosition().x>_camera->_cameraX - 800 && obj->getPosition().x<_camera->_cameraX + WIDTH + 10)
				obj->Render();
		}
		break;
	case GS_REPLAY:
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
		DrawScore();
		if (_Map == 1)
			DrawTxt(L"WORLD 1.1", 360, 300, _font);
		else if (_Map == 2)
			DrawTxt(L"WORLD 1.2", 360, 300, _font);
		else
			DrawTxt(L"WORLD", 360, 300, _font);
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
		//_mario->ProcessInput(_keyboard);
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
	_sound_Background = _audio->LoadSound("Sounds\\Background.wav");
}
void CGameMario::LoadSprite()
{
	// Mario
	_sprites[S_BMARIO_LEFT] = new CSprite(_SpriteHandler, BMARIO_IMAGE_LEFT, 16, 32, 32, 8, 0.1); // fixed
	_sprites[S_BMARIO_RIGHT] = new CSprite(_SpriteHandler, BMARIO_IMAGE_RIGHT, 16, 32, 32, 8, 0.1);
	_sprites[S_SMARIO_RIGHT] = new CSprite(_SpriteHandler, SMARIO_IMAGE_RIGHT, 17, 16, 8, 8, 0.1);
	_sprites[S_SMARIO_LEFT] = new CSprite(_SpriteHandler, SMARIO_IMAGE_LEFT, 17, 16, 8, 8, 0.1);
	_sprites[S_EXPLOSION] = new CSprite(_SpriteHandler, S_EXPLOSION_IMAGE, 16, 16, 3, 3, 0.2);
	_sprites[S_FIREBULLET] = new CSprite(_SpriteHandler, FIREBULLET_IMAGE, 8, 8, 4, 4, 0.2);
	//Static Object
	_sprites[S_FLAG] = new CSprite(_SpriteHandler, FLAG_IMAGE, 16, 16, 4, 2, 0.2);
	_sprites[S_BRICK] = new CSprite(_SpriteHandler, BRICK_IMAGE, 16, 16, 16, 4, 0.2);
	_sprites[S_PIPE] = new CSprite(_SpriteHandler, PIPE_IMAGE, 16, 17, 8, 4, 0.2);
	_sprites[S_CASTLE] = new CSprite(_SpriteHandler, CASTLE_IMAGE, 80, 80, 1, 1, 0.2);
	_sprites[S_CLOUD] = new CSprite(_SpriteHandler, CLOUD_IMAGE, 8, 24, 4, 4, 0.2);
	_sprites[S_GRASS] = new CSprite(_SpriteHandler, GRASS_IMAGE, 8, 16, 8, 4, 0.2);
	_sprites[S_MOUNTAIN] = new CSprite(_SpriteHandler, MOUNTAIN_IMAGE, 40, 17.5, 4, 2, 0.2);
	//Enemies
	_sprites[S_GOOMBA] = new CSprite(_SpriteHandler, GOOMBA_IMAGE, 16, 16, 6, 6, 0.2);
	_sprites[S_KOOPA] = new CSprite(_SpriteHandler, KOOPA_IMAGE, 16, 24, 4, 4, 0.2);
	_sprites[S_PIRHANA] = new CSprite(_SpriteHandler, PIRHANA_IMAGE, 16, 16, 2, 2, 0.2);
	//Items
	_sprites[S_FLOWER] = new CSprite(_SpriteHandler, FLOWER_IMAGE, 16, 16, 4, 4, 0.2);
	_sprites[S_FUNGI] = new CSprite(_SpriteHandler, FUNGI_IMAGE, 16, 16, 2, 2, 0.2);
	_sprites[S_MONEY] = new CSprite(_SpriteHandler, MONEY_IMAGE, 16, 16, 7, 7, 0.2);
	_sprites[S_NUMBER] = new CSprite(_SpriteHandler, NUMBER_IMAGE, 16, 16, 10, 10, 0.2);
	//Others
	_sprites[S_STAR] = new CSprite(_SpriteHandler, STAR_IMAGE, 16, 16, 4, 4, 0.2);
}
void CGameMario::ChangeMap(int Map)
{
	_timeGame = 10;
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
	if (_Map<4)
		ChangeState(GS_PLAYING);
	else ChangeState(GS_WIN);
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
int StringToWString(std::wstring &ws, const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}
void CGameMario::DrawScore()
{
	
	// dòng một
	wstring ws;
	string text;
	DrawTxt(L"MARIO", 24, 8, _font);
	DrawTxt(L"WORLD", 400, 8, _font);
	DrawTxt(L"TIME", 600, 8, _font);
	// dòng hai
	// draw Time
	if (_timeGame > 0)
		text = to_string(_timeGame);
	else
		text = "0";
	StringToWString(ws, text);
	DrawTxt(ws, 606, 30, _font);

	//// draw score coin
	text = to_string(_coin);
	StringToWString(ws, text);
	DrawTxt(ws, 224, 30, _font);

	text = to_string(_life);
	StringToWString(ws, text);
	DrawTxt(ws, 30, 30, _font);
	//while (text.length() < 2)
	//	text = "0" + text;
	//text = "x" + text;
	//DrawText(wstring(text.begin(), text.end()), Vector2(95, 18));
	//// draw time of state
	//text = to_string(m_timeOfState);
	//DrawText(wstring(text.begin(), text.end()), Vector2(200, 18));
}
void CGameMario::ChangeState(char state)
{
	_state = state;
	switch (state)
	{
	case GS_PLAYING:
		//a->PlaySound(sBackground); 
		_camera->_cameraX = 0;
		staticObjs.clear();
		dynamicObjs.clear();
		break;
	case GS_WIN:
		//a->PlaySound(sWinState);
		break;
	}
}