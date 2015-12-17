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
	ResetRect();
}


Mario::~Mario()
{
}
void Mario::Move(float TPF)
{
	_x += _vx * TPF;
	_y += _vy * TPF;
	if (_x < Camera::_cameraX)									//Không cho đi quá Camera
		_x = Camera::_cameraX;
	if (_x > Camera::_cameraX + WIDTH)
		_x = Camera::_cameraX + WIDTH;
}
void Mario::Update(float TPF)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(TPF);
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
	else if (_keyboard->KeyDown(DIK_UP))
	{
		_vy = -FALLDOWN_VELOCITY_DECREASE;
	}
	else if (_keyboard->KeyDown(DIK_DOWN))
	{
		_vy = FALLDOWN_VELOCITY_DECREASE;
	}
	else if (_keyboard->KeyPress(DIK_SPACE))
	{
		if (_y >= GROUND_Y) 
			_vy -= JUMP_VELOCITY_BOOST;
	}
	else
	{
		_vx = 0;
		_vy = 0;
		_sprite->Reset();
	}
}
void Mario::CollisionTemp(BaseObject* obj, float t)
{
	float normalx = 0;
	float normaly = 0;
	BaseObject *a = new BaseObject();
	a->_x = this->_x;
	a->_y = this->_y;
	a->_width = this->_width;
	a->_height = this->_height;
	a->_vx = this->_vx * t;
	a->_vy = this->_vy * t;
	BaseObject *b = new BaseObject();
	b->_x = obj->_x;
	b->_y = obj->_y;
	b->_width = obj->_width;
	b->_height = obj->_height;
	b->_vx = 0;
	b->_vy = 0;
	BaseObject* temp = GetSweptBroadphaseBox(a);
	if (AABBCheck(temp, b))
	{
		float collecsionTime = SweptAABB(a, b, normalx, normaly);
		if (collecsionTime < 1.0f && collecsionTime > 0)
		{
				GetCollisionWith(b,normalx, normaly);
		}
		//
		//	
		//if (AABB(this, obj) == RIGHT);
		////mario->_x = testBrick->_x + testBrick->_width+1;
		//if (AABB(this, obj) == TOP);
		//if (AABB(this, obj) == BOTTOM);
	}
}

void Mario::GetCollisionWith(BaseObject* b,float normalx,float normaly)
{

		if (normalx == -1)
		{
//			_x = obj->_x - this->_width;
		}
	
}
