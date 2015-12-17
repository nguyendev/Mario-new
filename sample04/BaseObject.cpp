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

BaseObject::BaseObject(float xWorld, float yWorld, float cameraX, float cameraY)
{
	_x = xWorld;
	_y = yWorld;
	_cameraX = cameraX;
	_cameraY = cameraY;
	_sprite = NULL;
	_oldNode = NULL;
	ResetRect();
}
void BaseObject::ResetRect()
{
	_rect.left = _x;
	_rect.top = _y;
	_rect.right = _rect.left + _width;
	_rect.bottom = _rect.top + _height;
}

