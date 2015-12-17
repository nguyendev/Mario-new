#include "BackGround.h"
#include "Global.h"


BackGround::BackGround() :BaseObject()
{
}
BackGround::BackGround(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
}

void BackGround::Render()
{
	_sprite->Render(getPosition().x, getPosition().y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
