#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
class Writer
{
public:
	Writer();
	~Writer();
	void DrawTextAdvanced(LPCWSTR text, int x, int y, int width, int height, D3DXCOLOR color, LPD3DXFONT font);
	void DrawNumber(CSprite* sprite, int number, int x, int y, int vpx, int vpy);
	void DrawNumber(CSprite* sprite, int number, int vpx, int vpy, int x, int y, char zoomX, char zoomY);
	LPDIRECT3DSURFACE9 CreateSurface(char* filePath, LPDIRECT3DDEVICE9 d3ddv);
};
