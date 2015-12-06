#include "Brick.h"
#include "Global.h"

Brick::Brick() :BaseObject(){}
Brick::Brick(float _x, float _y, float width, float height,float _vx, float _vy, bool _isBright, int ID, Sprite* sprite) : BaseObject(_x, _y, width, height, _vx, _vy)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(4, 4, 0.5, _sprite);
}

void Brick::Render()
{
	//switch (_ID)
	//{
	//case(17) :
		_sprite->Draw(_x, _y, _vx, _vy, ZOOM, ZOOM, _ani->GetRect(2), 0.5);
	/*	break;
	case(18) :
		_sprite->Draw(_x, _y, _vx, _vy, ZOOM, ZOOM, _ani->GetRect(0), 0.5);
		break;
	case(19) :
		_sprite->Draw(_x, _y, _vx, _vy, ZOOM, ZOOM, _ani->GetRect(8), 0.5);
		break;

	}*/

}
