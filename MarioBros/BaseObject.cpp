 #include "BaseObject.h"




BaseObject::BaseObject()
{
	_sprite = NULL;
	_ani = NULL;
	ResetRect();
}

BaseObject::BaseObject(float xWorld, float yWorld, float width, float height)
{
	_x = xWorld;
	_y = yWorld;
	_width = width;
	_height = height;
	_sprite = NULL;
	_direction = 0; ///1 left to  ,2 right to
	_ani = NULL;
	ResetRect();
}

BaseObject::~BaseObject()
{
	if (_ani != NULL)
		delete _ani;
}
void BaseObject::ResetRect()
{
	_rect.left = _x;
	_rect.top = _y;
	_rect.right = _rect.left + _width;
	_rect.bottom = _rect.top + _height;
}