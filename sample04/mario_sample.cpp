#include <time.h>
#include <d3dx9.h>
#include "mario_sample.h"
#include "utils.h"
#include "Brick.h"
#include "Cloud.h"
#include <string>
#include <string.h>
#include "Global.h"
#include "Mario.h"

#define MENU_MAX 160
#define MENU_MIN  148




CMarioSample::CMarioSample(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate):
CGame(hInstance,Name,Mode,IsFullScreen, FrameRate)
{
	_col = new Collision();
	_audio = new Audio(_hWnd);
	_camera = new Camera();
	_writer = new Writer();
	_keyboard = new KeyBoard(_hWnd, hInstance);
	for (int i = 0; i < 20; i++)
		_sprites[i] = NULL;
	_marioMenuY = 148;
	_marioMenuX = 100;
}

CMarioSample::~CMarioSample()
{
	delete _audio;
	delete _camera;
	delete _writer;
	delete _col;
}

void CMarioSample::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));
	D3DXCreateSprite(d3ddv,&_SpriteHandler);
	HRESULT res = D3DXCreateSprite(_d3ddv,&_SpriteHandler);

	
	D3DXCreateFont(_d3ddv, 30, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("SuperMarioBros"), &_fontArial);
	
	LoadSprite();
	LoadMap();
	LoadAudio();
	mario = new Mario(0, 180, _camera->_cameraX, _camera->_cameraY, 0, _sprites[S_SMARIO]);
	testBrick2 = new Brick(180, 150, _camera->_cameraX, _camera->_cameraY, 0, _sprites[S_BRICK]);
	testBrick = new Brick(180, 180, _camera->_cameraX, _camera->_cameraY, 0, _sprites[S_BRICK]);
	_marioMenu = new CSprite(_SpriteHandler, "Image\\imgOptionCursor.png", 8, 8, 1, 1);
	_state = GS_MENU;
	timegame = 300; 
	wait1Sec = 0;
	_title  =   _writer->CreateSurface("Image\\imgbgMenu.png", d3ddv);
}

void CMarioSample::UpdateWorld(int t)
{
		wait1Sec += 0.05;
		if (wait1Sec>1)
		{
			wait1Sec -= 1;
			timegame--;
		}
		//CollisionHanding();
		mario->Update(t);
}
void CMarioSample::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (_state)
	{
		case GS_MENU:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
			RenderMenu(d3ddv);
			
			break;
		case GS_PLAYING:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
			_audio->PlaySound(_sound_GameOver);
			_camera->Update(mario);
			//_writer->DrawTextAdvanced(L"YOU WON !", 100, 300, 800, 200, D3DCOLOR_XRGB(255, 255, 255), _fontArial);
			_writer->DrawNumber(_sprites[S_NUMBER], timegame, 150, 20, 0, 0);
			for (int i = 0; i < _countI; i++)
			{
				//D3DXCOLOR(1, 0, 0, 1)
				//_staticObjs[i]->_cameraX = _camera->_cameraX;
				_staticObjs[i]->Render();
			}
			mario->Render();
			testBrick->Render();
			testBrick2->Render();
			break;
		case GS_GAMEOVER:
			d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0);
			break;
	}
	_SpriteHandler->End();
}

void CMarioSample::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	switch (_state)
	{
	case GS_MENU:
		if (IsKeyDown(DIK_Q))
			PostQuitMessage(0);
		else if (IsKeyDown(DIK_DOWN))
		{
			_marioMenuX += 40;
			if (_marioMenuY >= MENU_MAX)
			{
				_marioMenuY = MENU_MIN;
			}
		}
		else if (IsKeyDown(DIK_UP))
		{
			_marioMenuY -= 40;
			if (_marioMenuY <= MENU_MIN)
			{
				_marioMenuY = MENU_MAX;
			}
		}
		else if (IsKeyDown(DIK_RETURN))
		{
			if (_marioMenuY == MENU_MIN)
			{
				_state = GS_PLAYING;
			}
			else
				_state = GS_PLAYING;
		}
		break;

	case GS_PLAYING:
		if (IsKeyDown(DIK_RIGHT))
		{
			mario->_vx = MARIO_SPEED;
			mario->_vx_last = mario->_vx;
		}
		else
		if (IsKeyDown(DIK_LEFT))
		{
			mario->_vx = -MARIO_SPEED;
			mario->_vx_last = mario->_vx;
		}
		else
		{
			mario->_vx = 0;
			mario->_sprite->Reset();
		}
		if (IsKeyDown(DIK_Q))
			PostQuitMessage(0);
		break;
	}
	
}

void CMarioSample::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
		case DIK_SPACE:
			if (mario->_y <= GROUND_Y) mario->_vy+=JUMP_VELOCITY_BOOST;			// start jump if is not "on-air"
			break;
	}
}



