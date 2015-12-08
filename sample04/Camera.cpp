#include "Camera.h"
#include "Global.h"

float Camera::_cameraX = 0;
float Camera::_cameraY = 0;
Camera::Camera()
{
	_cameraX = 0;
	_cameraY = 0;
}


Camera::~Camera()
{
}
void Camera::Update(BaseObject* mario)
{
	if (mario->_x - _cameraX > WIDTH / 2 / ZOOM)
		_cameraX = mario->_x - WIDTH / 2 /ZOOM;
	if (mario->_x < _cameraX)
		mario->_x = _cameraX;
}