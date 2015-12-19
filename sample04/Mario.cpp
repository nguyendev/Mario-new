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
	//Theo phương y
	ay = G;
	
		
	_m_Velocity.y += ay*TPF;
	if (isJumping)	// if space button is down
	{
		_timejump += TPF;
		if (_timejump<0.3)
		{
			ay = -G;
			_m_Velocity.y = -200;
		}
		else
		{
			ay = G;
		}
	}
	_m_Position.y += _m_Velocity.y*TPF + 1.0 / 2 * ay*TPF*TPF;
	

	//Theo phương x
	_m_Velocity.x += ax*TPF;
	if (_m_Velocity.x > vMax) 
		_m_Velocity.x = vMax;	
	else if (_m_Velocity.x < -vMax) 
		_m_Velocity.x = -vMax;
	_m_Position.x += _m_Velocity.x * TPF + 1 / 2 * ax*TPF*TPF;
	

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
		if (dir != DIR::NONE)
		{
			//D3DXVECTOR2 position = this->getPosition();
			
			if (obj->_ID >= 18 && obj->_ID <= 22) //collision with Brick
			{
				
				if (dir == DIR::TOP)
				{
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					isJumping = false;		// if collision on top of brick, mario is not Jumping
					_timejump = 0;			// reset time jumped
				}
					
				if (dir == DIR::BOTTOM)
				{
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					isJumping = false;
				}
					
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
}
void Mario::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{
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
	if (_m_Velocity.x > 0)			_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_m_Velocity.x < 0)		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_vx_last < 0) _sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else					_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Mario::ProcessInput(KeyBoard* _keyboard)
{
	if (_keyboard->KeyDown(DIK_RIGHT))
	{
		//m_Velocity.x = MARIO_SPEED;
		//_vx_last = getVelocity().x;
		ax = G / 3;
		vMax = VMAX;
	}
	else if (_keyboard->KeyDown(DIK_LEFT))
	{
		//_m_Velocity.x = -MARIO_SPEED;
		//_vx_last = getVelocity().x;
		ax = -G / 3;
		vMax = VMAX;
	}
	else
	{
		ax = 0;
		//ay = 0;
		_m_Velocity.x = 0;
		_m_Velocity.y = 0;
		_sprite->Reset();
	}
	if (_keyboard->KeyDown(DIK_SPACE))
	{
		isJumping = true;
	}
	else
	{
		isJumping = false;
		_sprite->Reset();
	}
	
	
}

