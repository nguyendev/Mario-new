#include "sprite.h"
#include "Camera.h"
#include "Writer.h"
#define MENU_MAX 170
#define MENU_MIN  149
#define MENU_INCREASE 17
class MenuGame
{
protected:
	CSprite* _marioMenu;
public:
	
	int _marioMenuX;
	int _marioMenuY;
	LPDIRECT3DSURFACE9 _title;
	void RenderMenu(LPDIRECT3DDEVICE9 d3ddv, float cameraX, float cameraY,LPDIRECT3DSURFACE9 _backBuffer);
	void LoadMenuGame(PDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE _SpriteHandler, Writer* _writer);
	void LoadMap();
	void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t);
	MenuGame();
	~MenuGame();
};

