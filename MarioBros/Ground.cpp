#include "Ground.h"
#include "BaseObject.h"
#include "Global.h"
#include "Animation.h"
#include "Sprite.h"

Ground::Ground() :BaseObject(){}
Ground::Ground(float _x, float _y, float width, float height,float vx, float vy, int ID, Sprite* sprite) : BaseObject(_x, _y, width, height, vx, vy)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(4, 4, 0.5, _sprite);
}

void Ground::Render()
{
	_sprite->Draw(_x, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
		_sprite->Draw(_x, _y + 40, 0, 600, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
}