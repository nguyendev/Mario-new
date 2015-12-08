#include "BaseObject.h"



//float BaseObject::_cameraX = 0;
//float BaseObject::_cameraY = 0;
BaseObject::BaseObject()
{
	_sprite = NULL;
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
}

