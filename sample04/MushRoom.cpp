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
	_widthRect = _width;
	_heightRect = _height;
	timeRised = RISE_TIME;
	_state = TS_IDLE;		// đang chờ
}
void MushRoom::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	
	switch (_state)
	{
	case TS_IDLE:								// đang chờ
		break;
	case TS_MOVEUP:
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
			if (_ID == 33)						// nếu là nấm đỏ
			{
				_m_Velocity.y = Y_VELOCITY;
				_m_Velocity.x = X_VELOCITY;
			}
			SetState("_state", TS_ACTIVING);
		}
			
	case TS_ACTIVING:							// đang được kích hoạt
		if (_ID == 33)							// là nấm đỏ
		{
			_m_Position.x += _m_Velocity.x;
			// y direction
			_m_Position.y += _m_Velocity.y;
			// phải update vận tốc sau khi xét va chạm
			CheckCollision(staticObj, dynamicObj);
		}
		break;
	case TS_BREAKED:			// bị ăn rồi
		_isNeedDelete = true;
		break;
	}
}

void MushRoom::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)	// need to fix
{
	//Collision with staticObj
	list<BaseObject*>::iterator i;
	for (i = staticObj->begin(); i != staticObj->end(); i++)
	{
		obj = *i;
		
		
		if (obj->_ID >= 14 && obj->_ID <= 21 && obj->_ID != 19|| obj->_ID == 59 || obj->_ID == 29)
		{
			DIR dir = Collision::getInstance()->isCollision(this, obj);
			//_m_Velocity = Collision::getInstance()->getVelocity();
			// đi xuống
			if (dir == DIR::NONE)
			{
				_m_Velocity.y = Y_VELOCITY;
			}
			if (dir != DIR::NONE)
			{

				switch (dir)
				{
				case LEFT: case RIGHT:
					if (_ID == 33)	{
						// nếu ko phải hoa
						obj->_ID;
						this->setVelocity(this->getVelocity().x*-1, this->getVelocity().y);				
					}
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					break;
				}
			}
		}
		if (obj->_ID == 22)
		{
			DIR dir = Collision::getInstance()->isCollision(this, obj);
		}
	}
}
void MushRoom::Render()
{
	if (_ID == 33)				// không phải hoa
	{
		_currentSprite = 1;
		_sprite->setIndex(_currentSprite);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
	}
	else if(_ID==34)						// là hoa
	{
		_currentSprite++;
		if (_currentSprite<4 || _currentSprite>7)
			_currentSprite = 4;
		_sprite->setIndex(_currentSprite);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
		
	}
	
}
void MushRoom::SetState(char* Name, int val)
{
	if (strcmp(Name, "_state") == 0)
	{
		ChangeState(val);
		return;
	}
}

int MushRoom::GetState(char* Name)
{
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}
void MushRoom::ChangeState(char state)
{
	_state = state;
}
MushRoom::~MushRoom()
{
}
