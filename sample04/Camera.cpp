﻿#include "Camera.h"
#include "Global.h"

float Camera::_cameraX = 0;
float Camera::_cameraY = 0;
Camera::Camera(float x, float y, float width, float height)
{
	_cameraX = x;
	_cameraY = y;
	_width = width;
	_height = height;
	ResetRect();
}


Camera::~Camera()
{
}
void Camera::Update(QuadTree* quadTree)
{
	if (_cameraX + _width < quadTree->rect.right - 80)
	{
		if (mario->getPosition().x > _cameraX + _width / 2)
		{
			_cameraX = mario->getPosition().x - _width / 2;
		}
		if (mario->getPosition().x < _cameraX)
		{
			mario->setPositionX(_cameraX);
		}
	}
	else
		_cameraX = quadTree->rect.right - _width;
	ResetRect();
	
}
void Camera::ResetRect()
{
	_rect.left = _cameraX;
	_rect.right = _cameraX + _width;
	_rect.top = _cameraY;
	_rect.bottom = _cameraY + _height;
}