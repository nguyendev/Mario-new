#include "Writer.h"
#include "Brick.h"
#include "Pipe.h"

void DrawTextAdvanced(LPCWSTR text, int x, int y, int width, int height, D3DXCOLOR color, LPD3DXFONT font)
{
	RECT rect;
	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;
	font->DrawTextW(NULL, (LPCWSTR)text, -1, &rect, 0, color);
}
void DrawNumber(CSprite* sprite, int number, int x, int y, int vpx, int vpy)
{
	DrawNumber(sprite, number, x, y,vpx, vpy,1,1);
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
void DrawNumber(CSprite* sprite, int number, int x, int y,int vpx, int vpy, char zoomX, char zoomY)
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
		sprite->Render(x, y,vpx, vpy, zoomX, zoomY, rSrc, 1);
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
	Camera*  _camera;
	int _count;
	FILE * pFile;
	BaseObject* obj = NULL;
	int m = 0;
	int i = 0, j = 0;

	pFile = fopen("MAP1.ptl", "r");
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
				t[i].srcY = k + 1;
				t[i].id = a[k][l];
				i++;
			}
			_count = i;
		}
	}
	for (int i = 0; i < _count; i++)
	{
		switch (t[i].id)
		{
		case 14: case 15: case 16:
			obj = new Pipe(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_PIPE], 0);
			break;

		case 18:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 0);
			break;
		case 19:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 8);
			break;
		case 17:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 2);
			break;
		case 20:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 4);
			break;
		case 21:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK], 5);
			break;
		default:
			obj = new Brick(PIXEL * (t[i].srcX), PIXEL * (t[i].srcY), _camera->_cameraX, _camera->_cameraY, t[i].id, game->_sprites[S_BRICK],1);
			break;
		}
		game->staticObjs.push_back(obj);
	}
	fclose(pFile);
}