#include "BaseObject.h"



//float BaseObject::_cameraX = 0;
//float BaseObject::_cameraY = 0;
BaseObject::BaseObject()
{
	_sprite = NULL;
	_oldNode = NULL;
	ResetRect();
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
	ResetRect();
}
void BaseObject::ResetRect()
{
	_rect.left = _m_Position.x;
	_rect.top = _m_Position.y;
	_rect.right = _rect.left + _width;
	_rect.bottom = _rect.top + _height;
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
	return Box(_m_Position.x, _m_Position.y, _width, _height, _m_Velocity.x, _m_Velocity.y);
}

void BaseObject::setVelocity(float vx, float vy)
{
	_m_Velocity.x = vx;
	_m_Velocity.y = vy;
}

