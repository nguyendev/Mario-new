#include "Brick.h"


Brick::Brick() :BaseObject()
{
}
Brick::Brick(float _x, float _y, int ID, CSprite* sprite) : BaseObject(_x, _y)
{
	_sprite = sprite;
	_ID = ID;
}

void Brick::Render()
{
	switch (_ID)
	{
	case(17) :
		_sprite->Render(_x, _y, _vx, _vy);
		break;
	case(18) :
		//_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(0), 0.5);
		break;
	case(19) :
		//_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(8), 0.5);
		break;

	}

}
