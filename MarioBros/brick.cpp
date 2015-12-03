#include "brick.h"



#define DEEP_PIPE 0.3

Pipe::Pipe() :BaseObject(){}
Pipe::Pipe(float x, float y, float _width, float _height, int ID, Sprite* sprite) : BaseObject(x, y, _width, _height)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(4, 5, 0, _sprite);
}

void Pipe::Render()
{
	switch (_ID)
	{
	case 1010:
		_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(0), DEEP_PIPE);				//Đỉnh ống
		_sprite->Draw(_x, _y + TILE_SIZE, ZOOM, ZOOM, _ani->GetRect(2), DEEP_PIPE);				//Chân ống
		break;
	case 1020:
		_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(0), DEEP_PIPE);				//Đỉnh ống
		_sprite->Draw(_x, _y + TILE_SIZE, ZOOM, ZOOM, _ani->GetRect(2), DEEP_PIPE);				//Chân ống
		_sprite->Draw(_x, _y + TILE_SIZE * 2, ZOOM, ZOOM, _ani->GetRect(2), DEEP_PIPE);
		break;
	case 1030:
		_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(0), DEEP_PIPE);				//Đỉnh ống
		_sprite->Draw(_x, _y + TILE_SIZE, ZOOM, ZOOM, _ani->GetRect(2), DEEP_PIPE);				//Chân ống
		_sprite->Draw(_x, _y + TILE_SIZE * 2, ZOOM, ZOOM, _ani->GetRect(2), DEEP_PIPE);
		_sprite->Draw(_x, _y + TILE_SIZE * 3, ZOOM, ZOOM, _ani->GetRect(2), DEEP_PIPE);
		break;
	case 1031:
		_sprite->Draw(_x, _y, ZOOM, ZOOM, D3DXVECTOR2(40, 40), -PI / 2, D3DCOLOR_XRGB(255, 255, 255), _ani->GetRect(0), DEEP_PIPE);
		_sprite->Draw(_x + TILE_SIZE, _y, ZOOM, ZOOM, D3DXVECTOR2(40, 40), -PI / 2, D3DCOLOR_XRGB(255, 255, 255), _ani->GetRect(2), DEEP_PIPE);
		break;
	case 1032:
		_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(1), DEEP_PIPE);
		_sprite->Draw(_x, _y + TILE_SIZE, ZOOM, ZOOM, _ani->GetRect(3), DEEP_PIPE);
		break;
	}
}

void Pipe::ResetWhenReload(Sprite* _sprite)
{
	_sprite = _sprite;
	_ani = new Animation(2, 2, 0, _sprite);
}