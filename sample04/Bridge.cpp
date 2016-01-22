#include "Bridge.h"
#include "Global.h"



Bridge::Bridge() :BaseObject()
{
}
Bridge::Bridge(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) : BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_isChanged = false;
	_isNeedDelete = false;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = 0;
	// dai 7 don vi
	_widthRect = _width*7;
	_heightRect = _height;
	_state = TS_IDLE;
	// khoi tao
}

void Bridge::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	_m_Velocity.y = GOING_SPEED;
	if (_ID==41)							// neu dang di len
	{ 
		// neu khoang cach lon hon khoang cach quy dinh
		// neu di qua len tren man hinh
		if (_m_Position.y < Camera::_cameraY)
			_m_Position.y = Camera::_cameraY + HEIGHT/ZOOM;	// thi quay ve vi tri khoi tao
		_m_Position.y -= _m_Velocity.y;
	}
	else if (_ID==42)		// neu di xuong
	{
		_m_Position.y += _m_Velocity.y;
		if (_m_Position.y > Camera::_cameraY + HEIGHT / ZOOM)
			_m_Position.y = Camera::_cameraY;	// thi quay ve vi tri khoi tao
	}
}
void Bridge::Render()
{
	// ve 6 sprite
	_sprite->setIndex(_SpriteIndex);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
	_sprite->setIndex(_SpriteIndex + 1);
	_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
	_sprite->setIndex(_SpriteIndex + 1);
	_sprite->Render(_m_Position.x + _width * 2, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
	_sprite->setIndex(_SpriteIndex + 1);
	_sprite->Render(_m_Position.x + _width * 3, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
	_sprite->setIndex(_SpriteIndex + 1);
	_sprite->Render(_m_Position.x + _width * 4, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
	_sprite->setIndex(_SpriteIndex + 1);
	_sprite->Render(_m_Position.x + _width * 5, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
	_sprite->setIndex(_SpriteIndex + 1);
	_sprite->Render(_m_Position.x + _width * 6, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
	_sprite->setIndex(_SpriteIndex + 2);
	_sprite->Render(_m_Position.x + _width * 7, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);

}
void Bridge::SetState(char* Name, int val)
{
	if (strcmp(Name, "_isChanged") == 0)
	{
		if (val == 0)
			_isChanged = false;
		else _isChanged = true;
		return;
	}
	if (strcmp(Name, "_state") == 0)
	{
		ChangeState(val);
		return;
	}
}

int Bridge::GetState(char* Name)
{
	if (strcmp(Name, "_isChanged") == 0)
		return _isChanged;
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}

void Bridge::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case TS_IDLE:
	case TS_MOVEUP:

	case TS_BREAKING:
		break;
	case TS_BREAKED:
		_isNeedDelete = true;
	}
}