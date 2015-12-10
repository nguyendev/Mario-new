#include "Mario.h"
#include "Global.h"

Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_vx = 0;
	_vy = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_vx_last = 1.0f;
}


Mario::~Mario()
{
}
void Mario::Move(int t)
{
	_x +=_vx * t;
	_y += _vy * t;
	if (_y < GROUND_Y) 
		_vy += FALLDOWN_VELOCITY_DECREASE;
	else 
	{
		_y = GROUND_Y;
		_vy = 0;
	}
}
void Mario::Update(int t)
{
	
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(t);
		if (_vx > 0) _sprite->Next();
		if (_vx < 0) _sprite->Next();
		last_time = now;
	}
}

void Mario::Render()
{
	if (_vx > 0)			_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_vx < 0)		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_vx_last < 0) _sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else					_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Mario::ProcessInput(KeyBoard* _keyboard)
{
	if (_keyboard->KeyDown(DIK_RIGHT))
	{
		_vx = MARIO_SPEED;
		_vx_last =_vx;
	}
	else if (_keyboard->KeyDown(DIK_LEFT))
	{
		_vx = -MARIO_SPEED;
		_vx_last = _vx;
	}
	else if (_keyboard->KeyPress(DIK_SPACE))
	{
		if (_y >= GROUND_Y) 
			_vy -= JUMP_VELOCITY_BOOST;
	}
	else
	{
		_vx = 0;
		_sprite->Reset();
	}
}
