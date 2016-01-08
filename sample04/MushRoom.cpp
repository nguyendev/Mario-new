#include "MushRoom.h"

// Khi activate thì nấm bay lên 1 khoảng thời gian
// nếu va chạm bên trái vật khác thì v = âm, va chạm bên phải thì v dương.
MushRoom::MushRoom()
{
}
MushRoom::MushRoom(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y,cameraX, cameraY)
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
	_heightRect = _height-1;
	isFlower = false;		// không phải là hoa.
	timeRised = RISE_TIME;
	_state = TS_IDLE;		// đang chờ
}
void MushRoom::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	
	switch (_state)
	{
	case TS_IDLE:								// đang chờ
		_currentSprite = 3;						// tàng hình
		CheckCollision(staticObj, dynamicObj);
		break;
	case TS_ACTIVING:							// đang được kích hoạt
		if (!isFlower)							// là nấm đỏ
		{
			_ID = 33;							// đổi id thành 33
			_currentSprite = 1;
			// di chuyển
			if (timeRised > 0){ // not going up yet
				// y direction
				_m_Velocity.y = -Y_VELOCITY;
				_m_Position.y += _m_Velocity.y;
				timeRised-=TPF;
			}
			else if (timeRised >= -TPF&&timeRised<=0)				// dang chuyen trang thai tu di len => di len hoan toan
			{
				_m_Velocity.x = X_VELOCITY;
				_m_Velocity.y = Y_VELOCITY;
				timeRised -= 2*TPF;
			}
			else{				// get definitely out of the brick
				// x direction
				_m_Position.x += _m_Velocity.x;
				// y direction
				_m_Position.y += _m_Velocity.y;
				// phải update vận tốc sau khi xét va chạm
				_m_Velocity.y = Y_VELOCITY;
				CheckCollision(staticObj, dynamicObj);
			}
		}

		else									// là hoa
		{
			_ID = 34;							// đổi id thành 34
			_currentSprite++;
			if (_currentSprite<4||_currentSprite>7)
				_currentSprite = 4;
			// di chuyển
			if (timeRised < 10){ // not going up yet
				// y direction
				_m_Velocity.y = -Y_VELOCITY;
				_m_Position.y += _m_Velocity.y;
				timeRised++;
			}
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
		if (obj->_ID >= 14 && obj->_ID <= 22)
		{
			DIR dir = Collision::getInstance()->isCollision(this, obj);
			float timeCollision = Collision::getInstance()->getTimeCollision();
			if (dir != DIR::NONE)
			{

				switch (dir)
				{
				case LEFT: case RIGHT:
					_m_Velocity.x *=-1;
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					break;
				}

			}
		}

	}
	for (i = dynamicObj->begin(); i != dynamicObj->end(); i++)
	{
		obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, obj);
		float timeCollision = Collision::getInstance()->getTimeCollision();
		if (dir != DIR::NONE)
		{
			if (obj->_ID == 1)									// va chạm với mario
			{
				if (_state == TS_IDLE)							// nếu đang chờ...
				{
					if (dir == BOTTOM)							// va chạm đáy của item
					{
						if (obj->GetState("_state") != M_NORMAL)// là loại bình thường => là nấm		đang test
							isFlower = false;					
						else									// không phải loại bình thường => là hoa
							isFlower = true;					
						SetState("_state",TS_ACTIVING);					// thì kích hoạt
					}
				}
				/*if (_state == TS_ACTIVING)						// nếu đã được kích hoạt
				{
					SetState("_state", TS_BREAKED);				// thì chuyển sang breaked
				}*/
			}
		}
	}
}
void MushRoom::Render()
{
	_sprite->setIndex(_currentSprite);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
}
void MushRoom::SetState(char* Name, int val)
{
	ChangeState(val);
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
