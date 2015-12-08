#include "Cloud.h"
#include "Global.h"


Cloud::Cloud() :BaseObject()
{
}
Cloud::Cloud(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_vx = 5;
	_vy = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
}

void Cloud::Render()
{
	_sprite->Render(_x, _y, _cameraX, _cameraY, MARIO_DEEP);
}
