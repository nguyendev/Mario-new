#pragma once
#include "BaseObject.h"
#include "Sprite.h"
class Cloud:public BaseObject
{
public:
	Cloud();
	~Cloud();
	Cloud(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Render();
};

