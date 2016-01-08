#include "Coin.h"


Coin::Coin()
{
}
Coin::Coin(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite, int NumberOfCoins) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Position.x = x;
	_m_Position.y = y;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_heightRect = _height;
	_widthRect = _width-1;
	_currentSprite = 7;			// tàng hình
	timeFly = MAX_TIME_FLY;
	_state = TS_IDLE;
	_timeOfEachSprite = 0;
	_NumberOfCoins = NumberOfCoins;
}
void Coin::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	switch (_state){
	case TS_IDLE:
		// reset vị trí, sprite, thời gian bay.
		_m_Position.x = RecentX;
		_m_Position.y = RecentY;
		_currentSprite = 7;
		timeFly = MAX_TIME_FLY;
		break;
	case TS_ACTIVING:
		

		// xử lý vị trí 
		if (timeFly > MAX_TIME_FLY*0.75 ){	// flying up
			_m_Position.y -= 4;
			timeFly-=TPF;			
		}
		else if (timeFly <= MAX_TIME_FLY *0.25 && timeFly > 0){	// falling down
			_m_Position.y += 4;
			timeFly-=TPF;
		}
		else								// hết bay: timefly<=0
		{
			_NumberOfCoins--;				// Tiền giảm 1
			if (_NumberOfCoins>0)			// còn tiền
				SetState("_state", TS_IDLE);// chuyển về chờ	
			else							// hết tiền
			{
				SetState("_state", TS_BREAKED);// chuyển về break.
			}
		}
		break;
	case TS_BREAKED:
		_isNeedDelete = true;
		break;
	}

}
void Coin::Render()
{
	switch (_state){
	case TS_IDLE:
		_sprite->setIndex(3);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
		break;
	case TS_ACTIVING:
		_currentSprite--; 
		if (_currentSprite <2 || _currentSprite>6)
			_currentSprite = 6;
		_sprite->setIndex(_currentSprite);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
		
		
			
		break;
	case TS_BREAKED:
		break;
	}
	
}

void Coin::SetState(char* Name, int val)
{
	ChangeState(val);
}

int Coin::GetState(char* Name)
{
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}
void Coin::ChangeState(char state)
{
	_state = state;
}
Coin::~Coin()
{
}
