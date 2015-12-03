//Framework ----------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h>
#include "Game.h"
#include "Graphic.h"
#include "Sprite.h"
#include "Animation.h"
#include <stdio.h>
#include "Global.h"
#include "Map.h"
#include <conio.h>
#include <stdio.h>
#include "Castle.h"

//--------------------------------


#include <list>
using namespace std;
Game::Game(HWND hWnd, HINSTANCE hInstance)
{
	//Framework ----------------------
	_hWnd=hWnd;
	_hInstance=hInstance;
	_input = new Input(_hWnd, _hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);
	_g=new Graphic(_hWnd);
	_timeManager = new TimeManager();
	_audio = new Audio(_hWnd);
	//-----------------------------------

	//GAME STATE ---------------------
	_state = MS_MENU;
	_xMenu = 200;
	_yMenu = YMENU_MIN;
	//--------------------------------
	
	D3DXCreateFont(_g->device,30,0,FW_BOLD,0,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,TEXT("Arial"),&_fontArial);
	srand((unsigned)(time(NULL)));
	_bgMenu = _g->CreateSurface("Image\\imgbgMenu.png");
	for (int i = 0; i < 5; i++) _sprites[i] = NULL;

	LoadSprite();
	LoadAudio();
	_camera = new Camera(0, 0, 800, 600);

	
	////LoadMap();
	//LoadResource::LoadResource(_a);
	//

}
void Game::LoadSprite()
{
	_sprites[S_SMARIO] = new Sprite(_g, "Image\\SmallMario.png");
	_sprites[S_BMARIO] = new Sprite(_g, "Image\\BigMario.png");
	_sprites[S_PIPE] = new Sprite(_g, "Image\\Pipe.bmp");
	_sprites[S_CASTLE] = new Sprite(_g, "Image\\gach.png");
	_sprites[S_BACKGROUND] = new Sprite(_g, "Image\\imgWorld111.png");
	_marioMenu = new Sprite(_g, "Image\\imgSmallMario.png");
}
void Game::LoadAudio()
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
void Game::LoadMap()
{
	FILE * pFile;
	int i = 0, j = 0;
	pFile = fopen("1.ptl", "r");
	long a[100][1000];

	char ch;
	string s = "";
	if (pFile == NULL)
	{
		printf("File ko ton tai");
		return;
	}
	bool kt = true;
	while (EOF != (ch = getc(pFile)))

	{
		if (ch != ' ' && ch != '\n')
		{
			s = s + ch;
			if (kt == true)
			{
				j++;
				kt = false;
			}
		}

		if (' ' == ch)
		{
			a[i][j - 1] = atoi(s.c_str());
			s = "";
			kt = true;
		}
		if ('\n' == ch)
		{
			a[i][j] = atoi(s.c_str());
			m = j;
			j = 0;
			i++;
			s = "";
			kt = true;
		}

	}
	n = i;


	int pixel = 8;
	for (int k = 0; k < n; k++)
	{
		for (int l = 0; l < m; l++)
		{
			switch (a[i][j])
			{
				case 0:
					break;
				default:
					_staticObjs[k][l] = new Castle( 8* (k + 1), 8* (l + 1), 0, 0, 0, _sprites[S_CASTLE]);
					break;
			}
		}
	}
	fclose(pFile);
}
void Game::GameRun()
{
	_timeManager->LimitFPS(60);
	_TPF = _timeManager->TPF;
	_input->GetMouse();
	_input->GetKey();
	Update();
	Render();
}
void Game::ProcessInput()
{
	switch (_state)
	{
	case MS_MENU:
		if (_input->KeyDown(DIK_Q))
			PostQuitMessage(0);
		else if (_input->KeyPress(DIK_DOWN))
		{
			_yMenu += YMENU;
			if (_yMenu > YMENU_MAX)
				_yMenu = YMENU_MIN;
		}
		else if (_input->KeyPress(DIK_UP))
		{
			_yMenu -= YMENU;
			if (_yMenu < YMENU_MIN)
				_yMenu = YMENU_MAX;
		}
		_audio->PlaySound(_sound_GameOver);
		break;
		
	case MS_PLAYING:
		break;
	}
}
void Game::Update()
{
	BaseObject* _obj;
	list<BaseObject*>::iterator i;
	ProcessInput();
}
void Game::Render()
{
	_g->device->BeginScene();
	_g->spriteDX->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	_g->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); 
	switch (_state)
	{
		case MS_MENU:
			_g->device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0); 
			GameMenu();
			break;
	}
	_g->spriteDX->End();
	_g->device->EndScene();
	_g->device->Present(NULL,NULL,NULL,NULL);
}

//Choose menu
void Game::GameMenu()
{
	_g->device->StretchRect(_bgMenu, NULL, _g->backBuffer, NULL, D3DTEXF_NONE);
	_recMenu.top = 16;
	_recMenu.left = 102;
	_recMenu.right = 120;
	_recMenu.bottom = 32;
	_marioMenu->Draw(_xMenu, _yMenu, 2, 2, _recMenu, 1);
}
Game::~Game()
{
	delete _g;
	delete _audio;
	delete _input;
	delete _timeManager;
}


