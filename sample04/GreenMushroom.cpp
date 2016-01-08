#include "GreenMushRoom.h"

// Khi activate thì nấm bay lên 1 khoảng thời gian
// nếu va chạm bên trái vật khác thì v = âm, va chạm bên phải thì v dương.
GreenMushRoom::GreenMushRoom()
{
}
GreenMushRoom::GreenMushRoom(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Position.x = x;
	_m_Position.y = y;
	_m_Velocity.x = 0;
	_m_Velocity.y = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_widthRect = _width;
	_heightRect = _height+2;
	_state = TS_IDLE;
	timeRised = 0;
}
void GreenMushRoom::Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case TS_IDLE:				// trạng thái chờ 
		break;
	case TS_MOVEUP:				// đang đi lên
		Move();
		
		break;
	case TS_BREAKED:							// đã bị ăn
		Move();
		break;
	}
}
void GreenMushRoom::Move()
{
	if (timeRised < 10){ // not going up yet
		// y direction
		_m_Position.y += _m_Velocity.y;
	}
	else{				// get definitely out of the brick
		// x direction
		_m_Position.x += _m_Velocity.x;
		// y direction
		_m_Position.y += _m_Velocity.y;
	}
	timeRised++;
}
void GreenMushRoom::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)	// need to fix
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
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					break;
				default:
					break;
				}
			}
			if (obj->_ID == 1){			// va chạm với mario
				// xử lý ở đây
				if (dir == BOTTOM)
				_m_Velocity.y = -Y_VELOCITY;
				return;
			}
		}
	}
}
void GreenMushRoom::Render()
{
	switch (_state)
	{
	case TS_IDLE:				// trạng thái chờ 
		_sprite->setIndex(0);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
		break;
	case TS_MOVEUP:				// đang đi lên
		_sprite->setIndex(0);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
		break;
	case TS_BREAKED:							// đã bị ăn
		_sprite->setIndex(0);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
		break;
	}
	
}
void GreenMushRoom::SetState(char* Name, int val)
{
	if (strcmp(Name, "_state") == 0)
	{
		ChangeState(val);
		return;
	}
}

int GreenMushRoom::GetState(char* Name)
{
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}

void GreenMushRoom::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case TS_IDLE:
	case TS_MOVEUP:
		break;
	}
}

GreenMushRoom::~GreenMushRoom()
{
}
