#include "Goomba.h"
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
	_heightRect = _height-1;
	_state = ES_ACTIVING;		// khoi tao trang thai cho`. -  DANG TEST
	_currentSprite = 0;
	_countingTimeToDie = WAITING_TIME_TO_DIE;
	_isNotCrashedByMario = false;
}
void Goomba::Move()
{
	_m_Position.x += _m_Velocity.x;
	_m_Position.y += _m_Velocity.y;
}

void Goomba::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ 
		break;
	case ES_ACTIVING:			// duoc kich hoat
		_m_Velocity.y = Y_VELOCITY;
		Move();
		CheckCollision(staticObj, dynamicObj);
		break;
	case ES_CRASHED:						// đã bị dậm hoặc crash với koopa hoặc đạn
		if (_isNotCrashedByMario)				// nếu bị crash bởi koopa hoặc đạn
		{
			_countingTimeToDie -= TPF;							// thời gian chết giảm dần
			_m_Position.x += 4;
			if (_countingTimeToDie > (WAITING_TIME_TO_DIE*0.75))	// 1 phần tư thời gian nảy lên không
				_m_Position.y -= 4;
			else
				_m_Position.y += 4;
			if (_countingTimeToDie < 0)							// hết thời gian
				SetState("_state", ES_DIED);
		}
		else								// nếu ko
		{
			_countingTimeToDie -= TPF;
			if (_countingTimeToDie < 0)
				SetState("_state", ES_DIED);
			break;
		}
		
	case ES_DIED:				
		_isNeedDelete = true;
		break;
	}
}
void Goomba::Render()
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ duoc kich hoat
		break;
	case ES_ACTIVING:				// đang đi 
		if (_currentSprite > 1)
			_currentSprite = 0;
		_sprite->setIndex(_currentSprite++);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, GOOMBA_DEEP);
		break;
	case ES_CRASHED:							// đã bị dam
		if (_isNotCrashedByMario)				// không bị dậm bởi mario
		{
			_sprite->setIndex(0);
			_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, GOOMBA_DEEP);
		}
		else
		{
			_sprite->setIndex(2);
			_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, GOOMBA_DEEP);
		}			
		break;
	case ES_DIED:
		_isNeedDelete = true;
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
		DIR dir = Collision::getInstance()->isCollision(this, obj);
		float timeCollision = Collision::getInstance()->getTimeCollision();
		if (dir != DIR::NONE)
		{
			if ((obj->_ID >= 14 && obj->_ID <= 22 )|| obj->_ID == 52) //collision with Brick or pipe
			{
				switch (dir)
				{
				case LEFT:
					//_m_Velocity.x = X_VELOCITY;
					break;
				case RIGHT:
					//_m_Velocity.x = -X_VELOCITY;

					break;
				case TOP:
					break;
				case BOTTOM:
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
		if (obj->_ID == 1)
		{										// va chạm với mario
			// xử lý ở đây
			if (dir != DIR::NONE)
			{
				if (this->GetState("_state") == ES_ACTIVING)		// nếu đang đi
				{
					if (dir == TOP)									// bị dậm trên đầu
					{
						this->SetState("_state", ES_CRASHED);		// chuyển sang trạng thái bị crash
					}
				}
			}
		}

		if (obj->_ID == 53)											// va chạm với koopa
		{										
			// xử lý ở đây
			if (dir != DIR::NONE)
			{
				if (obj->GetState("_state") == ES_MOVE_SHELL_LEFT 
					|| obj->GetState("_state") == ES_MOVE_SHELL_RIGHT)	// nếu koopa bị crash và đang di chuyển
				{
					_isNotCrashedByMario = true;
					if (this->GetState("_state")==ES_ACTIVING)
						this->SetState("_state", ES_CRASHED);
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