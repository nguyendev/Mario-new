#include "SpecialBrick.h"
#include "Global.h"



SpecialBrick::SpecialBrick() :BaseObject()
{
}
SpecialBrick::SpecialBrick(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, CSprite* ItemSprite) : BaseObject(x, y, _cameraX, _cameraY)
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
	isContainItem = true;										// đang chứa đồ

	if (_ID == 50)												// id gạch là 50 thì là sao
	{
		Item = new Star(x, y, _cameraX, _cameraY,37,ItemSprite);
		_currentSprite = 8;										// khởi tạo là gạch hỏi chấm
		_timeToFlicker = TIME_FLICKER;							// có thời gian nhấp nháy
	}
	else if (_ID == 52)		//.. 52 thì là nấm xanh
	{
		Item = new GreenMushRoom(x, y, _cameraX, _cameraY, 36, ItemSprite);
		_currentSprite = 11;									// khởi tạo tàng hình
	}
}
void SpecialBrick::Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	if (_ID == 50)								// là gạch hỏi chấm, sao
	{
		Item->Update(TPF, staticObj, dynamicObj, keyboard);// update sao
		switch (_state)
		{
		case TS_IDLE:							// trạng thái chờ thì nhấp nháy
			_timeToFlicker -= TPF;
			if (_timeToFlicker<0)
			{
				_currentSprite++;
				if (_currentSprite < 8 || _currentSprite >10)
					_currentSprite = 8;
				_timeToFlicker = TIME_FLICKER;	// reset thời gian nhấp nháy
			}
			// reset
			_m_Position.y = Recent_Y;			// vị trí
			_moveupTime = 0.1;					// reset moveup time
			isFalling = false;					// trạng thái falling
			break;
		case TS_MOVEUP:
			if (isContainItem)						// còn đang chứa đồ
			{
				Item->SetState("_state", TS_MOVEUP);// item đi ra ngoài viên gạch
				isContainItem = false;					// hết chứa đồ
			}
			
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
				if (_m_Position.y > Recent_Y)			// nếu vị trí gạch lớn hơn vị trí ban đầu thì reset lại 
				{
					_m_Position.y = Recent_Y;			// vị trí
					_moveupTime = 0.1;					// reset moveup time
					SetState("_state", TS_BREAKED);		// đổi trạng thái bị bể ( hết item
					isFalling = false;					// trạng thái falling

				}
			}

			break;
		case TS_BREAKED:							// gạch bị đụng rồi
			break;
		}
	}


	else if (_ID == 52)								// là gạch tàng hình
	{
		Item->Update(TPF, staticObj, dynamicObj, keyboard);// update nấm xanh
		switch (_state)
		{
		case TS_IDLE:
			break;
		case TS_MOVEUP:
			if (isContainItem)						// còn đang chứa đồ
			{
				Item->SetState("_state", TS_MOVEUP);// item đi ra ngoài viên gạch
				isContainItem = false;				// hết chứa đồ
			}
			

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
				if (_m_Position.y > Recent_Y)			// nếu vị trí gạch lớn hơn vị trí ban đầu thì reset lại 
				{
					_m_Position.y = Recent_Y;			// vị trí
					_moveupTime = 0.1;					// reset moveup time
					SetState("_state", TS_BREAKED);		// đổi trạng thái bị bể ( hết item
					isFalling = false;					// trạng thái falling

				}
			}
			break;
		case TS_BREAKED:							// gạch bị đụng rồi
			break;
		}
	}
	
}
void SpecialBrick::Render()
{
	Item->Render();									// luôn vẽ item
	if (_ID == 50)									// gạch chứa sao
	{
		switch (_state)
		{
		case TS_IDLE:								// trạng thái chờ thì nhấp nháy
			break;
		case TS_MOVEUP:
			_currentSprite = 3;
			break;
		case TS_BREAKED:							// gạch bị đụng rồi
			_currentSprite = 3;
			break;
		}
		_sprite->setIndex(_currentSprite);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
	}
	else if (_ID == 52)								// gạch tàng hình chứa nấm xanh
	{
		switch (_state)
		{
		case TS_IDLE:								// trạng thái chờ thì tàng hình
			_currentSprite = 11;
			break;
		case TS_MOVEUP:
			_currentSprite = 3;
			break;
		case TS_BREAKED:							// gạch bị đụng rồi
			_currentSprite = 3;
			break;
		}
		_sprite->setIndex(_currentSprite);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
	}
}
void SpecialBrick::SetState(char* Name, int val)
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

int SpecialBrick::GetState(char* Name)
{
	if (strcmp(Name, "_isChanged") == 0)
		return _isChanged;
	if (strcmp(Name, "_state") == 0)
		return _state;
	if (strcmp(Name, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}

void SpecialBrick::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case TS_IDLE:
	case TS_MOVEUP:
		break;
	}
}

