#pragma warning(disable: 4244) // possible loss of data
#pragma warning(disable: 4996) // variable may be unsafe
#include "Writer.h"
#include "Brick.h"
#include "Pipe.h"
#include "Goomba.h"
#include "Cloud.h"
#include "Mario.h"
#include "Grass.h"
#include "Mountain.h"
#include "Koopa.h"
#include "BrickQuestion.h"
#include "Coin.h"
#include "MushRoom.h"
#include "GreenMushroom.h"
#include "MuchMoneyBrick.h"
#include "Flag.h"
#include "Castle.h"
#include "Star.h"
#include "SpecialBrick.h"
#include "BrickMushroom.h"
#include "Bridge.h"

Camera*  _camera;
void DrawTxt(wstring text, int x, int y, LPD3DXFONT font)
{
	RECT rct;
	rct.left = x;
	rct.right = rct.left + 25 * text.length();
	rct.top = y;
	rct.bottom = y + 25;
	string s(text.begin(), text.end());
	LPCSTR lpMyString = s.c_str();
	//_text = text.c_str;
	//font->DrawText(NULL,text.c_str(), -1, &rct, 0, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(NULL, lpMyString, -1, &rct, 0, D3DCOLOR_XRGB(255, 255, 255));
}
void DrawNumber(CSprite* sprite, int number, int x, int y, int vpx, int vpy)
{
	DrawNumber(sprite, number, x,y, vpx, vpy, ZOOM, ZOOM);
}
LPDIRECT3DSURFACE9 CreateSurface(char* filePath, LPDIRECT3DDEVICE9 d3ddv)
{
	D3DXIMAGE_INFO imageInfo;
	D3DXGetImageInfoFromFile(filePath, &imageInfo);
	IDirect3DSurface9* rSurface;	//return surface
	d3ddv->CreateOffscreenPlainSurface(imageInfo.Width, imageInfo.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &rSurface, NULL);
	D3DXLoadSurfaceFromFile(rSurface, NULL, NULL, filePath, NULL, D3DX_DEFAULT, 0, NULL);
	return rSurface;
}
void DrawNumber(CSprite* sprite, int number, int x, int y, int vpx, int vpy, char zoomX, char zoomY)
{
	char temp;
	RECT rSrc;
	int numWidth = sprite->_Width;
	do
	{
		temp = number % 10;
		number = number / 10;
		rSrc.left = numWidth*temp;
		rSrc.right = numWidth*(temp + 1);
		rSrc.top = 0;
		rSrc.bottom = sprite->_Height;
		sprite->Render(x,y, vpx, vpy, zoomX, zoomY, rSrc, 1);
		x -= numWidth;
	} while (number>0);
}
typedef struct SRC {
	int id;
	int srcX;
	int srcY;
};
void ReadMap(char* fileName, bool isBright, CGameMario* game)
{
	bool _isStatic;
	int _count;
	FILE * pFile;
	BaseObject* obj = NULL;
	int m = 0;
	int i = 0, j = 0;
	int Count_Item = 0;

	pFile = fopen(fileName, "r");
	long a[200][1000];
	SRC t[2000];
	char ch;
	string s = "";
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
				t[i].srcX = l + 1;
				t[i].srcY = k + 1 + CHANGE_POSY;
				t[i].id = a[k][l];
				i++;
			}
			_count = i;
		}
	}
	if (game->_quadTree != NULL) delete game->_quadTree;
	int sizeWidth;
	int sizeHeight;
	if (fileName == "Map\\MAP1.ptl")
	{
		sizeWidth = 3865;
	}
	if (fileName == "Map\\MAP2.ptl")
		sizeWidth = 4000;
	game->_quadTree = new QuadTree(0, 0, sizeWidth, 0);
	Mario*	mario;
	for (int i = 0; i < _count; i++)
	{
		switch (t[i].id)
		{
		case 1:
			obj = new Mario(PIXEL * (t[i].srcX), PIXEL* (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BMARIO_RIGHT], game->_sprites[S_BMARIO_LEFT], game->_sprites[S_SMARIO_RIGHT], game->_sprites[S_SMARIO_LEFT], game->_sprites[S_FIREBULLET], game->_sprites[S_EXPLOSION], game);
			game->_camera->mario = obj;
			_isStatic = false;
			break;
		case 2:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 14, isBright);
			_isStatic = true;
			break;
		case 5:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 14, isBright);
			_isStatic = true;
			break;
		case 11: case 12: case 13:
			obj = new Grass(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_GRASS], 0);
			_isStatic = true;
			break;
		case 14: case 15: case 16:
			obj = new Pipe(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_PIPE], 0);
			_isStatic = true;
			break;
		case 17:
			obj = new StoneBrick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 2);
			_isStatic = true;
			break;
		case 18:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 0, isBright);
			_isStatic = true;
			break;
		case 19:
			obj = new BrickQuestion(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], game->_sprites[S_MONEY], 1);
			_isStatic = true;
			break;
		case 20:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 4, isBright);
			_isStatic = true;
			break;
		case 21:
			obj = new FloorBrick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 5);
			_isStatic = true;
			break;
		case 22:
			obj = new FloorBrick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 1);
			_isStatic = true;
			break;
		case 23:
			obj = new Castle(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_CASTLE], 0);
			_isStatic = true;
			break; 
		case 24:
			obj = new Castle(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_FLAGWIN], 0);
			_isStatic = true;
			break;
		case 25: case 26: case 27:
			obj = new Cloud(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_CLOUD], 0);
			_isStatic = true;
			break;
		case 28: case 29:
			obj = new Mountain(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_MOUNTAIN], 0);
			_isStatic = true;
			break;
		case 30: case 31: case 35:
			obj = new Pipe(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_PIPE], 0);
			_isStatic = true;
			break;
		case 39:
			obj = new StoneBrick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 6);
			_isStatic = true;
			break;
		case 41:
			obj = new Bridge(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRIDGE]);
			_isStatic = true;
			break;
		case 50:
			obj = new BrickMushroom(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK]);
			_isStatic = true;
			break;
		case 51:
			obj = new BrickQuestion(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], game->_sprites[S_MONEY], 5);
			_isStatic = true;
			break;
		case 52:
			obj = new BrickMushroom(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK]);
			_isStatic = true;
			break;
		case 53:
			obj = new Koopa(PIXEL * (t[i].srcX), PIXEL* (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_KOOPA]);
			_isStatic = false;
			break;
		case 55:
			obj = new Goomba(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_GOOMBA]);
			_isStatic = false;
			break;
		case 58:
			obj = new Flag(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_FLAG], 0);
			_isStatic = true;
			break;
		case 59:
			obj = new BrickMushroom(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK]);
			_isStatic = true;
			break;

		}
		// them doi tuong tinh vao quadtree.
		if (obj != NULL)
		{
			obj->_game = game;
			game->_quadTree->Add(obj, _isStatic);
		}
		obj = NULL;
	}
	fclose(pFile);
}
int StringToWString(std::wstring &ws, const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}