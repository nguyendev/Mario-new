#include "Flag.h"
#include "Global.h"


Flag::Flag() :BaseObject()
{
}
Flag::Flag(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	yFlag = y + _sprite->_Height;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	_widthRect = _width;
	_heightRect = _height * 10;
	_state = TS_IDLE;
}

void Flag::Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{
	if (_state == TS_ACTIVING)
	{
		yFlag += 100 * Time;							//Cập nhật tọa độ cờ.
		if (yFlag > _m_Position.y + _height * 9)
		{
			yFlag = _m_Position.y + _height * 9;
			ChangeState(TS_IDLE_2);
		}
	}
}

void Flag::ChangeState(char state)
{
	_state = state;
}

void Flag::Render()
{
 
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 2);
		_sprite->Render(_m_Position.x - _width/2, yFlag, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		_sprite->setIndex(_SpriteIndex + 3);
		for (int i = 1; i < 10; i++){
			_sprite->Render(_m_Position.x, _m_Position.y + i*_height, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
		}
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y + 10*_height, Camera::_cameraX, Camera::_cameraY, FLAG_DEEP);
}
void Flag::SetState(char* varName, int val)
{
	if (strcmp(varName, "_state") == 0)
		ChangeState(val);
}
int Flag::GetState(char* varName)
{
	if (strcmp(varName, "_state") == 0)
		return _state;
	return -1;
}