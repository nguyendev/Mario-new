﻿#include "InvisibleBrick.h"
#include "Global.h"


InvisibleBrick::InvisibleBrick() :BaseObject()
{
}
InvisibleBrick::InvisibleBrick(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_isChanged = false;
	_isNeedDelete = false;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_widthRect = _width;
	_heightRect = _height;
	_state = TS_IDLE;
	_moveupTime = 0.1;
	isFalling = false;
}

void InvisibleBrick::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case TS_IDLE:
		
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
				_m_Position.y = Recent_Y;	// vị trí
				_moveupTime = 0.1;			// reset moveup time
				SetState("_state", TS_BREAKED);// đổi trạng thái bị đụng
				isFalling = false;			// trạng thái falling
			}
		}
		break;
	case TS_BREAKED:		// bị đụng rồi
		_sprite->setIndex(3);
		break;
	}
}
void InvisibleBrick::Render()
{
	switch (_state)
	{
	case TS_IDLE:
		_sprite->setIndex(11);
		break;
	case TS_MOVEUP:
		_sprite->setIndex(3);
		break;
	case TS_BREAKED:
		_sprite->setIndex(3);
		break;
	}
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
void InvisibleBrick::SetState(char* Name, int val)
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
}

int InvisibleBrick::GetState(char* Name)
{
	if (strcmp(Name, "_isChanged") == 0)
		return _isChanged;
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}

void InvisibleBrick::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case TS_IDLE:
	case TS_MOVEUP:
		break;
	}
}