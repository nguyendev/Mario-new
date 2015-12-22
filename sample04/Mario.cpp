#include "Mario.h"
#include "Global.h"
#include "Collision.h"
#include "GameMario.h"

Mario::Mario() :BaseObject(){};
Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite, CGameMario* game) :BaseObject(x, y, cameraX, cameraY)
{
	_game = game;
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_vx_last = 1.0f;
	_widthRect = _width - 2;
	_heightRect = _height - 2;
	isCanJump = false;
	_timejump = 0;
	isJumping = false;
	m_MaxVelocity = D3DXVECTOR2(4.0f, 10.0f);
	m_MinVelocity = D3DXVECTOR2(-4.0f, -10.0f);
	_m_Velocity = D3DXVECTOR2(0, 0);
	waittime = 0;
	maxVelocity = m_MaxVelocity;
	minVelocity = m_MinVelocity;
	ax = ay = 0;
	vMax = VMAX;
	//Audio::getInstance()->initialize(hwnd);


}


Mario::~Mario()
{
}
void Mario::Move(float TPF)
{
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

	_m_Velocity.x += ax;

	// velocity is limited
	if (_m_Velocity.x > vMax)
		_m_Velocity.x = vMax;
	else if (_m_Velocity.x < -vMax)
		_m_Velocity.x = -vMax;
	_m_Position.x += _m_Velocity.x + 0.5*ax*ax;

	// pretend mario comeback.
	if (_m_Velocity.x*ax < 0){
		if (_m_Velocity.x>-0.5 && _m_Velocity.x < 0.5){	// G must smaller than 0.5
			_m_Velocity.x = 0;
			ax = 0;
		}
	}
	// tao quan tinh
	if (_m_Velocity.x>0){
		ax = -G / 2;
	}
	else if (_m_Velocity.x < 0){
		ax = G / 2;
	}
	// y direction
	ay = G;
	_m_Velocity.y += ay;
	_m_Position.y += _m_Velocity.y + 0.5*ay*ay;
	if (isOnTheGround){
		_timejump = 0;
		isJumping = false;
	}

	if (_m_Position.x < Camera::_cameraX)									//Không cho đi quá Camera
		_m_Position.x = Camera::_cameraX;
	if (_m_Position.x > Camera::_cameraX + WIDTH)
		_m_Position.x = Camera::_cameraX + WIDTH;
	_PositionX_Old = _m_Position.x;
}
void Mario::CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
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
			//D3DXVECTOR2 position = this->getPosition();

			if (obj->_ID >= 17 && obj->_ID <= 22) //collision with Brick
			{
				switch (dir)
				{
				case NONE:
					break;
				case LEFT:
					/*_m_Velocity = Collision::getInstance()->getVelocity();
					_m_Position.x = obj->getPosition().x - this->_width - 1;
					_m_Position.x = _PositionX_Old;*/
					break;
				case RIGHT:
					break;
				case TOP:
					//_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					break;
				case BOTTOM:
					_m_Velocity = Collision::getInstance()->getVelocity();
					break;
				default:
					break;
				}
			}

			if (obj->_ID >= 14 && obj->_ID <= 16) // collision with Pipe
			{
				_game->_audio->PlaySound(_game->_sound_Warp);
			}
		}
	}
	//------------------------

	//Collision with dynamicObj

	for (i = dynamicObj->begin(); i != dynamicObj->end(); i++)
	{
		obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, obj);
		if (dir != DIR::NONE){
			
			if (obj->_ID == 55)
			{
				if (dir == DIR::LEFT || dir == DIR::RIGHT || dir == DIR::TOP || dir == DIR::BOTTOM)
					_m_Position.x + 100;
			}
		}
	}
	//--------------------
}
void Mario::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyborad)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(TPF);
		CheckCollision(staticObj, dynamicObj);
		ProcessInput(keyborad);
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
		ax = G;
	}
	if (_keyboard->KeyDown(DIK_LEFT))
	{
		ax = -G;
	}

	if (_keyboard->KeyDown(DIK_SPACE))
	{
		_timejump++;
		if (_timejump < 6){
			_m_Velocity.y = -5;
			isJumping = true;
		}
	}
	else
	{
		isJumping = false;

	}
	
}

