#pragma once

#include "Brick.h"
using namespace std;

class FloorBrick :public BaseObject
{
private:
	int _SpriteIndex;
public:
	FloorBrick();
	FloorBrick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite,int SpriteIndex);
	~FloorBrick();
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void CollisionTemp(BaseObject *){};
};