//Load Resources
void CMarioSample::LoadAudio()
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
void CMarioSample::LoadSprite()
{
	_sprites[S_GOOMBA] = new CSprite(_SpriteHandler, GOOMBA_IMAGE, 16, 16, 6, 6);
	_sprites[S_BMARIO] = new CSprite(_SpriteHandler, BMARIO_IMAGE, 16, 32, 8, 8);
	_sprites[S_BRICK] = new CSprite(_SpriteHandler, BRICK_IMAGE, 16, 16, 8, 8);
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
	_sprites[S_SMARIO] = new CSprite(_SpriteHandler, SMARIO__IMAGE, 16, 16, 8, 8);
	_sprites[S_STAR] = new CSprite(_SpriteHandler, STAR_IMAGE, 16, 16, 4, 4);
}
typedef struct SRC {
	int id;
	int srcX;
	int srcY;
};
void CMarioSample::LoadMap()
{
	FILE * pFile;
	FILE * sFile;

	int m = 0;
	int i = 0, j = 0;

	pFile = fopen("MAP1.ptl", "r");
	long a[200][1000];

	char ch;
	string s = "";
	if (pFile == NULL)
	{
		MessageBox(_hWnd, "File khong ton tai", MARIO_VOID, MB_OK);
		return;
	}
	bool kt = true;
	while (EOF != (ch = getc(pFile)))
	{
		if (ch != ' ' && ch != '\n')
		{
			s = s + ch;
		}
		if (' ' == ch && s != "")
		{
			a[i][j] = atoi(s.c_str());
			j++;
			s = "";
			kt = true;
		}
		if ('\n' == ch)
		{
			if (s != ""){
				a[i][j] = atoi(s.c_str());
				j++;

			}
			m = j;
			j = 0;
			i++;
			s = "";
			kt = true;
		}
	}
	int n = i;
	i = 0;
	for (int k = 0; k < n; k++)
	{
		for (int l = 0; l < m; l++)
		{
			if (a[k][l] == 0)
				continue;
			else
			{
				SRC t;
				t.srcX = l + 1;
				t.srcY = k + 1;
				t.id = a[k][l];
				switch (a[k][l])
				{
					//case 28: case 29:
					//	_staticObjs[i] = new Mountain(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0, vx, vy, t.id, _sprites[S_MOUNTAIN]);
					//	i++;
					//	break;
					//case 25: case 26: case 27:
					//	_staticObjs[i] = new Cloud(PIXEL * (t.srcX), PIXEL * (t.srcY), 40, 40, vx, vy, t.id, _sprites[S_CLOUD]);
					//	i++;
					//case 11: case 12: case 13:
					//	_staticObjs[i] = new Grass(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0, vx, vy, t.id, _sprites[S_GRASS]);
					//	i++;
					//	break;
					//case 22:
					//	_staticObjs[i] = new Ground(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0, vx, vy, t.id, _sprites[S_BASIC]);
					//	i++;
					//	break;
					//	/*case 23:
					//	_staticObjs[i] = new Castle(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0, vx, vy, t.id, _sprites[S_CLOUD]);
					//	i++;
					//	break;*/
				default:
					_staticObjs[i] = new Brick(PIXEL * (t.srcX), PIXEL * (t.srcY), _camera->_cameraX, _camera->_cameraY, t.id, _sprites[S_BRICK]);
					i++;
					break;
				}
			}
			_countI = i;
		}
	}
	fclose(pFile);
}
void CMarioSample::CollisionHanding()
{
	
	/*if (collisiontime < 1.0f)
	{
		if (normalx == -1.0f)
			MessageBox(_hWnd, "va cham nomarlx -1", "INFO", MB_OKCANCEL);
		else if (normaly == 1.0f)
			MessageBox(_hWnd, "va cham nomarly 1", "INFO", MB_OKCANCEL);
		else if (normalx == -1.0f)
			MessageBox(_hWnd, "va cham normalx -1", "INFO", MB_OKCANCEL);
		else if (normaly == 1.0f)
			MessageBox(_hWnd, "va cham normaly 1", "INFO", MB_OKCANCEL);
	}*/
	if (_col->AABBCheck(mario, testBrick))
	{
		float normalx;
		float normaly;
		float collisiontime = _col->SweptAABB(mario, testBrick, OUT normalx, OUT normaly);
		//mario->_x += mario->_vx * collisiontime;
		////mario->_y += mario->_vy * collisiontime;
		//float remainingtime = 1.0f - collisiontime;

		if (collisiontime < 1.0f)
		{
			/*if (normalx == -1.0f)
				MessageBox(_hWnd, "va cham", "INFO", MB_OKCANCEL);
			else if (normaly == 1.0f)
				MessageBox(_hWnd, "va cham", "INFO", MB_OKCANCEL);
			else if (normalx == -1.0f)
				MessageBox(_hWnd, "va cham", "INFO", MB_OKCANCEL);
			else if (normaly == 1.0f)*/
				MessageBox(_hWnd, "va cham", "INFO", MB_OKCANCEL);
		}
		MessageBox(_hWnd, "va cham", "INFO", MB_OKCANCEL);
		//MessageBox(_hWnd, "va cham", "INFO", MB_OKCANCEL);
		
	}
	//	MessageBox(_hWnd, "va cham", "INFO", MB_OKCANCEL);

}



void CMarioSample::RenderMenu(LPDIRECT3DDEVICE9 d3ddv)
{
	_marioMenu->Render(_marioMenuX, _marioMenuY, _camera->_cameraX, _camera->_cameraY, 1);
	d3ddv->StretchRect(_title, NULL, _BackBuffer, NULL, D3DTEXF_NONE);
}