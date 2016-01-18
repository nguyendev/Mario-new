﻿#include "Goomba.h"
#include "Collision.h"

Goomba::Goomba()
{
}
Goomba::Goomba(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Position.x = x;
	_m_Position.y = y;
	_m_Velocity.x = -X_VELOCITY;
	_m_Velocity.y = Y_VELOCITY;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_widthRect = _width;
	_heightRect = _height;
	_state = ES_ACTIVING;		// khoi tao trang thai cho`. -  DANG TEST
	_currentSprite = 0;
	_waitingTimeToDie = 0.5;
}
void Goomba::Move()
{
	_m_Position.x += _m_Velocity.x;
	_m_Position.y += _m_Velocity.y;
}

void Goomba::Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ 
		break;
	case ES_ACTIVING:			// duoc kich hoat
		_m_Velocity.y = Y_VELOCITY;
		Move();
		CheckCollision(staticObj, dynamicObj);
		_sprite->Next(0, 1, Time);
		break;
	case ES_CRASHED:						// đã bị dam
		_waitingTimeToDie -= Time;
		if (_waitingTimeToDie <= 0)
			SetState("_state", ES_DIED);
		break;
	case ES_DIED:				
		_isNeedDelete = true;
		break;
	}
	NewRect();
}
void Goomba::Render()
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ duoc kich hoat
		break;
	case ES_ACTIVING:				// đang đi 
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, GOOMBA_DEEP);
		break;
	case ES_CRASHED:							// đã bị dam
		_sprite->setIndex(2);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, GOOMBA_DEEP);
		break;
	case ES_DIED:
		// delete from quadtree.
		break;
	}
}
void Goomba::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)	// need to fix
{
	//Collision with staticObj
	list<BaseObject*>::iterator i;
	for (i = staticObj->begin(); i != staticObj->end(); i++)
	{
		obj = *i;
	
			if (obj->_ID >= 14 && obj->_ID <= 22 || obj->_ID == 52) //collision with Brick or pipe
			{
				DIR dir = Collision::getInstance()->isCollision(this, obj);
				_m_Velocity = Collision::getInstance()->getVelocity();
				if (dir != DIR::NONE)
				{
					switch (dir)
					{
					case LEFT:	case RIGHT:
						this->setVelocity(this->getVelocity().x*(-1), this->getVelocity().y);
						break;
					case BOTTOM: case TOP:
						_m_Velocity.y = 0;
						break;
					}
				}
			
		}
	}
}

void Goomba::SetState(char* Name, int val)
{
	if (strcmp(Name, "_state") == 0)
	{
		ChangeState(val);
		return;
	}
}

int Goomba::GetState(char* Name)
{
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}

void Goomba::ChangeState(char state)
{
	_state = state;
	
}

Goomba::~Goomba()
{
}