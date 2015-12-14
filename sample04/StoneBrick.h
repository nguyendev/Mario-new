#pragma once

#include "Brick.h"
using namespace std;

class StoneBrick :public BaseObject
{

private:
	int _SpriteIndex;
public:

	StoneBrick();
	StoneBrick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite,int SpriteIndex);
	~StoneBrick();
	void Update();
	void Render();
	void CollisionTemp(BaseObject *){};
};