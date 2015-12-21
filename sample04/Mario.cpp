#include "Mario.h"
#include "Global.h"
#include "Collision.h"
#include "Audio.h"


Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite, HWND hwnd) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_vx_last = 1.0f;
	_widthRect = _width -2;
	_heightRect = _height -2;
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
	LoadAudio();
	Audio::getInstance()->initialize(hwnd);
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
				Audio::getInstance()->PlaySound(_sound_1up);
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
void Mario::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(TPF);
		CheckCollision(staticObj, dynamicObj);
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
	}
	else if (_keyboard->KeyDown(DIK_LEFT))
	{
		_m_Velocity.x = -1;
	}
	else
	{
		_m_Velocity.x = 0;
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

void Mario::LoadAudio()
{
	_sound_1up = Audio::getInstance()->LoadSound("Sounds\\1up.wav");
	_sound_Beep = Audio::getInstance()->LoadSound("Sounds\\Beep.wav");
	_sound_BigJump = Audio::getInstance()->LoadSound("Sounds\\BigJump.wav");
	_sound_BowserDie = Audio::getInstance()->LoadSound("Sounds\\Bowser.wav");
	_sound_Break = Audio::getInstance()->LoadSound("Sounds\\Break.wav");
	_sound_Bump = Audio::getInstance()->LoadSound("Sounds\\Bump.wav");
	_sound_Coin = Audio::getInstance()->LoadSound("Sounds\\Coin.wav");
	_sound_Die = Audio::getInstance()->LoadSound("Sounds\\Die.wav");
	_sound_EnemyFire = Audio::getInstance()->LoadSound("Sounds\\EnemyFire.wav");
	_sound_FireBall = Audio::getInstance()->LoadSound("Sounds\\FireBall.wav");
	_sound_Flagpole = Audio::getInstance()->LoadSound("Sounds\\Flagpole.wav");
	_sound_GameOver = Audio::getInstance()->LoadSound("Sounds\\GameOver.wav");
	_sound_Item = Audio::getInstance()->LoadSound("Sounds\\Item.wav");
	_sound_Jump = Audio::getInstance()->LoadSound("Sounds\\Jump.wav");
	_sound_Kick = Audio::getInstance()->LoadSound("Sounds\\Kick.wav");
	_sound_Pause = Audio::getInstance()->LoadSound("Sounds\\Pause.wav");
	_sound_Powerup = Audio::getInstance()->LoadSound("Sounds\\Powerup.wav");
	_sound_Skid = Audio::getInstance()->LoadSound("Sounds\\Skid.wav");
	_sound_Squish = Audio::getInstance()->LoadSound("Sounds\\Squish.wav");
	_sound_Thwomp = Audio::getInstance()->LoadSound("Sounds\\Thwomp.wav");
	_sound_Vine = Audio::getInstance()->LoadSound("Sounds\\Vine.wav");
	_sound_Warp = Audio::getInstance()->LoadSound("Sounds\\Warp.wav");
	_sound_Background = Audio::getInstance()->LoadSound("Sounds\\Background.wav");
}
