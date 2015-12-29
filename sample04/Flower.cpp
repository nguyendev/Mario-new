#include "Flower.h"

Flower::Flower()
{
}
Flower::Flower(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Position.x = x;
	_m_Position.y = y;
	_m_Velocity.x = 0;
	_m_Velocity.y = -Y_VELOCITY;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	Activated = false;
	timeRised = 0;
}
void Flower::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{
		if (Activated)
		{
			Move();
			CheckCollision(staticObj, dynamicObj);
			Render();
			_sprite->Next(TPF);
		}
}
void Flower::Move()
{
	// y direction
	if (timeRised < 9){
		_m_Velocity.y = Y_VELOCITY;
		_m_Position.y += _m_Velocity.y;
	}
	timeRised++;
}
void Flower::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)	// need to fix
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
					break;
				case RIGHT:
					break;
				case TOP:
					//_m_Velocity = Collision::getInstance()->getVelocity();
					break;
				case BOTTOM:
					break;
				default:
					break;
				}
			}
		}
	}
}
void Flower::Render()
{
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
}
Flower::~Flower()
{
}
