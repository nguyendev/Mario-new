#include "Mario.h"
#include "Global.h"
#include "Collision.h"
#include "GameMario.h"
#define MARIO_VX	100.0f	//velocity of mario
#define MARIO_VY	20.2f
#define MAX_MARIO_VX 2.0f	//max velocity of mario
#define MAX_MARIO_VY 2.0f
#define GRAVITY		4.0f	//gravity ratio
#define FRICTION_X	2.5f   //friction of mario
#define ACCEL_X		1.5f //1.5 //accelerator of mario
Mario::Mario() :BaseObject(){};
Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sbig_right, CSprite* sbig_left, CSprite* ssmall_right, CSprite* ssmall_left, CSprite* sbullet, CSprite* sExplosion, CGameMario* game) :BaseObject(x, y, cameraX, cameraY)
{
	_game = game;
	_sprite = ssmall_right;
	_sSmall_right = ssmall_left;
	_sBig_left = sbig_left;
	_sBig_right = sbig_right;
	_sBullet = sbullet;
	_sExplosion = sExplosion;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_vx_last = 1.0f;
	_widthRect = _width - 2;
	_heightRect = _height - 1;
	isCanJump = false;
	_timejump = 0;
	isJumping = false;
	_m_Velocity = D3DXVECTOR2(0,0);
	waittime = 0; 
	maxVelocity = m_MaxVelocity;
	isChangeDirectionL = false;
	isChangeDirectionR = true;
}
Mario::~Mario()
{
	delete _sprite;
	delete _sSmall_right;
	delete _sBig_left;
	delete _sBig_right;
}
void Mario::TurnLeft(float TPF)
{
	_m_Velocity.x -= FRICTION_X * TPF;
	if (_m_Velocity.x <= -MAX_MARIO_VX)
		_m_Velocity.x = -MAX_MARIO_VX;
	isChangeDirectionL = true;
	isChangeDirectionR = false;
}
void Mario::TurnRight(float TPF)
{
	// if press Right, Update _vx
	_m_Velocity.x += FRICTION_X * TPF;
	if (_m_Velocity.x >= MAX_MARIO_VX)
		_m_Velocity.x = MAX_MARIO_VX;
	isChangeDirectionR = true;
	isChangeDirectionL = false;
}
void Mario::Stand(float TPF)
{
	//Giam toc do xuong khi khong bam phim
	if (_m_Velocity.x < 0.0f)
		_m_Velocity.x += FRICTION_X / 2 * TPF;
	else if (_m_Velocity.x > 0.0f)
		_m_Velocity.x -= FRICTION_X / 2 * TPF;

	if ((_m_Velocity.x <= 1.5f) && (_m_Velocity.x >= -1.5f))
		_m_Velocity.x = 0.0f;
	//isChangeDirectionL = false;
	//isChangeDirectionR = true;
}
void Mario::Jump(float TPF)
{
	_m_Velocity.y = -MARIO_VY;
}
void Mario::Move(float TPF)
{
	_m_Position.x += _m_Velocity.x;
	_m_Position.y += _m_Velocity.y;
	if (_m_Position.x < Camera::_cameraX)									//Không cho đi quá Camera
		_m_Position.x = Camera::_cameraX;
	if (_m_Position.x > Camera::_cameraX + WIDTH)
		_m_Position.x = Camera::_cameraX + WIDTH;
	if (_m_Velocity.x != 0)
	{
		if (isChangeDirectionL)
			_sprite->Next(TPF);
		else if (isChangeDirectionR)
			_sSmall_right->Next(TPF);
	}
	else
	{
		_sSmall_right->setIndex(0);
		_sprite->setIndex(7);
	}
	
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
					//_m_Position.y = obj->getPosition().y + obj->_heightRect + 1;
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
     						obj->SetState("_state", TS_BREAKING);
					}
					break;
				case BOTTOM:
					//_m_Position.y = obj->getPosition().y - this->_height - 1;
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					_m_Position.x = (int) _m_Position.x;
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
	_m_Velocity.y += 1;
	Move(TPF);
	CheckCollision(staticObj, dynamicObj);
	ProcessInput(keyborad, TPF);
	
}
void Mario::Render()
{		
	if (isChangeDirectionL)
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (isChangeDirectionR)
		_sSmall_right->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Mario::ProcessInput(KeyBoard* _keyboard, float TPF)
{
	if (_keyboard->KeyDown(DIK_DOWN))		//Ngồi
	{
	}
	else if (_keyboard->KeyDown(DIK_RIGHT))
	{
		TurnRight(TPF);
	}
	else if (_keyboard->KeyDown(DIK_LEFT))
	{
		TurnLeft(TPF);
	}
	
	else if (_keyboard->KeyPress(DIK_SPACE))
		Jump(TPF);
	else
	{
		Stand(TPF);
	}
	
}

