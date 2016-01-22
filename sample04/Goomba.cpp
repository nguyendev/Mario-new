#include "Goomba.h"
#include "Collision.h"

Goomba::Goomba()
{
}
Goomba::Goomba(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite, bool isBright) :BaseObject(x, y, cameraX, cameraY)
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
	_waitingTimeToDie = WAITING_TIME_TO_DIE;
	_isBright = isBright;						// màu xanh hay ko?
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
		_timeToFlicker -= TPF;
		if (_timeToFlicker<0)
		{
			_currentSprite++;
			if (_isBright == false)			// không phải màu xanh
			{
				if (_currentSprite >1)
					_currentSprite = 0;
			}
			else							// là gạch màu xanh
			{
				if (_currentSprite >4||_currentSprite <3)
					_currentSprite = 3;
			}
			_timeToFlicker = TIME_FLICKER;	// reset thời gian nhấp nháy
		}
		Move();
		CheckCollision(staticObj, dynamicObj);
		break;
	case ES_CRASHED:						// đã bị dam
		_waitingTimeToDie -= TPF;
		if (_waitingTimeToDie <= 0)
			SetState("_state", ES_DIED);
		break;
	case ES_SHOOTED:						// bị bắn hoặc bị đập bởi mai rùa
		_waitingTimeToDie -= TPF;
		_m_Velocity.x = X_VELOCITY / 2;
		Move();
		// 1 phần 3 thời gian bay lên
		if (_waitingTimeToDie>2*WAITING_TIME_TO_DIE/3)
			_m_Velocity.y = -Y_VELOCITY;
		else if (_waitingTimeToDie> 0 &&_waitingTimeToDie<2*WAITING_TIME_TO_DIE/3)
		{
			_m_Velocity.y = Y_VELOCITY;
		}
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
		_sprite->setIndex(_currentSprite);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
		break;
	case ES_CRASHED:							// đã bị dam
		if (_isBright == false)					// nếu là màu vàng
			_sprite->setIndex(2);
		else									// nếu là màu xanh
			_sprite->setIndex(5);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
		break;
	case ES_SHOOTED:
		if (_isBright == false)					// nếu là màu vàng
			_sprite->setIndex(7);
		else									// nếu là màu xanh
			_sprite->setIndex(10);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
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
				// không va chạm với gạch nào
				if (dir == DIR::NONE)
				{
					_m_Velocity.y = Y_VELOCITY;
				}
				if (dir != DIR::NONE)
				{
					switch (dir)
					{
					case LEFT:	case RIGHT:
						this->setVelocity(this->getVelocity().x*(-1), this->getVelocity().y);
						break;
					case BOTTOM: 
						// gặp gạch đang bị đẩy lên thì chuuyển sang trạng thái bị bắn
						if (obj->getVelocity().y < 0)
							this->SetState("_state", ES_SHOOTED);
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