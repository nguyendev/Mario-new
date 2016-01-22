#include "Bullet.h"
#include "BaseObject.h"
#include "Collision.h"
#include "Global.h"
#include "Sprite.h"
#include "Mario.h"
#include "GameMario.h"
Bullet::Bullet() :BaseObject(){}
Bullet::Bullet(float x, float y, float _cameraX, float _cameraY, float vx, CSprite *sprite, CSprite* sprite1, CGameMario* game, int ID) : BaseObject(x, y, _cameraX, _cameraY)
{
	_game = game;
	_sprite = sprite;
	_sprite1 = sprite1;
	_isNeedDelete = false;
	timedelay = 0;
	timeblow = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_widthRect = _width;
	_heightRect = _height;
	_m_Velocity.x = 0;
	ax = vx;
	_m_Velocity.y = ay = 0;
	
	waitIncreaseVecY = 0;
	_sprite->setIndex(0);
	_ID = ID;
	if (_ID == 99)
	{
		_state = BS_IDLE;
	}
	else
		_state = BS_IDLE_2;
}

Bullet::~Bullet(void)
{

}
void Bullet::Move(float TPF, list<BaseObject*> *staObjs, list<BaseObject*> *dynObjs)
{
	BaseObject* _obj;
	//theo phuong x
	_m_Velocity.x = ax *TPF;
	_m_Position.x += _m_Velocity.x; 
	list<BaseObject*>::iterator i;
	for (i = staObjs->begin(); i != staObjs->end(); i++)
	{
		_obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, _obj);
		if (dir != DIR::NONE)
		{
			if (_obj->_ID >= 14 && _obj->_ID <= 22) //collision with Brick and special brick
			{
				if (dir == LEFT || dir == RIGHT)
				{
					_m_Velocity.x = 0;
					SetState("_state", BS_BLOW);
					_game->_audio->PlaySound(_game->_sound_Bump);
				}
			}
		}
		//else if (_obj->_ID == 29)
		//{
		//	if (_m_Position.x >= _obj->getPosition().x + 30)
		//		SetState("_state", BS_BLOW);
		//}
	}
	//Theo phương y
	if (_state != BS_BLOW)
	{
		waitIncreaseVecY += TPF;
		if (waitIncreaseVecY > 0.05)
		{
			_m_Velocity.y += 0.2;
			waitIncreaseVecY = 0;
		}
		_m_Position.y += _m_Velocity.y;
		for (i = staObjs->begin(); i != staObjs->end(); i++)
		{
			_obj = *i;
			DIR dir = Collision::getInstance()->isCollision(this, _obj);
			if (dir != DIR::NONE)
			{		
				if (_obj->_ID >= 14 && _obj->_ID <= 22) //collision with Brick and special brick
				{
					if (dir == BOTTOM)
					{
						_m_Velocity.y = -1.5;
					}
				}
			}
		}



		// check collision with dynamicObject
		for (i = dynObjs->begin(); i != dynObjs->end(); i++)
		{
			_obj = *i;
			if (_obj->_ID == 53 || _obj->_ID == 55)
			{
				DIR dir = Collision::getInstance()->isCollision(this, _obj);
				if (dir != DIR::NONE)
				{
					if (_obj->_ID == 53 || _obj->_ID == 55)
					{
						SetState("_state", BS_BLOW);
						_obj->SetState("_state", ES_SHOOTED);
					}
						
					
				}
			}
		}
		
	}
	// delete bullet when out camera
	if (getPosition().x > Camera::_cameraX + WIDTH + 100|| getPosition().x < Camera::_cameraX - 20)
		SetState("_state", BS_BLOW);
	//xOld = x;
	//yOld = y;
	NewRect();
}
void Bullet::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case BS_ACTIVING:
		_m_Velocity.y = 1.5;
		break;
	case BS_BLOWED:
		_isNeedDelete = true;
		break;
	}
}
void Bullet::SetState(char* varName, int val)
{
	if (strcmp(varName, "_state") == 0)
	{
		ChangeState(val);
	}
}
int Bullet::GetState(char *varName)
{
	if (strcmp(varName, "_state") == 0)
		return _state;
	if (strcmp(varName, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}
void Bullet::Render()
{
	switch (_state)
	{
	case BS_ACTIVING:
		//_sprite->Render(_m_Position.x - 11, _m_Position.y - 12,_cameraX, _cameraY, 0.5);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
		break;
	case BS_BLOW:
		_sprite1->Render(_m_Position.x + 3, _m_Position.y, Camera::_cameraX, Camera::_cameraY, DYNAMIC_DEEP);
		break;
	}
}
void Bullet::Update(float TPF, list<BaseObject*>* staObjs, list<BaseObject*>* dynObjs, KeyBoard* input)
{
	switch (_state)
	{
	case BS_ACTIVING:
		Move(TPF, staObjs, dynObjs);
		_sprite->Next(0, 3, TPF);
		break;
	case BS_BLOW:
		//ani = new Animation(3, 1, 0, sprite1);
		timeblow += TPF;
		if (timeblow>0.1)
			_sprite1->setIndex(1);
		if (timeblow>0.2)
			_sprite1->setIndex(2);
		timedelay += TPF;
		if (timedelay>0.3)
			SetState("_state", BS_BLOWED);
		break;
	case BS_BLOWED:
		_isNeedDelete = true;
		break;
	}
}