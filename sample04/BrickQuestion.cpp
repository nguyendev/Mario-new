﻿#include "BrickQuestion.h"
#include "Global.h"



BrickQuestion::BrickQuestion() :BaseObject()
{
}
BrickQuestion::BrickQuestion(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, CSprite* CoinSprite, int NumberOfCoins) : BaseObject(x, y, _cameraX, _cameraY)
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
	_moveupTime = MAX_MOVEUP_TIME;
	isFalling = false;
	_currentSprite = 0;
	_timeToFlicker = TIME_FLICKER;
	_NumberOfCoins = NumberOfCoins;
	coin = new Coin(x, y, _cameraX, _cameraY, 32, CoinSprite, NumberOfCoins);
}
void BrickQuestion::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	coin->Update(TPF, staticObj, dynamicObj, keyboard);
	switch (_state)
	{
	case TS_IDLE:				// trạng thái chờ thì nhấp nháy
		_timeToFlicker -= TPF;
		if (_timeToFlicker<0)
		{
			_currentSprite++;
			if (_currentSprite < 8 || _currentSprite >10)
				_currentSprite = 8;
			_timeToFlicker = TIME_FLICKER;		// reset thời gian nhấp nháy
		}
		// reset
		_m_Position.y = Recent_Y;				// vị trí
		_moveupTime = MAX_MOVEUP_TIME;						// reset moveup time
		isFalling = false;						// trạng thái falling
		coin->SetState("_state", TS_IDLE);		// reset đông tiền
		break;
	case TS_MOVEUP:
		coin->SetState("_state", TS_ACTIVING);
		// đi lên
		if (_moveupTime > 0 && !isFalling){
			_moveupTime -= TPF;
			// vận tốc âm
			_m_Velocity.y = -Y_VELOCITY_UP;
			_m_Position.y += _m_Velocity.y;
		}
		if (_moveupTime <= 0){
			isFalling = true;
		}
		
		// nếu đang rơi thì moveupTime 
		if (isFalling){
			_m_Velocity.y = Y_VELOCITY_UP;
			_m_Position.y += _m_Velocity.y;
			if (_m_Position.y > Recent_Y)			// nếu vị trí gạch lớn hơn vị trí ban đầu thì reset lại 
			{
				_m_Position.y = Recent_Y;			// vị trí
				_moveupTime = MAX_MOVEUP_TIME;		// reset moveup time
				_NumberOfCoins--;					// trừ tiền
				if (_NumberOfCoins>0)				// còn tiền
					SetState("_state", TS_IDLE);	// đổi trạng thái chờ
				else
					SetState("_state", TS_BREAKED);	// hết tiền => breaked
				isFalling = false;					// trạng thái falling
			}
		}
		break;
	case TS_BREAKED:							// gạch bị đụng rồi
		break;
	}
}
void BrickQuestion::Render()
{
	coin->Render();
	switch (_state)
	{
	case TS_IDLE:				// trạng thái chờ thì nhấp nháy
		break;
	case TS_MOVEUP:
		_currentSprite = 8;
		break;
	case TS_BREAKED:							// gạch bị đụng rồi
		_currentSprite = 3;
		break;
	}
	_sprite->setIndex(_currentSprite);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
void BrickQuestion::SetState(char* Name, int val)
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

int BrickQuestion::GetState(char* Name)
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

void BrickQuestion::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case TS_IDLE:
	case TS_MOVEUP:
		break;
	}
}

