#include "Cloud.h"
#include "Global.h"


Cloud::Cloud() :BaseObject()
{
}
Cloud::Cloud(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;

}
void Cloud::Render()
{
	switch (_ID)
	{
	case 25:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x + _width*2, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x + _width*3, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		break;
	case 26:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x + _width * 2, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width*3, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x + _width * 4, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x + _width * 5, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		break;
	case 27:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x + _width * 2, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width*3, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x + _width * 4, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width * 5, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x + _width * 6, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		_sprite->Render(_m_Position.x + _width * 7, _m_Position.y, Camera::_cameraX, Camera::_cameraY, CLOUD_DEEP);
		break;
	}
	
}
