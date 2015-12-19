#include "Brick.h"
#include "Global.h"


Brick::Brick() :BaseObject()
{
}
Brick::Brick(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	_widthRect = _width;
	_heightRect = _height;
}
void Brick::Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{
}
void Brick::Render()
{
	switch (_ID)
	{
	case 22:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		_sprite->Render(_m_Position.x, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		//_height += _height;
		break;
	case 18:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 19:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 17:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 20:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	case 21:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		break;
	}
	
}
