#pragma warning(disable: 4244) // possible loss of data
#pragma warning(disable: 4305) // argument
#include "Pipe.h"
#include "Global.h"


Pipe::Pipe() :BaseObject()
{
}


Pipe::Pipe(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	switch (ID)
	{
	case 14:
		_widthRect  = _width*2;
		_heightRect = _height*2;
		break;
	case 15:
		_widthRect = _width * 2;
		_heightRect = _height * 3;
	case 16:
		_widthRect = _width * 2;
		_heightRect = _height * 4;
	}
	_SpriteIndex = SpriteIndex;
}


void Pipe::Render()
{
	switch (_ID)
	{
	case 14:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);		//Đầu ống
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												//Chân ống
		_sprite->Render(_m_Position.x, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_m_Position.x + _width, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		break;
	case 15:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);		//Đầu ống
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												//Chân ống
		_sprite->Render(_m_Position.x, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_m_Position.x + _width, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												
		_sprite->Render(_m_Position.x, _m_Position.y + _height*2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_m_Position.x + _width, _m_Position.y + _height*2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		break;
	case 16:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);		//Đầu ống
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_m_Position.x + _width, _m_Position.y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												//Chân ống
		_sprite->Render(_m_Position.x, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_m_Position.x + _width, _m_Position.y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);
		_sprite->Render(_m_Position.x, _m_Position.y + _height * 2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_m_Position.x + _width, _m_Position.y + _height * 2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);
		_sprite->Render(_m_Position.x, _m_Position.y + _height * 3, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_m_Position.x + _width, _m_Position.y + _height * 3, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		break;
	}
}