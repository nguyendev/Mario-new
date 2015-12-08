#pragma once

#include "Sprite.h"
#include "Camera.h"
#include <list>
using namespace std;

class Brick :public BaseObject
{


public:

	Brick();
	Brick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	~Brick();
	void Update();
	void Render();
};