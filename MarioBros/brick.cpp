#include "Brick.h"
#include "Global.h"

Brick::Brick() :BaseObject(){}
Brick::Brick(float _x, float _y, float width, float height, bool _isBright, int ID, Sprite* sprite) : BaseObject(_x, _y, width, height)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(4, 4, 0.5, _sprite);
}

void Brick::Render()
{
		_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(0), 0.5);
}
