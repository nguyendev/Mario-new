#include "Camera.h"
#include "BaseObject.h"


Camera::Camera()
{}


void Camera::Update(BaseObject *_obj)
{
	int vpx = _obj->_x - 400;
	//int vpx = xc;
	if (vpx <= 0) vpx = 0;

}
Camera::~Camera()
{
}
