#include "BaseObject.h"




BaseObject::BaseObject()
{
	_sprite = NULL;
}

BaseObject::BaseObject(float xWorld, float yWorld)
{
	_x = xWorld;
	_y = yWorld;
	_sprite = NULL;
}

