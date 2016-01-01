#include "Camera.h"
#include "BaseObject.h"


Camera::Camera(float x,float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_vx = 0;
	ResetRect();
}

void Camera::ResetRect()
{
	_rect.left = _x;
	_rect.right = _x + _width;
	_rect.top = _y;
	_rect.bottom = _y + _height;
}
void Camera::Update()
{
	if (_obj->_x>_x + _width / 3)			//Nếu đối tượng đi quá 1/3 màn hình ...
		_x = _obj->_x - _width / 3;			//... thì Camera dịch chuyển theo
	ResetRect();
}
Camera::~Camera()
{
}
