#include "Mario.h"
#include "Global.h"
#include "Collision.h"
#include "GameMario.h"

#define MARIO_VY	2.6f	//velocity Y of mario
#define _MARIO_VX_NORMAL 1.5f	//max velocity of mario
#define MAX_MARIO_VX_	2.5f
#define GRAVITY		1.0f	//gravity ratio
#define FRICTION_X	1.25f   //friction of mario
Mario::Mario() :BaseObject(){};
Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sbig_right, CSprite* sbig_left, CSprite* ssmall_right, CSprite* ssmall_left, CSprite* sbullet, CSprite* sExplosion, CGameMario* game) :BaseObject(x, y, cameraX, cameraY)
{
	_game = game;
	_sprite = ssmall_right;
	_sSmall_right = ssmall_left;
	_sBig_left = sbig_right;
	_sBig_right = sbig_left;
	_sBullet = sbullet;
	_sExplosion = sExplosion;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_widthRect = _width;
	_heightRect = _height;
	isCanJump = false;
	timeJumped = 0;
	isJumping = false;
	_m_Velocity = D3DXVECTOR2(0,0);
	waittime = 0; 
	waitIncreaseVecY = 0;
	_m_PostionOld = _m_Position;
	isChangeDirectionL = false;
	isChangeDirectionR = true;
	waitRenderFirst = 0;
	_state = M_NORMAL;
	_isVisiableKeyboard = true;
	died = false;
	isBig = false;
	isShotable = false;
	waitbullet = 0;
	isShotting = false;
	waitShotting = 0;
	isProtected = false;
	isProtectedHidden = false;
	waitRender = 0;
	waitProtectHidden = 0;
	waitProtect = 0;
	isRender = true;
	waitInFlag = 0;
	isHasStar = false;
	_selectRowBig = 0;
	waitLostStar = 0;
	_watingNextState = 0;
	SetBox();
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
	waitIncreaseVecY += TPF;
	//waitIncreaseVecY += TPF;
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
	waitIncreaseVecY += TPF;
	//waitIncreaseVecY += TPF;
	_m_Velocity.x += FRICTION_X * TPF;
	if (_m_Velocity.x >= Max)
		_m_Velocity.x = Max;
	isChangeDirectionR = true;
	isChangeDirectionL = false;
	waitRenderFirst += TPF;
}
void Mario::Stand(float TPF)
{
	//waitIncreaseVecY += TPF;
	//Giam toc do xuong khi khong bam phim
	if (_m_Velocity.x < 0.0f)
		_m_Velocity.x += FRICTION_X / 2 * TPF;
	else if (_m_Velocity.x > 0.0f)
		_m_Velocity.x -= FRICTION_X / 2 * TPF;
	if ((_m_Velocity.x <= 1.5f) && (_m_Velocity.x >= -1.5f))
		_m_Velocity.x = 0.0f;
	waitRenderFirst = 0;
}
float Mario::Jump(float TPF)
{
	if (timeJumped < 0.2)
	{
		_m_Velocity.y = -MARIO_VY;
		isJumping = true;
		_game->_audio->PlaySound(_game->_sound_Jump);
	}
	return _m_Velocity.y;
}
void Mario::sExplosion(float TPF)
{
	if (isShotable == true)
	{
		if (waitbullet>0.5)
		{
			isShotting = true;
			BaseObject* obj = new Bullet(isChangeDirectionR ? _m_Position.x + 5 : _m_Position.x - 5, _m_Position.y, Camera::_cameraX, Camera::_cameraY, isChangeDirectionR ?200:-200, _sBullet, _sExplosion,_game);
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
	
	_m_PostionOld = _m_Position;
}
void Mario::SetBox()
{
	if (isBig)
	{
		_widthRect = 14;
		_heightRect = 30;
	}
	else
	{
		_widthRect = 14;
		_heightRect = 14;
	}
}
void Mario::UpdateSprite(float TPF)
{
	switch (_state)
	{
	case M_NORMAL: case M_AUTO_TO_CASTLE :case M_DIEING:case M_DIED:
		if (isHasStar)
			_selectRowBig = rand() % 4;
		else if (!isBig)
			_selectRowBig = 0;
		if (_m_Velocity.x != 0)
		{
			if (!isJumping)
			{
				if (waitRenderFirst < 0.5 && _m_Velocity.y == 0)
				{
					if (isBig)
					{
						_sBig_left->setIndex(5 + 8 * _selectRowBig);
						_sBig_right->setIndex(2 + 8 * _selectRowBig);
					}
					else
					{
						_sprite->setIndex(5 + 8 * _selectRowBig);
						_sSmall_right->setIndex(2 + 8 * _selectRowBig);
					}
				}
				else
				{
					if (isBig)
					{
						if (isChangeDirectionL)
						{
							_sBig_left->Next(2 + 8 * _selectRowBig, 4 + 8 * _selectRowBig, TPF);
						}
							
						else if (isChangeDirectionR)
						{
							_sBig_right->Next(3 + 8 * _selectRowBig, 5 + 8 * _selectRowBig, TPF);
						}
					}
					else
					{
						if (isChangeDirectionL)
							_sprite->Next(2, 4, TPF);
						else if (isChangeDirectionR)
							_sSmall_right->Next(3, 5, TPF);
					}
				}
			}
			else
			{
				if (isBig)
				{
						_sBig_left->setIndex(1 + 8* _selectRowBig);
						_sBig_right->setIndex(6 + 8 * _selectRowBig);
				}
				else
				{
					_sprite->setIndex(1 + 8 * _selectRowBig);
					_sSmall_right->setIndex(6 + 8 * _selectRowBig);
				}
			}
		}
		else
		{
			if (died)
			{
				if (isBig)
				{
					if (isShotable)
					{
						_sBig_left->setIndex(9 + 8 * _selectRowBig);
						_sBig_right->setIndex(9 + 8 * _selectRowBig);
					}
					else
					{
						_sBig_left->setIndex(1 + 8 * _selectRowBig);
						_sBig_right->setIndex(1 + 8 * _selectRowBig);
					}
					
				}
				else
				{
					_sprite->setIndex(1 + 8 * _selectRowBig);
					_sSmall_right->setIndex(1 + 8 *_selectRowBig);
				}

			}
			else if (isJumping)
			{
				if (isBig)
				{
					if (isShotable)
					{
						_sBig_left->setIndex(7 + 8 * _selectRowBig);
						_sBig_right->setIndex(14 + 8 * _selectRowBig);
					}
					else
					{
						_sBig_left->setIndex(1 + 8 * _selectRowBig);
						_sBig_right->setIndex(6 + 8 * _selectRowBig);
					}
					
				}
				else
				{
					_sprite->setIndex(1 + 8 * _selectRowBig);
					_sSmall_right->setIndex(6 + 8 * _selectRowBig);
				}
			}
			else
			{
				if (isBig)
				{

					_sBig_left->setIndex(6 + 8 * _selectRowBig);
					_sBig_right->setIndex(1 + 8 * _selectRowBig);
				}
				else
				{
					_sSmall_right->setIndex(0 + 8 * _selectRowBig);
					_sprite->setIndex(7 + 8 * _selectRowBig);
				}

			}
		}
		break;
	case M_PULL_FLAG:
		if (isBig)
		{
			if (isShotable == true)
			{
				_sBig_left->setIndex(8 + 8 * _selectRowBig);
				_sBig_right->setIndex(15 + 8 * _selectRowBig);
			}
			else
			{
				_sBig_left->setIndex(0 + 8 * _selectRowBig);
				_sBig_right->setIndex(7 + 8 * _selectRowBig);
			}
			
		}
		else
		{
			_sSmall_right->setIndex(7 + 8 * _selectRowBig);
			_sprite->setIndex(0 + 8 * _selectRowBig);
		}
		break;
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
		if (dir != DIR::NONE)
		{
			if (obj->_ID >= 17 && obj->_ID <= 22 && obj->_ID !=19 || obj->_ID == 39) //collision with Brick and special brick
			{
				_m_Velocity = Collision::getInstance()->getVelocity();
				switch (dir)
				{
				case TOP:
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
						if (isBig)
							obj->SetState("_state", TS_BREAKING);
						else
     						obj->SetState("_state", TS_MOVEUP);
					}
					break;
				case BOTTOM:	
					_m_Velocity.y = 0;
					isJumping = false;
					timeJumped = 0;
					break;
				}
			}
			if (obj->_ID == 19) // collistion with coin
			{
				_m_Velocity = Collision::getInstance()->getVelocity();
				switch (dir)
				{
				case TOP:
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
						obj->SetState("_state", TS_MOVEUP);
						_game->AddScore(100, obj->getPosition().x, obj->getPosition().y - 3);
						_game->_coin++;
						_game->_audio->PlaySound(_game->_sound_Coin);
					}
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					isJumping = false;
					timeJumped = 0;
					break;
				}
					
			}
			if (obj->_ID >= 14 && obj->_ID <= 16)// collision with Pipe
			{
				if (dir == BOTTOM){
					_m_Velocity.y = 0;
					isJumping = false;
					timeJumped = 0;
				}
				_game->_audio->PlaySound(_game->_sound_Warp);
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
					_m_Position = _m_PostionOld;
					break;
				case BOTTOM:
					_m_Velocity.y = 0;
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					isJumping = false;
					timeJumped = 0;
					_m_Position = _m_PostionOld;
					break;
				}
			}
			if (obj->_ID == 2)
			{
				_game->_audio->LoopSound(_game->_sound_Die);
				ChangeState(M_DIED);
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
					_m_Position.y += 8;
					isBig = true;
					_game->_audio->PlaySound(_game->_sound_Powerup);
				}
			}		
			if (obj->_ID == 58)
			{
				if (obj->GetState("_state") == TS_IDLE)
				{
					obj->SetState("_state", TS_ACTIVING);
					_m_Position.x = obj->getPosition().x;
					yTemp = obj->getPosition().y + obj->_height * 9;
					if (_m_Position.y == yTemp)
						_game->AddScore(5000, obj->getPosition().x, obj->getPosition().y - 3);
					else
						_game->AddScore(400, obj->getPosition().x, obj->getPosition().y - 3);
					ChangeState(M_PULL_FLAG);
				}					
			}
			if (obj->_ID == 59) //collision with Brick mushroom
			{
				switch (dir)
				{
				case BOTTOM:
					_m_Velocity.y = 0;
					isJumping = false;
					timeJumped = 0;
					break;
				case TOP:
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
						// đụng gạch nấm thì cho cho nó sang moveup
						
						if (!isBig)
						{
							// tạo mushroom nấm đỏ: id = 33.
							BaseObject* mushroom = new MushRoom(obj->getPosition().x, obj->getPosition().y, _cameraX, _cameraY, 33, _game->_sprites[S_FUNGI]);
							// thêm vào quadtree.
							_game->_quadTree->Add(mushroom, false);
							mushroom->SetState("_state", TS_MOVEUP);
							_game->AddScore(1000, obj->getPosition().x, obj->getPosition().y - 3);
							// gạch 
							
						}
						else
						{
							// tạo hoa: id = 34.
							BaseObject* mushroom = new MushRoom(obj->getPositionX(), obj->getPositionY(), _cameraX, _cameraY, 34, _game->_sprites[S_FUNGI]);
							// thêm vào quadtree.
							_game->_quadTree->Add(mushroom, false);
							mushroom->SetState("_state", TS_MOVEUP);
							// gạch 
						}
						obj->SetState("_state", TS_MOVEUP);
					}
					break;
				}
			}
			if (obj->_ID == 50) //va chạm gạch tàng hình
			{
				switch (dir)
				{
				case TOP:
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
						BaseObject* mushroom = new GreenMushRoom(obj->getPositionX(), obj->getPositionY(), _cameraX, _cameraY, 36, _game->_sprites[S_FUNGI]);
						// thêm vào quadtree.
						_game->_quadTree->Add(mushroom, false);
						mushroom->SetState("_state", TS_MOVEUP);
						// gạch 
						obj->SetState("_state", TS_MOVEUP);
					}
					break;
				case BOTTOM:
					break;
				}
			}
			if (obj->_ID == 52) //va chạm gạch sao
			{
				switch (dir)
				{
				case TOP:
					_m_Velocity = Collision::getInstance()->getVelocity();
					this->setVelocity(this->getVelocity().x, this->getVelocity().y*-1);
					if (obj->GetState("_state") == TS_IDLE)
					{
						BaseObject* mushroom = new Star(obj->getPositionX(), obj->getPositionY(), _cameraX, _cameraY, 37, _game->_sprites[S_FUNGI]);
						// thêm vào quadtree.
						_game->_quadTree->Add(mushroom, false);
						mushroom->SetState("_state", TS_MOVEUP);
						// gạch 
						obj->SetState("_state", TS_MOVEUP);
					}
					break;
				}
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
			
			if (dir != DIR::NONE)
			{
				switch (obj->_ID)
				{
				case 33: //nấm biến lớn
					isBig = true;
					obj->_isNeedDelete = true;
					_game->_audio->PlaySound(_game->_sound_Powerup);
					_selectRowBig = 0;
					SetBox();
					break;
				case 34: // bông hoa
					obj->_isNeedDelete = true;
					if (isBig)
					{
						isShotable = true;
						_selectRowBig = 1;
					}
					else
					{
						isBig = true;
						_selectRowBig = 0;
					}	
					_game->AddScore(1000, obj->getPosition().x, obj->getPosition().y - 3);
					_game->_audio->PlaySound(_game->_sound_Powerup);
					SetBox();
					break;
				case 36: // nam xanh an mang
					_game->_audio->PlaySound(_game->_sound_1up);
					obj->_isNeedDelete = true;
					_game->_life++;
					break;
				case 37:
					isHasStar = true;
					//_game->_audio->PlaySound(_game->_so)
					obj->_isNeedDelete = true;
					waitRender = 0;
					break;
					//case 51 duoc 100 da 400
				case 55:
					if (isHasStar == false)							//Nếu không có sao
					{
						if (obj->GetState("_state") == ES_ACTIVING)		// nếu đang đi
						{
							if (dir == BOTTOM)									// bị dậm trên đầu
							{
								isProtectedHidden = true;
								_game->AddScore(100, obj->getPosition().x, obj->getPosition().y - 3);
								_m_Velocity.y = -MARIO_VY / 2;
								obj->SetState("_state", ES_CRASHED);		// chuyển sang trạng thái bị crash
								_game->_audio->PlaySound(_game->_sound_Squish);
								_game->AddScore(100, obj->getPosition().x, obj->getPosition().y);
							}
							else
							{
								CollisionEnemy();
								obj;
							}
								
						}
					}
					else if (obj->GetState("_state") != ES_CRASHED)
					{
						obj->_isNeedDelete = true;
						//obj->SetState("_state", ES_CRASHED);
						_game->_audio->PlaySound(_game->_sound_Squish);
					}
					break;
				}
			}
		}
	}
	//--------------------
}
void Mario::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyborad)
{
	list<BaseObject*>::iterator i;
	UpdateSprite(TPF);
	switch (_state)
	{
	case M_NORMAL:
		Move(TPF);
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
			if (waitProtect>3)
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
		//Khi có sao
		if (isHasStar)
		{
			waitLostStar += TPF;
			if (waitLostStar >= 10)
			{
				waitLostStar = 0;
				isHasStar = false;
				_selectRowBig = 0;
			}
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
		CheckCollision(staticObj, dynamicObj);
		for (i = staticObj->begin(); i != staticObj->end(); i++)
		{
			obj = *i;
			char flagState;
			switch (obj->_ID)
			{
			case 58:
				flagState = obj->GetState("_state");
				Move(TPF);
				if (flagState == TS_IDLE_2)					//Nếu cờ được kéo xuống hoàn toàn.
				{
					//isFaceRight = false;
					_m_Position.x = obj->getPosition().x + obj->_width + 3;
					_m_Position.y = yTemp;
					waitInFlag += TPF;							//Chờ để di chuyển tiếp
					if (waitInFlag>0.5)
					{
						waitInFlag = 0;
						_m_Velocity.x = 1;
						ChangeState(M_AUTO_TO_CASTLE);
						break;
					}
				}
				else						//Khi cờ đang xuống...
				{
					_m_Velocity.x = 0;
					_m_Position.x = obj->getPosition().x - obj->_width/2 +1;
					if (_m_Position.y > yTemp)			//... nếu Mario đã xuống tới nơi
						_m_Velocity.y = 0;
					else
						_m_Velocity.y = 0.5;
				}
				break;
			}
		}
		break;
	case M_AUTO_TO_CASTLE:
		CheckCollision(staticObj, dynamicObj);
		Move(TPF);
		for (i = staticObj->begin(); i != staticObj->end(); i++)
		{
			obj = *i;
			switch (obj->_ID)
			{
			case 5:				//Lâu đài
				DIR dir = Collision::getInstance()->isCollision(this, obj);
				if (dir != DIR::NONE){
					ChangeState(M_WATING_NEXT_STATE);
				}
				break;
			}
		}
		break;
	case M_WATING_NEXT_STATE:
		if (_watingNextState > 30)
		{
			_game->ChangeState(GS_NEXT_STAGE);
			_watingNextState = 0;
			_game->_audio->StopSound(_game->_sound_Win);
		}
		else
		{
			_watingNextState += TPF;
			if (_game->_timeGame > 0)
			{
				_game->_score += 50;
				_game->_timeGame--;
				_game->_audio->PlaySound(_game->_sound_Win);
			}
			else
			{
				_game->_timeGame = 0;
			}
		}
		break;
	case M_DIED:
		Move(TPF);
		if (_m_Position.y > 400)
		{
			_game->_life--;
			if (_game->_life >= 0)
				_game->ChangeState(GS_REPLAY);
			else
				_game->ChangeState(GS_GAMEOVER);
		}
		_game->_audio->StopSound(_game->_sound_Background);
		break;
	}
	NewRect();
}
void Mario::Render()
{		
	if (isRender == false) return;
	if (isChangeDirectionL)
	{
		if (isBig)
			_sBig_left->Render(_m_Position.x, _m_Position.y + 8, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
		else
			_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);

	}
	else if (isChangeDirectionR)
	{
		if (isBig)
			_sBig_right->Render(_m_Position.x, _m_Position.y+ 8, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
		else
			_sSmall_right->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	}
}
void Mario::CollisionEnemy()
{
	if (isBig == true)	//Lớn sẽ bị thu nhỏ
	{
		isBig = false;
		isProtected = true;
		waitProtect = 0;
		waitRender = 0;
		isShotable = false;
		SetBox();
	}
	else ChangeState(M_DIEING);

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
	
	//Nếu còn được bảo vệ thì không cho chết.
	if (_state == M_NORMAL && (isProtectedHidden == true || isProtected == true) && state == M_DIEING)
		return;
	_state = state;
	switch (_state)
	{
	case M_PULL_FLAG:
		_m_Velocity.y = 1;
		break;
	case M_DIEING:
		_m_Velocity.x = 0;
		_isVisiableKeyboard = false; //vo hieu ban phim khi sap chet
		_m_Velocity.y = -2;
		_game->_audio->StopSound(_game->_sound_Background);
		_game->_audio->PlaySound(_game->_sound_Die);
		died = true;
		ChangeState(M_DIED);
		
		break;
	
	}
}

void Mario::EatCoin(float _x, float _y)
{
	_game->_coin++;
	_game->AddScore(200, _x, _y - 3);
}