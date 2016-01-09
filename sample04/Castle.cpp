#include "Castle.h"
#include "Global.h"


Castle::Castle() :BaseObject()
{
}
Castle::Castle(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	_heightRect = _height + _m_Position.y;
	_widthRect = _width;
}
void Castle::Render()
{
	_sprite->setIndex(_SpriteIndex);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CASTLE_DEEP);
	_sprite->setIndex(_SpriteIndex + 1);
	_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CASTLE_DEEP); 
	_sprite->setIndex(_SpriteIndex + 2);
	_sprite->Render(_m_Position.x, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, CASTLE_DEEP);
	_sprite->setIndex(_SpriteIndex + 3);
	_sprite->Render(_m_Position.x + _width, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, CASTLE_DEEP);
}
