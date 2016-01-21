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
	_heightRect = _height;
	_state = TS_IDLE;
	timeRised = RISE_TIME;
}
void GreenMushRoom::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case TS_IDLE:				// trạng thái chờ 
		break;
	case TS_MOVEUP:				// thoát ra khỏi viên gạch
		if (timeRised > 0){ // not going up yet
			// y direction
			_m_Velocity.y = -Y_VELOCITY;
			_m_Position.y += _m_Velocity.y;
			timeRised -= TPF;
		}
		// nếu hết thời gian đi lên thì chuyển trạng thái activing
		if (timeRised <= 0)
		{
			//Khởi tạo vận tốc di chuyển
			_m_Velocity.y = Y_VELOCITY;
			_m_Velocity.x = X_VELOCITY;
			SetState("_state", TS_ACTIVING);
		}
		break;
	case TS_ACTIVING:			// đang hoạt động
		_m_Position.x += _m_Velocity.x;
		// y direction
		_m_Position.y += _m_Velocity.y;
		// phải update vận tốc sau khi xét va chạm
		CheckCollision(staticObj, dynamicObj);
		break;
	case TS_BREAKED:			// đã bị ăn
		_isNeedDelete = true;
		break;
	}
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
		if (dir == DIR::NONE)
		{
			_m_Velocity.y = Y_VELOCITY;
		}
		if (dir != DIR::NONE)
		{
			//D3DXVECTOR2 position = this->getPosition();
			if (obj->_ID >= 14 && obj->_ID <= 22) //collision with Brick and pipes
			{
				switch (dir)
				{
				case LEFT: case RIGHT:
					_m_Velocity.x *= -1;			// đổi hướng vận tốc ngang
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					break;
				}
			}
		}
	}
}
void GreenMushRoom::Render()
{
	switch (_state)
	{
	case TS_IDLE:				// trạng thái chờ 
		break;
	case TS_MOVEUP:				// đang đi lên
		_sprite->setIndex(0);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
		break;
	case TS_ACTIVING:
		_sprite->setIndex(0);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
	case TS_BREAKED:							// đã bị ăn 
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
