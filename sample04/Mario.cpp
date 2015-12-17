#include "Mario.h"
#include "Global.h"
#include "Collision.h"
Collision* checkCollision;
Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_vx_last = 1.0f;
	ResetRect();
	checkCollision = new Collision();
}


Mario::~Mario()
{
}
void Mario::Move(float TPF)
{
	//Theo phương x
	_m_Velocity.x += ax*TPF;
	if (_m_Velocity.x > vMax) 
		_m_Velocity.x = vMax;	
	else if (_m_Velocity.x < -vMax) 
		_m_Velocity.x = -vMax;
	_m_Position.x += _m_Velocity.x * TPF + 1 / 2 * ax*TPF*TPF;

	//Theo phương y
	ay = G / 2;
	_m_Velocity.y += ay*TPF;
	_m_Position.y += _m_Velocity.y*TPF + 1.0 / 2 * ay*TPF*TPF;

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
		DIR dir = checkCollision->isCollision(this, obj);
		if (obj->_ID >= 18 && obj->_ID <= 25)
		{
			if (dir == DIR::TOP || dir == DIR::BOTTOM)
				this->setVelocity(this->getVelocity().x, this->getVelocity().y * -1);
		}
		else if (obj->_ID <= 18 || obj->_ID >= 25)
			if (dir == DIR::LEFT || dir == DIR::RIGHT)
				this->setVelocity(this->getVelocity().x * -1, this->getVelocity().y);
		/*else
		{
			if (dir == DIR::TOP || dir == DIR::BOTTOM)
				this->setVelocity(this->getVelocity().x, this->getVelocity().y * -1);
			else if (dir == DIR::LEFT || dir == DIR::RIGHT)
				this->setVelocity(this->getVelocity().x * -1, this->getVelocity().y);
		}*/
	}
}
void Mario::Update(float TPF, list<BaseObject*>* staticObj)
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
	else if (_keyboard->KeyPress(DIK_SPACE))
	{
	}
	else
	{
		ax = 0;
		ay = 0;
		_m_Velocity.x = 0;
		_m_Velocity.y = 0;
		_sprite->Reset();
	}
}

