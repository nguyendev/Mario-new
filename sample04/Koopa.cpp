#include "Koopa.h"
#include "Collision.h"

Koopa::Koopa()
{
}
Koopa::Koopa(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y,cameraX, cameraY)
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
	_heightRect = _height-1;
	_state = ES_ACTIVING;		// khoi tao trang thai cho`. -  DANG TEST
	_currentSprite = 0;
	_waitingTimeToLiveAgain = 4;
}
void Koopa::Move()
{
	_m_Position.x += _m_Velocity.x;
	_m_Position.y += _m_Velocity.y;
}

void Koopa::Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ 
		break;
	case ES_ACTIVING:			// duoc kich hoat
		_m_Velocity.x = -X_VELOCITY;
		Move();
		CheckCollision(staticObj, dynamicObj);
		break;
	case ES_CRASHED:						// đã bị dậm lần 1
		_m_Velocity.x = 0;
		Move();
		CheckCollision(staticObj, dynamicObj);
		_waitingTimeToLiveAgain -= Time;
		if (_waitingTimeToLiveAgain <= 0)
		{
			SetState("_state", ES_ACTIVING);
			_waitingTimeToLiveAgain = 4;	// reset waiting time
		}
			
		break;
	case ES_MOVE_SHELL_RIGHT:				// bi dam lan thu 2, di chuyen sang ben phai
		_m_Velocity.x = X_VELOCITY*2;
		Move();
		break;
	case ES_MOVE_SHELL_LEFT:				// bi dam lan thu 2, di chuyen sang ben trai
		_m_Velocity.x = -X_VELOCITY*2;
		Move();
		break;
	case ES_DIED:
		_isNeedDelete = true;
		break;
	}
}
void Koopa::Render()
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ duoc kich hoat
		break;
	case ES_ACTIVING:				// đang đi 
		if (_currentSprite > 1)
			_currentSprite = 0;
		_sprite->setIndex(_currentSprite++);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_CRASHED:							// đã bị dam
		_sprite->setIndex(2);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_MOVE_SHELL_RIGHT:		
		_sprite->setIndex(3);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_MOVE_SHELL_LEFT:		// bi dam lan thu 2, di chuyen sang ben phai
		_sprite->setIndex(3);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_DIED:
		_isNeedDelete = true;
		break;
	}
}
void Koopa::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)	// need to fix
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
			if (obj->_ID >= 17 && obj->_ID <= 22 || obj->_ID == 52) //collision with Brick
			{
				switch (dir)
				{
				case LEFT:
					_m_Velocity.x = X_VELOCITY;
					break;
				case RIGHT:
					
					_m_Velocity.x = -X_VELOCITY;
					break;
				case TOP:
					break;
				case BOTTOM:						// va chạm bên trên viên gạch thì vận tốc bằng 0.
					_m_Velocity.y = 0;
					break;
				default:
					break;
				}
			}
		}
	}
	// va chạm với vật di chuyển
	for (i = dynamicObj->begin(); i != dynamicObj->end(); i++)
	{
		obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, obj);
	}
}

void Koopa::SetState(char* Name, int val)
{
	if (strcmp(Name, "_state") == 0)
	{
		ChangeState(val);
		return;
	}
}

int Koopa::GetState(char* Name)
{
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}

void Koopa::ChangeState(char state)
{
	_state = state;

}

Koopa::~Koopa()
{
}