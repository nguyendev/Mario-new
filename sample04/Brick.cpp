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
	
	_widthRect = _width;
	_heightRect = _height;
	_state = TS_IDLE;
	_isBright = isBright;
	_moveupTime = MAX_MOVEUP_TIME;
	isFalling = false;
	// khởi tạo vận tốc đi lên cho gạch
	// khởi tạo 2 mảnh gạch
	SmallPiece1 = new BaseObject(x, y, _cameraX, _cameraY);
	SmallPiece2 = new BaseObject(x, y, _cameraX, _cameraY);
	// tâm:
	CenterX = x + _width / 2;
	// khởi tạo màu gạch
	if (_isBright==false)			// tối màu
		_SpriteIndex = 0;
	else					// sáng màu
		_SpriteIndex = 4;
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
			// vận tốc âm
			_m_Velocity.y = -Y_VELOCITY_UP;
			_m_Position.y += _m_Velocity.y;
		}
		if (_moveupTime <= 0){
			isFalling = true;
		}
		// nếu đang rơi thì moveupTime
		if (isFalling){
			// Vận tốc dương
			_m_Velocity.y = Y_VELOCITY_UP;
			_m_Position.y += _m_Velocity.y;
			if (_m_Position.y > Recent_Y)		// nếu vị trí gạch lớn hơn vị trí ban đầu thì reset lại 
			{
				_m_Position.y = Recent_Y;	// vị trí
				_moveupTime = MAX_MOVEUP_TIME;			// reset moveup time
				SetState("_state", TS_IDLE);// đổi trạng thái sang chờ.
				isFalling = false;			// trạng thái falling
			}
		}
		break;
	case TS_BREAKING:						// đang bị vỡ
		// đang bay lên
		if (_moveupTime > 0 && !isFalling){
			// vận tốc lớn hơn 0
			_m_Velocity.y = Y_VELOCITY_UP;
			_moveupTime -= TPF;
			// gạch 1
			SmallPiece1->_m_Position.x -= SPEED_OF_BRICK_PIECE_X;
			SmallPiece1->_m_Position.y -= SPEED_OF_BRICK_PIECE_Y;
			// gạch 2 
			SmallPiece2->_m_Position.x -= SPEED_OF_BRICK_PIECE_X;
			SmallPiece2->_m_Position.y -= SPEED_OF_BRICK_PIECE_Y/2;
			
		}
		// các mảnh đang rơi
		else if (_moveupTime <= 0 && _moveupTime>-MAX_MOVEUP_TIME*3){
			_moveupTime -= TPF;
			// gạch 1
			SmallPiece1->_m_Position.y += SPEED_OF_BRICK_PIECE_Y;
			SmallPiece1->_m_Position.x -= SPEED_OF_BRICK_PIECE_X;
			// gạch 2 
			SmallPiece2->_m_Position.y += SPEED_OF_BRICK_PIECE_Y / 3;
			SmallPiece2->_m_Position.x -= SPEED_OF_BRICK_PIECE_X;
		}
		if (_moveupTime < -MAX_MOVEUP_TIME*3)
		{
			SetState("_state", TS_BREAKED);
		}
		break;	
	case TS_BREAKED:						//đã bị vỡ
		_isNeedDelete = true;
		break;
	}
}
void Brick::Render()
{
	if (this->_ID == 5 || this->_ID == 2 || this->_ID == 3|| this ->_ID == 4)
		return;

		if (_state ==TS_IDLE||_state==TS_MOVEUP)
		{
			_sprite->setIndex(_SpriteIndex);
			_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		}
		// nếu là breaking
		else if (_state == TS_BREAKING)
		{
			// set index là mảnh gạch
			if (_isBright== false)						// nếu là màu tối
				_sprite->setIndex(12);
			else								// nếu là màu sáng
				_sprite->setIndex(13);
			// mảnh 1
			_sprite->Render(SmallPiece1->getPosition().x, SmallPiece1->getPosition().y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
			// mảnh 2
			_sprite->Render(SmallPiece2->getPosition().x, SmallPiece2->getPosition().y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
			// mảnh 3 đối xứng với mảnh 2 qua tâm
			_sprite->Render(2 * CenterX - SmallPiece1->getPosition().x, SmallPiece1->getPosition().y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
			// mảnh 4 đối xứng với mảnh 2 qua tâm
			_sprite->Render(2 * CenterX - SmallPiece2->getPosition().x, SmallPiece2->getPosition().y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
		}
		// nếu không phải breaking hoặc breaked thì vẽ
	
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
		break;
	case TS_BREAKED:
		_isNeedDelete = true;
	}
}