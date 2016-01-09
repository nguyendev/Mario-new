#include "Brick.h"
#include "Global.h"



Brick::Brick() :BaseObject()
{
}
Brick::Brick(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex, bool isBright) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_isChanged = false;
	_isNeedDelete = false;
	_isContainCoin = false;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	_widthRect = _width;
	_heightRect = _height;
	_state = TS_IDLE;
	_isBright = isBright;
	_moveupTime = 0.1;
	isFalling = false;
}
void Brick::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case TS_IDLE:
		break;
	case TS_MOVEUP:
		if (_moveupTime > 0&&!isFalling){
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
				SetState("_state", TS_IDLE);// đổi trạng thái sang chờ.
				isFalling = false;			// trạng thái falling
			}
		}
		break;
	case TS_BREAKING:
		_xBreak1 += _vxBreak1*TPF;
		_xBreak2 += _vxBreak2*TPF;
		_vyBreak1 += _ayBreak*TPF;
		_vyBreak2 += _ayBreak*TPF;
		_yBreak1 += _vyBreak1*TPF + 0.5*_ayBreak*TPF*TPF;
		_yBreak2 += _vyBreak2*TPF + 0.5*_ayBreak*TPF*TPF;
		if (_yBreak1>_m_Position.y + 600)
			ChangeState(TS_BREAKED);
		if (_angle<2 * PI)
			_angle += 0.2;
		else _angle = 0;
		break;
	}
	NewRect();
}
void Brick::Render()
{
	
	if (_state != TS_BREAKING)
	{
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
	}
	else{
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_xBreak1, _yBreak1, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		_sprite->Render(_xBreak2, _yBreak2, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		_sprite->Render(2 * _m_Position.x - _xBreak1, _yBreak1, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		_sprite->Render(2 * _m_Position.x - _xBreak2,_yBreak2, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
//				_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
	}
}
void Brick::SetState(char* Name, int val)
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

int Brick::GetState(char* Name)
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

void Brick::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case TS_IDLE:
	case TS_MOVEUP:

	case TS_BREAKING:
		_xBreak1 = _xBreak2 = _m_Position.x;
		_yBreak1 = _m_Position.y;
		_yBreak2 = _m_Position.y;
		_vyBreak1 = -900;
		_vyBreak2 = -600;
		_vxBreak1 = 150;
		_vxBreak2 = 100;
		_ayBreak = Gy;
		break;
	case TS_BREAKED:
		_isNeedDelete = true;
	}
}