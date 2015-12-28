#include "Star.h"


Star::Star()
{
}
Star::Star(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Position.x = x;
	_m_Position.y = y;
	_m_Velocity.x = X_VELOCITY;
	_m_Velocity.y = -Y_VELOCITY;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	timeJump = 10;				// max high the star can go
	Activated = false;
}
void Star::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (Activated)
		{
			Move();
			CheckCollision(staticObj, dynamicObj);
			Render();
			_sprite->Next();
			last_time = now;
		}
	}
}
void Star::Move()
{
	// x direction
	_m_Position.x += _m_Velocity.x;
	// y direction
	timeJump--;
	if (timeJump <= 0)	// going down
		_m_Velocity.y = Y_VELOCITY;
	else if (timeJump > 0)
		_m_Velocity.y = -Y_VELOCITY;
	_m_Position.y += _m_Velocity.y;
}
void Star::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)	// need to fix
{
	//Collision with staticObj
	list<BaseObject*>::iterator i;
	for (i = staticObj->begin(); i != staticObj->end(); i++)
	{
		obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, obj);
		float timeCollision = Collision::getInstance()->getTimeCollision();
		if (dir != DIR::NONE)
		{
			//D3DXVECTOR2 position = this->getPosition();

			if (obj->_ID >= 17 && obj->_ID <= 22) //collision with Brick
			{
				switch (dir)
				{
				case LEFT:
					_m_Velocity.x = -X_VELOCITY;
					break;
				case RIGHT:
					_m_Velocity.x = X_VELOCITY;
					break;
				case TOP:
					//_m_Velocity = Collision::getInstance()->getVelocity();
					_m_Velocity.y = Y_VELOCITY;
					timeJump = 10;
					break;
				case BOTTOM:
					_m_Velocity.y = -Y_VELOCITY;
					_m_Velocity = Collision::getInstance()->getVelocity();
					break;
				default:
					break;
				}
			}
		}
	}
}
void Star::Render()
{
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
}
Star::~Star()
{
}
