#pragma once

#include "Brick.h"
using namespace std;

class IronBrick :public BaseObject
{
private:
	int _SpriteIndex;

public:

	IronBrick();
	IronBrick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex);
	~IronBrick();
	void Update();
	void Render();
	void CollisionTemp(BaseObject *){};
};