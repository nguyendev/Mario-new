#include "Flag.h"
#include "Global.h"


Flag::Flag() :BaseObject()
{
}
Flag::Flag(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
}

void Flag::Render()
{
 
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 2, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 3, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 4, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 5, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 6, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 7, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 8, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x, _m_Position.y - _height * 9, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x - _width / 2, _m_Position.y - _height*9, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x, _m_Position.y - _height*10, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);

}
