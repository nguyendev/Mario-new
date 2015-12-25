#include "Goomba.h"
#include "Collision.h"
#define GOOMBA_SPEED -100.0f

Goomba::Goomba()
{
}
Goomba::Goomba(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite):BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Velocity.x = -1;		// demo, if the game is real, it is 0
	_m_Velocity.y = 1;
	_width = _sprite->_Width;
	_height = _sprite->_Height-1;
	_widthRect = _width;
	_heightRect = _height;
	state = ES_ACTIVING;
	ay = Gy;
}
void Goomba::Move(float t)
{
	_m_Position.x += _m_Velocity.x;
	_m_Position.y += _m_Velocity.y;
}
void Goomba::Collision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{
	list<BaseObject*>::iterator i;
	for (i = staticObj->begin(); i != staticObj->end(); i++)
	{
		obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, obj);
		if (obj->_ID >= 17 && obj->_ID <= 22) //collision with Brick
		{
			switch (dir)
			{
			case BOTTOM:
				_m_Velocity = Collision::getInstance()->getVelocity();
				break;
			}
		}
	}
	
}
void Goomba::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyborad)
{
	switch (state)
	{
	case ES_ACTIVING:
		break;
	case ES_IDLE:
		waitIdle += TPF;
		if (waitIdle > 1)
			this->setStatusObject(StatusObject::DEAD);
		break;
	case ES_FALL:
		_m_Position.x += _m_Velocity.x*TPF;
		_m_Velocity.y += ay*TPF;
		_m_Position.y += _m_Velocity.y*TPF + 0.5*ay*TPF*TPF;
		if (_m_Position.y>HEIGHT)
			this->setStatusObject(StatusObject::DEAD);
	}
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(TPF);
		Collision(staticObj,dynamicObj);
		_sprite->Next(0,1);
		last_time = now;
	}
}
void Goomba::Render()
{
	if (state != ES_FALL)
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Goomba::CollisionTemp(BaseObject* obj)
{
	
}
