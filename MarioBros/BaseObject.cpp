 #include "BaseObject.h"




BaseObject::BaseObject()
{
	_sprite = NULL;
	_ani = NULL;
}

BaseObject::BaseObject(float xWorld, float yWorld, float width, float height, float vx, float vy)
{
	_x = xWorld;
	_y = yWorld;
	_width = width;
	_height = height;
	_vx = vx;
	_vy = vy;
	_sprite = NULL;
	_direction = 0; ///1 left to  ,2 right to
	_ani = NULL;
}


BaseObject::BaseObject(float xWorld, float yWorld, float width, float height ,int vxObj, int vyObj,float vx, float vy)
{
	_x = xWorld;
	_y = yWorld;
	_width = width;
	_height = height;
	_vx = vx;
	_vy = vy;
	_vxObj = vxObj;
	_vxObj = vyObj;
	_sprite = NULL;
	_direction = 0; ///1 left to  ,2 right to
	_ani = NULL;
}

BaseObject::~BaseObject()
{
	if (_ani != NULL)
		delete _ani;
}
