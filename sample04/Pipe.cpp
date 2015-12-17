#include "Pipe.h"
#include "Global.h"


Pipe::Pipe() :BaseObject()
{
}


Pipe::Pipe(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_vx = 5;
	_vy = 5;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	ResetRect();
}

void Pipe::Update()
{
	_x += 10;
}

void Pipe::Render()
{
	switch (_ID)
	{
	case 14:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);		//Đầu ống
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_x + _width, _y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												//Chân ống
		_sprite->Render(_x, _y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_x + _width, _y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		break;
	case 15:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);		//Đầu ống
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_x + _width, _y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												//Chân ống
		_sprite->Render(_x, _y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_x + _width, _y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												
		_sprite->Render(_x, _y + _height*2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_x + _width, _y + _height*2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		break;
	case 16:
		_sprite->setIndex(_SpriteIndex);
		_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);		//Đầu ống
		_sprite->setIndex(_SpriteIndex + 1);
		_sprite->Render(_x + _width, _y, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);												//Chân ống
		_sprite->Render(_x, _y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_x + _width, _y + _height, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);
		_sprite->Render(_x, _y + _height * 2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_x + _width, _y + _height * 2, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 4);
		_sprite->Render(_x, _y + _height * 3, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		_sprite->setIndex(_SpriteIndex + 5);
		_sprite->Render(_x + _width, _y + _height * 3, Camera::_cameraX, Camera::_cameraY, PIPE_DEEP);
		break;
	}
}