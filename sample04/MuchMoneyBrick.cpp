﻿#include "MuchMoneyBrick.h"
#include "Global.h"



MuchMoneyBrick::MuchMoneyBrick() :BaseObject()
{
}
MuchMoneyBrick::MuchMoneyBrick(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_isChanged = false;
	_isNeedDelete = false;
	_isContainCoin = false;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_widthRect = _width;
	_heightRect = _height;
	_state = TS_IDLE;
	_moveupTime = 0.1;
	isFalling = false;
	_NumberOfCoin = 5;
	_currentSpriteIndex = 0;
}
void MuchMoneyBrick::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case TS_IDLE:		// reset lại
		_currentSpriteIndex = 0;
		_m_Position.y = Recent_Y;		// vị trí
		_moveupTime = 0.1;				// reset moveup time
		isFalling = false;				// trạng thái falling
		break;
	case TS_MOVEUP:
		
		if (_moveupTime > 0 && !isFalling){
			_moveupTime -= TPF;
			_m_Position.y -= 1;
		}
		if (_moveupTime <= 0){
			isFalling = true;
			
		}
		// nếu đang rơi thì moveupTime
		if (isFalling){
			_m_Position.y += 1;
			if (_m_Position.y > Recent_Y)		// nếu vị trí gạch lớn hơn vị trí ban đầu thì reset lại 
			{
				SetState("_state", TS_IDLE);	// về bình thường
				_NumberOfCoin--;
				if (_NumberOfCoin == 0)					// nếu hết tiền thì thành gạch sắt
					SetState("_state", TS_BREAKED);
			}
			
		}
		
		break;
	case TS_BREAKED:							// gạch bị đụng rồi
		_currentSpriteIndex = 3;
		_m_Position.y = Recent_Y;
		break;
	}
}
void MuchMoneyBrick::Render()
{
	_sprite->setIndex(_currentSpriteIndex);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
void MuchMoneyBrick::SetState(char* Name, int val)
{
	if (strcmp(Name, "_isChanged") == 0)
	{
		if (val == 0)
			_isChanged = false;
		else _isChanged = true;
		return;
	}
	if (strcmp(Name, "_state") == 0)
	{
		ChangeState(val);
		return;
	}
	if (strcmp(Name, "_isContainCoin") == 0)
		_isContainCoin = val;
}

int MuchMoneyBrick::GetState(char* Name)
{
	if (strcmp(Name, "_isChanged") == 0)
		return _isChanged;
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	if (strcmp(Name, "_isContainCoin") == 0)
		return _isContainCoin;
	return -1;
}

void MuchMoneyBrick::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case TS_IDLE:
	case TS_MOVEUP:
		break;
	}
}

