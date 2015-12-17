#include "Brick.h"
#include "Global.h"


Brick::Brick() :BaseObject()
{
}
Brick::Brick(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_vx = 5;
	_vy = 5;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	ResetRect();
}
void Brick::Update()
{
	_x += 10;
}
void Brick::Render()
{
	switch (_ID)
	{
	case 22:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		
		_sprite->Render(_x, _y + _height, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 18:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 19:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 17:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 20:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 21:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	}
	
}
