#include "MuchMoneyBrick.h"
#include "Global.h"


MuchMoneyBrick::MuchMoneyBrick() :BaseObject()
{
}
MuchMoneyBrick::MuchMoneyBrick(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex)
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
	NumberOfCoins = 5;	// 5 đồng tiền
	_sprite->setIndex(0);
}

void MuchMoneyBrick::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state)
	{
	case TS_IDLE:
		_sprite->setIndex(0);
		break;
	case TS_MOVEUP:
		// đang đi lên
		if (_moveupTime > 0 && !isFalling){			
			_moveupTime -= TPF;
			_m_Position.y -= 1;
			NumberOfCoins--;		// số tiền trừ sau mỗi lần va chạm
		}
		// lên đỉnh
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
				SetState("_state", TS_IDLE);// đổi về trạng thái bình thường sau khi bị đụng
				isFalling = false;			// trạng thái falling
			}
		}
		if (NumberOfCoins==0)				// nếu hết tiền thì chuyển sang breaked
			SetState("_state", TS_BREAKED);
		break;
	case TS_BREAKED:		// bị đụng rồi
		_sprite->setIndex(3);
		break;
	}
}
void MuchMoneyBrick::Render()
{
	switch (_state)
	{
	case TS_IDLE:
		_sprite->setIndex(0);
		break;
	case TS_BREAKED:		// bị đụng rồi
		_sprite->setIndex(3);
		
		break;
	}
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