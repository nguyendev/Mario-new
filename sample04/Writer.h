#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "Camera.h"
#include "GameMario.h"


void ReadMap(char* fileName, bool isBright, CGameMario* game);
void DrawTxt(wstring text, int x, int y, LPD3DXFONT font);
void DrawNumber(CSprite* sprite, int number, int x, int y, int vpx, int vpy);
void DrawNumber(CSprite* sprite, int number, int vpx, int vpy, int x, int y, char zoomX, char zoomY);
LPDIRECT3DSURFACE9 CreateSurface(char* filePath, LPDIRECT3DDEVICE9 d3ddv);

