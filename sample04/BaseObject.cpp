#pragma warning(disable: 4244) // possible loss of data
#include "BaseObject.h"



//float BaseObject::_cameraX = 0;
//float BaseObject::_cameraY = 0;
BaseObject::BaseObject()
{
	_sprite = NULL;
	_oldNode = NULL;
}
BaseObject::~BaseObject()
{
	
}

BaseObject::BaseObject(float x, float y, float cameraX, float cameraY)
{
	_m_Position.x = x;
	_m_Position.y = y;
	_m_Velocity.x = 0;
	_m_Velocity.y = 0;
	_cameraX = cameraX;
	_cameraY = cameraY;
	_sprite = NULL;
	_oldNode = NULL;
	_widthRect = _width;
	_heightRect = _height;
	m_isActive = true;
	m_status = StatusObject::ALIVE;
}

void BaseObject::setPosition(float x, float y)
{
	_m_Position.x = x;
	_m_Position.y = y;
}
void BaseObject::setPositionX(float x)
{
	_m_Position.x = x;
}
void BaseObject::setPositionY(float y)
{
	_m_Position.y = y;
}

Box BaseObject::getBouding()
{
	return Box(_m_Position.x, _m_Position.y, _widthRect, _heightRect, _m_Velocity.x, _m_Velocity.y);
}

void BaseObject::setVelocity(float vx, float vy)
{
	_m_Velocity.x = vx;
	_m_Velocity.y = vy;
}

void BaseObject::setStatusObject(StatusObject status)
{
	m_status = status;
}

