#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "BaseObject.h"
#include <list>
using namespace std;

class Ground :public BaseObject
{
public:
	Ground();
	Ground(float _x, float _y, float width, float height, int _ID, Sprite* _sprite);
	void Render();
};