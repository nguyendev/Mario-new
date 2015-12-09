#include "MenuGame.h"


MenuGame::MenuGame()
{
	_marioMenuY = MENU_MIN;
	_marioMenuX = 100;
}


MenuGame::~MenuGame()
{
}
typedef struct SRC {
	int id;
	int srcX;
	int srcY;
};
list<SRC> getlistSRC(string filepath){
	list<SRC> list;
	FILE *f = fopen(filepath.c_str(), "rt");
	while (!feof(f)){
		SRC t;
		fscanf(f, "%d", &t.id);
		fscanf(f, "%d", &t.srcX);
		fscanf(f, "%d", &t.srcY);
		list.push_back(t);
	}
	fclose(f);

	return list;
}

int srcX;
int srcY;
list<SRC> l = getlistSRC("MAP1.txt");
int i = 0;
void MenuGame::LoadMap()
{
	for each(const SRC &t in l){
		srcX = t.srcX;
		srcY = t.srcY;
		}
};

void MenuGame::LoadMenuGame(PDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE _SpriteHandler, Writer* _writer)
{
	_marioMenu = new CSprite(_SpriteHandler, "Image\\imgOptionCursor.png", 8, 8, 1, 1);
	_title = _writer->CreateSurface("Image\\imgbgMenu.png", d3ddv);
}
void MenuGame::RenderMenu(LPDIRECT3DDEVICE9 d3ddv, float cameraX, float cameraY, LPDIRECT3DSURFACE9 _backBuffer)
{
	_marioMenu->Render(_marioMenuX, _marioMenuY, cameraX, cameraY, 1);
	d3ddv->StretchRect(_title, NULL, _backBuffer, NULL, D3DTEXF_NONE);
}
void MenuGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{

}