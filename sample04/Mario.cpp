#include "Mario.h"
#include "Global.h"
#include "Collision.h"

#include "GameMario.h"
#define MARIO_VY	2.6f	//velocity Y of mario
#define _MARIO_VX_NORMAL 1.0f	//max velocity of mario
#define MAX_MARIO_VX_	1.5f
#define GRAVITY		1.0f	//gravity ratio
#define FRICTION_X	1.25f   //friction of mario
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
	_widthRect = _width;
	_heightRect = _height-1;
	isCanJump = false;
	timeJumped = 0;
	isJumping = false;
	_m_Velocity = D3DXVECTOR2(0,0);
	waittime = 0; 
	waitIncreaseVecY = 0;
	_m_PostionOld = _m_Position;
	isJumping = false;
	isChangeDirectionL = false;
	isChangeDirectionR = true;
	waitRenderFirst = 0;
	_state = M_NORMAL;
	_isVisiableKeyboard = true;
	died = false;
	isShotable = true;
	waitbullet = 0;
	isShotting = false;
	waitShotting = 0;

	//trang thai bao ve
	isProtected = true;
	isProtectedHidden = false;
	waitRender = 0;
	waitProtectHidden = 0;
	waitProtect = 0;
	isRender = true;

	//Co
	waitInFlag = 0;
}
Mario::~Mario()
{
	delete _sprite;
	delete _sSmall_right;
	delete _sBig_left;
	delete _sBig_right;
}
void Mario::TurnLeft(float TPF, float Max)
{
	_m_Velocity.x -= FRICTION_X * TPF;
	if (_m_Velocity.x <= -Max)
		_m_Velocity.x = -Max;
	isChangeDirectionL = true;
	isChangeDirectionR = false;
	waitRenderFirst += TPF;
}
void Mario::TurnRight(float TPF, float Max)
{
	// if press Right, Update _vx
	_m_Velocity.x += FRICTION_X * TPF;
	if (_m_Velocity.x >= Max)
		_m_Velocity.x = Max;
	isChangeDirectionR = true;
	isChangeDirectionL = false;
	waitRenderFirst += TPF;
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
	waitRenderFirst = 0;
}
void Mario::Jump(float TPF)
{
	if (timeJumped < 0.2)
	{
		_m_Velocity.y = -MARIO_VY;
		isJumping = true;
		_game->_audio->PlaySound(_game->_sound_Jump);
	}
}
void Mario::sExplosion(float TPF)
{
	if (isShotable == true)
	{
		if (waitbullet>1)
		{
			isShotting = true;
			BaseObject* obj = new Bullet(isChangeDirectionR ? _m_Position.x + 5 : _m_Position.x - 5, _m_Position.y, Camera::_cameraX, Camera::_cameraY, isChangeDirectionR ?160:-160, _sBullet, _sExplosion,_game);
			obj->SetState("_state", BS_ACTIVING);
			_game->_quadTree->Add(obj, false);
			_game->_audio->PlaySound(_game->_sound_FireBall);
			waitbullet = 0;
		}
		
	}
}
void Mario::Move(float TPF)
{
	waitIncreaseVecY += TPF;
	if (waitIncreaseVecY > 0.3)
	{
		_m_Velocity.y += 1;
		waitIncreaseVecY = 0;
	}
	_m_Position.y += _m_Velocity.y;
	_m_Position.x += _m_Velocity.x;
	if (_m_Position.x < Camera::_cameraX)									//Không cho đi quá Camera
		_m_Position.x = Camera::_cameraX;
	if (_m_Position.x > Camera::_cameraX + WIDTH)
		_m_Position.x = Camera::_cameraX + WIDTH;
	if (_m_Velocity.x != 0)
	{
		if (!isJumping)
		{
			if (waitRenderFirst < 0.5 && _m_Velocity.y == 0)
			{
				_sprite->setIndex(5);
				_sSmall_right->setIndex(2);
			}
			else 
			{
				if (isChangeDirectionL)
					_sprite->Next(2, 4, TPF);
				else if (isChangeDirectionR)
					_sSmall_right->Next(3, 5, TPF);
			}
		}
		else
		{
			_sprite->setIndex(1);
			_sSmall_right->setIndex(6);
		}
	}
	else
	{
		
		if (died)
		{
			_sprite->setIndex(1);
			_sSmall_right->setIndex(1);
		}
		else if (isJumping)
		{
			_sprite->setIndex(1);
			_sSmall_right->setIndex(6);
		}
		else
		{
			_sSmall_right->setIndex(0);
			_sprite->setIndex(7);
		}
	}
	_m_PostionOld = _m_Position;
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
			if (obj->_ID >= 17 && obj->_ID <= 22||obj->_ID==52) //collision with Brick and special brick
			{
				switch (dir)
				{
				case TOP:
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
     						obj->SetState("_state", TS_MOVEUP);
					}
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					//_m_Position.x = (int) _m_Position.x;
					isJumping = false;
					timeJumped = 0;
					break;
				}
			}
			if (obj->_ID >= 14 && obj->_ID <= 16)
			{
				_m_Velocity.y = 0;
				isJumping = false;
				timeJumped = 0;
			}
			if (obj->_ID == 51){
				switch (dir)
				{
				case TOP:
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
						obj->SetState("_state", TS_MOVEUP);
					}
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					isJumping = false;
					timeJumped = 0;
					break;
				}
			}
			
			if (obj->_ID == 36)				// collision with green mushroom
			{
				if (obj->GetState("_state") == TS_IDLE)			// nếu đang chờ thì đi lên
				{
					obj->SetState("_state", TS_MOVEUP);
				}
				if (obj->GetState("_state") == TS_MOVEUP)		// nếu đã đi lên rồi thì bị ăn
				{
					obj->SetState("_state", TS_BREAKED);
				}
			}
			// va chạm với ngôi sao
			if (obj->_ID == 35)				
			{
				if (obj->GetState("_state") == TS_IDLE)			// nếu đang chờ thì đi lên
				{
					obj->SetState("_state", TS_MOVEUP);
				}
				
			}
			if (obj->_ID == 32)				// collision with coin
			{
				if (dir == TOP)
				{
					if (obj->GetState("_state") == TS_IDLE)
						obj->SetState("_state", TS_ACTIVING);
				}
			}
			if (obj->_ID == 58)
			{
				obj->SetState("_state", TS_ACTIVING);
				_m_Position.x = obj->getPosition().x;
				yTemp = obj->getPosition().y + obj->_heightRect;
				ChangeState(M_PULL_FLAG);
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
		if (obj->_ID != 99)
		{
			DIR dir = Collision::getInstance()->isCollision(this, obj);
			if (dir != DIR::NONE){

				if (obj->_ID == 55)
				{
				if (dir == DIR::LEFT || dir == DIR::RIGHT || dir == DIR::TOP || dir == DIR::BOTTOM)
				_m_Position.x + 100;
				}
			}
		}
	}
	//--------------------
}
void Mario::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyborad)
{
	list<BaseObject*>::iterator i;
	switch (_state)
	{
	case M_NORMAL:
		Move(TPF);
		//if (_state != M_DIEING && _state != M_DIED)
		CheckCollision(staticObj, dynamicObj);
		ProcessInput(keyborad, TPF);
		if (_game->_coin >= 100)
		{
			_game->_coin = 0;
			_game->_life++;
			_game->_audio->PlaySound(_game->_sound_1up);
		}
		if (isShotable == true)
		{
			waitbullet += TPF;
		}
		if (isShotting == true)
		{
			waitShotting += TPF;
			if (waitShotting>0.2)
			{
				waitShotting -= 0.2;
				isShotting = false;
			}
		}
		// het thoi gian thi chet
		if (_game->_timeGame == 0)
		{

			ChangeState(M_DIEING);
		}
		if (isJumping == true)
		{
			timeJumped += TPF;
		}
		if (_m_Velocity.y > 0)
		{
			isJumping = true;
			timeJumped = 10;
		}
		//Thời gian bảo vệ khi bị thu nhỏ.
		if (isProtected == true)
		{
			waitProtect += TPF;
			if (waitProtect>2)
			{
				isProtected = false;
				isRender = true;
			}
		}
		if (isProtectedHidden == true)
		{
			waitProtectHidden += TPF;
			if (waitProtectHidden>0.5)
			{
				isProtectedHidden = false;
				waitProtectHidden -= 0.5;
			}
		}
		//Tạo sự nhấp nháy khi được bảo vệ.
		if (isProtected == true)
		{
			waitRender += TPF;
			if (waitRender>0.05)
			{
				waitRender -= 0.05;
				isRender = !isRender;
			}
		}
		break;
	case M_PULL_FLAG:
		_isVisiableKeyboard = false;
		for (i = staticObj->begin(); i != staticObj->end(); i++)
		{
			obj = *i;
			char flagState;
			switch (obj->_ID)
			{
			case 58:
				flagState = obj->GetState("_state");
				if (flagState == TS_ACTIVING)						//Khi cờ đang xuống...
				{
					_m_Velocity.x = 0;
					if (_m_Position.y > yTemp)			//... nếu Mario đã xuống tới nơi
						_m_Velocity.y = 0;
					else
						_m_Velocity.y = 0.1;
					
				}
				else if (flagState == TS_IDLE_2)					//Nếu cờ được kéo xuống hoàn toàn.
				{
					//isFaceRight = false;
					_m_Position.x = obj->getPosition().x + obj->_width + 1;
					_m_Position.y = yTemp;
					waitInFlag += TPF;							//Chờ để di chuyển tiếp
					if (waitInFlag>0.5)
					{
						waitInFlag = 0;
						ChangeState(M_AUTO_TO_CASTLE);
					}
				}
				
				break;
			}
			_m_Position.y += _m_Velocity.y;
		}
		
		break;
	case M_AUTO_TO_CASTLE:
		CheckCollision(staticObj, dynamicObj);
		_m_Velocity.x = 1;
		Move(TPF);
		for (i = staticObj->begin(); i != staticObj->end(); i++)
		{
			BaseObject *obj = *i;
			switch (obj->_ID)
			{
			case 23:				//Lâu đài
				DIR dir = Collision::getInstance()->isCollision(this, obj);
				if (dir != DIR::NONE){
					_game->ChangeState(GS_NEXT_STAGE);
				}
				break;
			}
		}
		break;
	case M_DIED:
		if (_m_Position.y > 500)
		{
			_game->_life--;
			_game->ChangeState(GS_REPLAY);
		}
			
		
		break;
	}
}
void Mario::Render()
{		
	if (isRender == false) return;
	if (isChangeDirectionL)
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (isChangeDirectionR)
		_sSmall_right->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	
}
void Mario::ProcessInput(KeyBoard* _keyboard, float TPF)
{
	if (_isVisiableKeyboard)
	{
		if (_keyboard->KeyDown(DIK_X))
			Jump(TPF);

		if (_keyboard->KeyDown(DIK_F))
			sExplosion(TPF);
		if (_keyboard->KeyDown(DIK_DOWN))		//Ngồi
		{
		}
		else if (_keyboard->KeyDown(DIK_RIGHT))
		{
			if (_keyboard->KeyDown(DIK_Z))
				TurnRight(TPF, MAX_MARIO_VX_);
			else
				TurnRight(TPF, _MARIO_VX_NORMAL);
		}
		else if (_keyboard->KeyDown(DIK_LEFT))
		{
			if (_keyboard->KeyDown(DIK_Z))
				TurnLeft(TPF, MAX_MARIO_VX_);
			else
				TurnLeft(TPF, _MARIO_VX_NORMAL);
		}
		else
		{
			Stand(TPF);
		}
	}

}

void Mario::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case M_DIEING:
		_m_Velocity.x = 0;
		_m_Velocity.y = -2;
		_game->_audio->StopSound(_game->_sound_Background);

		_game->_audio->PlaySound(_game->_sound_Die);
		ChangeState(M_DIED);
		died = true;
		_isVisiableKeyboard = false; //vo hieu ban phim khi sap chet
		break;
	
	}
}