#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>

class CSprite {
protected: 
	LPDIRECT3DTEXTURE9 _Image;				// The container of all the sprites
	LPD3DXSPRITE _SpriteHandler;			

	int _Index;								// Current sprite index
							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
public: 
	int _Width;								// Sprite width
	int _Height;
	CSprite::CSprite(LPD3DXSPRITE SpriteHandler, char* FilePath, int Width, int Height, int Count, int SpritePerRow);
	void Next();
	void Reset();

	// Render current sprite at location (X,Y)
	void Render(int X, int Y, int vpx, int vpy);	
	~CSprite();
};

#endif