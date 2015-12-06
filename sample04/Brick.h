#pragma once

#include "Sprite.h"
#include "BaseObject.h"
#include <list>
using namespace std;

class Brick :public BaseObject
{


public:

	Brick();
	Brick(float _x, float _y, int _ID, CSprite* _sprite);
	~Brick();
	void Render();
};