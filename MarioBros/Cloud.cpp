#include "Cloud.h"

#include "Global.h"


Cloud::Cloud() :BaseObject()
{
}


Cloud::Cloud(float _x, float _y, float width, float height, int ID, Sprite* sprite) : BaseObject(_x, _y, width, height)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(4, 1, 0.5, _sprite);
}

void Cloud::Render()
{
	switch (_ID)
	{
	case(25):
		_sprite->Draw(_x, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(0), 1);
		_sprite->Draw(_x + _width / 4, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(1), 1);
		_sprite->Draw(_x + _width / 4 * 2, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(2), 1);
		_sprite->Draw(_x + _width / 4 * 3, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(3), 1);
		break;
	case(26):
		_sprite->Draw(_x, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(0), 0.5);
		_sprite->Draw(_x + TILE_SIZE, _y, 0, 600,ZOOM, ZOOM, _ani->GetRect(1), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 2, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(2), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 3, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 4, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(2), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 5, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(3), 0.5);
		break;
	case(27):
		_sprite->Draw(_x, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(0), 0.5);
		_sprite->Draw(_x + TILE_SIZE, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 2, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(2), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 3, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 4, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(2), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 5, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 6, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(2), 0.5);
		_sprite->Draw(_x + TILE_SIZE * 7, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(3), 0.5);
		break;
	}
}