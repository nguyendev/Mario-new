#pragma once
#include "Animation.h"
#include "Sprite.h"
#include "BaseObject.h"
#include <list>

class Grass : public BaseObject
{
public:
	Grass();
	Grass(float _x, float _y, float width, float height,float vx, float vy, int _ID, Sprite* _sprite);
	void Render();
};
