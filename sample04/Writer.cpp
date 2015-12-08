#include "Writer.h"


Writer::Writer()
{
}
void Writer::DrawTextAdvanced(LPCWSTR text, int x, int y, int width, int height, D3DXCOLOR color, LPD3DXFONT font)
{
	RECT rect;
	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;
	font->DrawTextW(NULL, (LPCWSTR)text, -1, &rect, 0, color);
}

Writer::~Writer()
{
}
void Writer::DrawNumber(CSprite* sprite, int number, int x, int y, int vpx, int vpy)
{
	DrawNumber(sprite, number, x, y,vpx, vpy,1,1);
}
LPDIRECT3DSURFACE9 Writer::CreateSurface(char* filePath, LPDIRECT3DDEVICE9 d3ddv)
{
	D3DXIMAGE_INFO imageInfo;
	D3DXGetImageInfoFromFile(filePath, &imageInfo);
	IDirect3DSurface9* rSurface;	//return surface
	d3ddv->CreateOffscreenPlainSurface(imageInfo.Width, imageInfo.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &rSurface, NULL);
	D3DXLoadSurfaceFromFile(rSurface, NULL, NULL, filePath, NULL, D3DX_DEFAULT, 0, NULL);
	return rSurface;
}
void Writer::DrawNumber(CSprite* sprite, int number, int x, int y,int vpx, int vpy, char zoomX, char zoomY)
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