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
};
//
//void Graphic::DrawTextAdvanced(LPCWSTR text, int x, int y, int width, int height, D3DXCOLOR color, LPD3DXFONT font)
//{
//	RECT rect;
//	rect.left = x;
//	rect.right = x + width;
//	rect.top = y;
//	rect.bottom = y + height;
//	font->DrawTextW(NULL, (LPCWSTR)text, -1, &rect, 0, color);
//}

/*void DrawNumber(Sprite* sprite, int number, int x, int y, char zoomX, char zoomY)
{
	char temp;
	RECT rSrc;
	int numWidth = sprite->width / 10;
	do
	{
		temp = number % 10;
		number = number / 10;
		rSrc.left = numWidth*temp;
		rSrc.right = numWidth*(temp + 1);
		rSrc.top = 0;
		rSrc.bottom = sprite->height;
		sprite->Draw(x, y, zoomX, zoomY, rSrc, 0.1);
		x -= numWidth;
	} while (number>0);
}
//void DrawNumber(Sprite* sprite, int number, int x, int y)
//{
//	DrawNumber(sprite, number, x, y, 1, 1);
//}
//DrawNumber(sprites[S_NUMBER], numLife, 150, 20);
*/