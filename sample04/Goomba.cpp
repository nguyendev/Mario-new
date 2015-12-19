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
	_m_Velocity.x = GOOMBA_SPEED;		// demo, if the game is real, it is 0
	_m_Velocity.y = +10;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	state = ES_ACTIVING;
	ay = G;
	ResetRect();
}
void Goomba::Move(float t)
{
	_m_Position.x += _m_Velocity.y * t;
	_m_Position.y += _m_Velocity.y* t;
}
void Goomba::CollisionStatic(float TPF, list<BaseObject*>* staticObj)
{
	list<BaseObject*>::iterator i;
	for (i = staticObj->begin(); i != staticObj->end(); i++)
	{
		obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, obj);
		//if (dir != DIR::NONE)
		//{
		//	MessageBox(NULL, "d", "s", NULL);
		//	if (obj->_ID >= 18 && obj->_ID <= 22) //collision with Brick
		//	{
				if (dir == DIR::TOP || dir == DIR::BOTTOM)
					this->setVelocity(this->getVelocity().x, this->getVelocity().y * -1);
			/*}
		}*/
	}
}
void Goomba::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
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
		ResetRect();
		if (_m_Position.y>HEIGHT)
			this->setStatusObject(StatusObject::DEAD);
	}
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(TPF);
		CollisionStatic(TPF, staticObj);
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
