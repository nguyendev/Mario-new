#include "background.h"
#define DEEP_PIPE 0.3

BackGround::BackGround() :BaseObject(){}
BackGround::BackGround(float x, float y, float _width, float _height, int ID, Sprite* sprite) : BaseObject(x, y, _width, _height)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(1, 1, 0, _sprite);
}

void BackGround::Render()
{
	switch (_ID)
	{
	case 2000:
		_sprite->Draw(_x, _y, 1, 1, _ani->GetRect(0), DEEP_PIPE);				//Đỉnh ống		//Chân ống
		break;
	}
}

