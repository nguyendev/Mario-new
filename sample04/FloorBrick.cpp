#include "FloorBrick.h"



FloorBrick::FloorBrick() :BaseObject()
{
}
FloorBrick::FloorBrick(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex,bool isBright) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	
	_widthRect = _width;
	_heightRect = _height;
	if (isBright==false)					// nếu màu tối
		_SpriteIndex = SpriteIndex;
	else
		_SpriteIndex = SpriteIndex + 4;
}
void FloorBrick::Render()
{
	_sprite->setIndex(_SpriteIndex);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
