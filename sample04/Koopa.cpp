#include "Koopa.h"
#include "Collision.h"

Koopa::Koopa()
{
}
Koopa::Koopa(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
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
	_heightRect = _height - 1;
	_state = ES_ACTIVING;		// khoi tao trang thai cho`. -  DANG TEST
	_currentSprite = 0;
	_waitingTimeToLiveAgain = WAITING_TIME_TO_LIVE;
	_waitingTimeToDie = WAITING_TIME_TO_DIE;
}
void Koopa::Move()
{
	_m_Position.x += _m_Velocity.x;
	_m_Position.y += _m_Velocity.y;
}

void Koopa::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ 
		break;
	case ES_ACTIVING:			// duoc kich hoat
		_currentSprite++;
		if (_currentSprite > 5)
			_currentSprite = 4;
		_m_Velocity.x = -X_VELOCITY;
		Move();
		CheckCollision(staticObj, dynamicObj);
		break;
	case ES_CRASHED:										// đã bị dậm lần 1
		_m_Velocity.x = 0;									// vận tốc ngang bằng 0
		Move();
		
		_waitingTimeToLiveAgain -= TPF;						// thời gian chờ đếm ngược
		if (_waitingTimeToLiveAgain < 0)
		{
			SetState("_state", ES_ACTIVING);
			_waitingTimeToLiveAgain = WAITING_TIME_TO_LIVE;	// reset waiting time
		}
		CheckCollision(staticObj, dynamicObj);
		break;
	case ES_MOVE_SHELL_RIGHT:				// bi dam lan thu 2, di chuyen sang ben phai
		_m_Velocity.x = X_VELOCITY * 2;
		Move();
		CheckCollision(staticObj, dynamicObj);
		break;
	case ES_MOVE_SHELL_LEFT:				// bi dam lan thu 2, di chuyen sang ben trai
		_m_Velocity.x = -X_VELOCITY * 2;
		Move();
		CheckCollision(staticObj, dynamicObj);
		break;
	case ES_SHOOTED:						// bị bắn
		_waitingTimeToDie -= TPF;
		_m_Velocity.x = X_VELOCITY / 2;
		Move();
		// 1 phần 3 thời gian bay lên
		if (_waitingTimeToDie>2 * WAITING_TIME_TO_DIE / 3)
			_m_Velocity.y = -Y_VELOCITY;
		else if (_waitingTimeToDie> 0 && _waitingTimeToDie<2 * WAITING_TIME_TO_DIE / 3)
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
	oldY = _m_Position.y;
}
void Koopa::Render()
{
	switch (_state)
	{
	case ES_IDLE:				// trạng thái chờ duoc kich hoat
		break;
	case ES_ACTIVING:				// đang đi 
		
		_sprite->setIndex(_currentSprite);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		_sprite->setIndex(_currentSprite - 4);
		_sprite->Render(_m_Position.x, _m_Position.y - 16 + 1, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_CRASHED:							// đã bị dam
		_sprite->setIndex(6);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_MOVE_SHELL_RIGHT:
		_sprite->setIndex(7);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_MOVE_SHELL_LEFT:		// bi dam lan thu 2, di chuyen sang ben phai
		_sprite->setIndex(7);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
		break;
	case ES_SHOOTED:
		_sprite->setIndex(7);
		_sprite->Render(_m_Position.x, _m_Position.y + 1, Camera::_cameraX, Camera::_cameraY, KOOPA_DEEP);
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
		
		//if (dir == DIR::NONE)										// đang không va chạm thì có trọng lực
		//{
		//	_m_Velocity.y = Y_VELOCITY;
		//}
		if (obj->_ID >= 14 && obj->_ID <= 22 || obj->_ID == 52) //collision with Brick and pipes
		{
			DIR dir = Collision::getInstance()->isCollision(this, obj);
			if (dir != DIR::NONE)
			{

				switch (dir)
				{
				case LEFT:
					// nếu đang hoạt động bình thường thì đổi chiều vận tốc
					if (this->GetState("_state") == ES_ACTIVING)
						_m_Velocity.x = -X_VELOCITY;
					// nếu đang di chuyển trong vỏ sang phải => đổi sang di chuyển sang trái
					if (this->GetState("_state") == ES_MOVE_SHELL_RIGHT)
						this->SetState("_state", ES_MOVE_SHELL_LEFT);
					break;
				case RIGHT:
					// nếu đang hoạt động bình thường thì đổi chiều vận tốc
					if (this->GetState("_state") == ES_ACTIVING)
						_m_Velocity.x = X_VELOCITY;
					// nếu đang di chuyển trong vỏ sang trái => đổi sang di chuyển sang phải
					if (this->GetState("_state") == ES_MOVE_SHELL_LEFT)
						this->SetState("_state", ES_MOVE_SHELL_RIGHT);

					break;
				case TOP:
					break;
				case BOTTOM:						// va chạm bên trên viên gạch thì vận tốc bằng 0.
					// va chạm với gạch đang đi lên
					if (obj->getVelocity().y < 0)
						this->SetState("_state", ES_SHOOTED);
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
		
		if (obj->_ID == 1)
		{										// va chạm với mario
			// xử lý ở đây
			DIR dir = Collision::getInstance()->isCollision(this, obj);
			if (dir != DIR::NONE)
			{
				if (this->GetState("_state") == ES_ACTIVING)		// nếu đang đi
				{
					if (dir == TOP)									// bị dậm trên đầu
					{
						this->SetState("_state", ES_CRASHED);		// chuyển sang trạng thái bị crash
					}

				}
				if (this->GetState("_state") == ES_CRASHED)							// nếu đã bị Crash
				{																	// bị va chạm tiếp
					float centerOfMario = (obj->getPositionX() + obj->_width) / 2;
					float centerOfKoopa = (this->getPositionX() + this->_width) / 2;
					if ((centerOfMario - centerOfKoopa) < 0)						// nếu tâm mario theo trục x nhỏ hơn koopa thì Move Right
						this->SetState("_state", ES_MOVE_SHELL_RIGHT);				// chuyển sang trạng thái bị move right
					else															// ngược lại
						this->SetState("_state", ES_MOVE_SHELL_LEFT);				// chuyển sang trạng thái bị move right
				}
				if (this->GetState("_state") == ES_MOVE_SHELL_LEFT || this->GetState("_state") == ES_MOVE_SHELL_RIGHT)
				{
					// cả goomba và koopa chuyển sang trạng thái bị bắn
					obj->SetState("_state", M_DIEING);
				}
				
			}
		}
		if (obj->_ID ==55)											// va chạm với goomba hoặc koopa.
		{							
			DIR dir = Collision::getInstance()->isCollision(this, obj);
			if (this->GetState("_state") == ES_MOVE_SHELL_LEFT || this->GetState("_state") == ES_MOVE_SHELL_RIGHT)
			{
					// cả goomba và koopa chuyển sang trạng thái bị bắn
					//obj->_isNeedDelete = true;
				if (dir != DIR::NONE)
				{
						obj->SetState("_state", ES_SHOOTED);
						_m_Position.y = oldY;
				}
			}
			// nếu đang di chuyển trong mai sang bên trái
		}
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