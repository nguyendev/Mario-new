#include "Mario.h"
#include "Global.h"
#include "Collision.h"
Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_vx_last = 1.0f;
	_widthRect = _width;
	_heightRect = _height;
	isCanJump = false;
	_timejump = 0;
	isJumping = false;
	m_MaxVelocity = D3DXVECTOR2(4.0f, 10.0f);
	m_MinVelocity = D3DXVECTOR2(-4.0f, -10.0f);
	_m_Velocity = D3DXVECTOR2(0,0);
	waittime = 0; 
	maxVelocity = m_MaxVelocity;
	minVelocity = m_MinVelocity;
	_m_Velocity = D3DXVECTOR2(0, 1);
}


Mario::~Mario()
{
}
void Mario::Move(float TPF)
{
	if (isCanJump)
	{
		if (_m_Position.y < 150)
			isCanJump = false;
	}
	if (_m_Position.y < 120)
		_m_Velocity.y *= -1;
	////Theo phương y
	//ay = G;
	//
	//	
	//_m_Velocity.y += ay*TPF;
	//if (isJumping)	// if space button is down
	//{
	//	_timejump += TPF;
	//	if (_timejump<0.3)
	//	{
	//		ay = -G;
	//		_m_Velocity.y = -200;
	//	}
	//	else
	//	{
	//		ay = G;
	//	}
	//}
	//
	

	////Theo phương x
	//_m_Velocity.x += ax*TPF;
	//if (_m_Velocity.x > vMax) 
	//	_m_Velocity.x = vMax;	
	//else if (_m_Velocity.x < -vMax) 
	//	_m_Velocity.x = -vMax;
	//_m_Position.x += _m_Velocity.x * TPF + 1 / 2 * ax*TPF*TPF;
	//


	// thiết lập max, min cho trường hợp small
	/*maxVelocity.x--;
	minVelocity.y++;

	if (_m_Velocity.x >= maxVelocity.x)
		_m_Velocity.x = maxVelocity.x;
	else if (_m_Velocity.x <= minVelocity.x)
		_m_Velocity.x = minVelocity.x;

	if (_m_Velocity.y >= maxVelocity.y)
		_m_Velocity.y = maxVelocity.y;
	else if (_m_Velocity.y <= minVelocity.y)
		_m_Velocity.y = minVelocity.y;*/

	_m_Position.x += _m_Velocity.x;
	_m_Position.y += _m_Velocity.y;
	if (_m_Position.x < Camera::_cameraX)									//Không cho đi quá Camera
		_m_Position.x = Camera::_cameraX;
	if (_m_Position.x > Camera::_cameraX + WIDTH)
		_m_Position.x = Camera::_cameraX + WIDTH;
}
void Mario::CollisionStatic(float TPF, list<BaseObject*>* staticObj)
{
	list<BaseObject*>::iterator i;
	for (i = staticObj->begin(); i != staticObj->end(); i++)
	{
		obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, obj);
		float timeCollision = Collision::getInstance()->getTimeCollision();
		if (dir != DIR::NONE)
		{
			//D3DXVECTOR2 position = this->getPosition();

			if (obj->_ID >= 18 && obj->_ID <= 22) //collision with Brick
			{
				switch (dir)
				{
				case NONE:
					break;
				case LEFT:
					_m_Velocity = Collision::getInstance()->getVelocity();
					_m_Position.x = obj->getPosition().x - this->_width - 1;
					break;
				case RIGHT:
					break;
				case TOP:
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					break;
				case BOTTOM:
					_m_Velocity = Collision::getInstance()->getVelocity();
					_m_Position.y = obj->getPosition().y - this->_height - 1;
					break;
				default:
					break;
				}
			}

			if (obj->_ID >= 14 && obj->_ID <= 16) // collision with Pipe
			{
				switch (dir)
				{
				case NONE:
					break;
				case LEFT:
					MessageBox(NULL, "", "", NULL);
					_m_Velocity.x = 0;
					_m_Position.x = obj->getPosition().x - this->_widthRect - 1;
					this->setVelocity(this->getVelocity().x*-1, this->getVelocity().y);
					break;
				case RIGHT:
					MessageBox(NULL, "", "", NULL);
					_m_Velocity = Collision::getInstance()->getVelocity();
					_m_Position.x = obj->getPosition().x + obj->_widthRect;
					break;
				case TOP:
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					break;
				case BOTTOM:
					_m_Velocity = Collision::getInstance()->getVelocity();
					_m_Position.y = obj->getPosition().y - this->_height - 1;
					break;
				default:
					break;
				}
			}
			//this->setPosition(position.x, position.y);
				//else if (dir == DIR::TOP)
				//{
				//	//if (getFSM() == FSM_Mario::FALL || getFSM() == FSM_Mario::RUN) // fall gặp vật cản
				//	//	setLocation(Location::LOC_ON_GROUND);
				//}
				/*_m_Velocity = Collision::getInstance()->getVelocity();
				this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);*/
				//if (dir == DIR::TOP || dir == DIR::BOTTOM)
				//{
				//	
				//	//position.y = obj->getPosition().y - this->_height;
				//	
				//	isCanJump = false;		// if collision on top of brick, mario is not Jumping
				//	//_timejump = 0;			// reset time jumped
				//}

				//if (dir == DIR::BOTTOM)
				//{
				//	//_m_Velocity = Collision::getInstance()->getVelocity();
				//	isCanJump = false;
				//	_m_Velocity *= -1;
				//}

				//if (dir == DIR::LEFT)
				//	_m_Velocity = Collision::getInstance()->getVelocity();
			}
			//else if (obj->_ID >= 14 && obj->_ID <= 16)  //collision with PIPE
			//{
			//	if (dir == DIR::LEFT || dir == DIR::RIGHT);
			//		//this->setVelocity(this->getVelocity().x*-1, this->getVelocity().y);
			//}
			
		
		
	}
}
void Mario::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{
	/*waittime += TPF;
	if (waittime > 1)
	{
		
		waittime = -1;
	}*/
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(TPF);
		CollisionStatic(TPF, staticObj);
		if (_m_Velocity.x > 0) _sprite->Next();
		if (_m_Velocity.x < 0) _sprite->Next();
		last_time = now;
	}
}

void Mario::Render()
{
	/*if (_m_Velocity.x > 0)			_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_m_Velocity.x < 0)		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_vx_last < 0) _sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);*/
	//else					
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Mario::ProcessInput(KeyBoard* _keyboard)
{
	if (_keyboard->KeyDown(DIK_RIGHT))
	{
		_m_Velocity.x = 1;
		//_vx_last = getVelocity().x;
		//ax = G / 3;
		//vMax = VMAX;
	}
	else if (_keyboard->KeyDown(DIK_LEFT))
	{
		_m_Velocity.x = -1;
		//_vx_last = getVelocity().x;
		//ax = -G / 3;
		//vMax = VMAX;
	}
	else
	{
		//ax = 0;
		////ay = 0;
		_m_Velocity.x = 0;
		//_m_Velocity.y++;
		//_sprite->Reset();
	}
	if (_keyboard->KeyPress(DIK_SPACE))
	{
		_m_Velocity.y = -4;
		isCanJump = true;
	}
	else
	{
		//isJumping = false;
		//_sprite->Reset();
	}
	
	
}

