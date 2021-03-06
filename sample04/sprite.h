#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>

class CSprite {
protected: 
	LPDIRECT3DTEXTURE9 _Image;				// The container of all the sprites
	LPD3DXSPRITE _SpriteHandler;			

	int _Index;						// Current sprite index
							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
public: 
	
	float _Width;								// Sprite width
	float _Height;
	float _waitNextImage;
	float _timePerImage;
	void setIndex(int Index);
	CSprite::CSprite(LPD3DXSPRITE SpriteHandler, char* FilePath, int Width, int Height, int Count, int SpritePerRow, float timePerImage);
	void Next(float time);
	void Reset();
	void Next(int start, int end, float time);
	// Render current sprite at location (X,Y)
	void Render(float x, float y, int vpx, int vpy, float deep);
	void Render(float x, float y);
	void Render(float X, float Y, int vpx, int vpy, bool isLeft, bool isDown, float deep);
	void Render(float X, float Y, int vpx, int vpy, int zoomX, int zoomY, RECT rSrc, float deep);
	~CSprite();
};

#endif