#include "FloorBrick.h"



FloorBrick::FloorBrick() :BaseObject()
{
}
FloorBrick::FloorBrick(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_vx = 5;
	_vy = 5;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
}

void FloorBrick::Update()
{
	_x += 10;
}
void FloorBrick::Render()
{
	_sprite->setIndex(_SpriteIndex);
	_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
