#include "MushRoom.h"

// Khi activate thì nấm bay lên 1 khoảng thời gian
// nếu va chạm bên trái vật khác thì v = âm, va chạm bên phải thì v dương.
MushRoom::MushRoom()
{
}
MushRoom::MushRoom(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Position.x = x;
	_m_Position.y = y;
	_m_Velocity.x = 0;
	_m_Velocity.y = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;

	Activated = false;
	timeRised = 0;
}
void MushRoom::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
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
void MushRoom::Move()
{
	if (timeRised < 10){ // not going up yet
		// y direction
		_m_Velocity.y = -Y_VELOCITY;
		_m_Position.y += _m_Velocity.y;
	}
	else{				// get definitely out of the brick
		// x direction
		_m_Velocity.x = X_VELOCITY;
		_m_Position.x += _m_Velocity.x;
		// y direction
		_m_Velocity.y = Y_VELOCITY;
		_m_Position.y += _m_Velocity.y;
	}
	timeRised++;
}
void MushRoom::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)	// need to fix
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
void MushRoom::Render()
{
	_sprite->setIndex(0);		// red mushroom
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
}
MushRoom::~MushRoom()
{
}
