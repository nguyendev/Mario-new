#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "FloorBrick.h"
#include "IronBrick.h"
#include "StoneBrick.h"
#include <list>

using namespace std;

class Brick :public BaseObject
{

private: 
	int _SpriteIndex;
public:

	Brick();
	Brick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex);
	~Brick();
	void Update();
	void Render();
	void CollisionTemp(BaseObject *){};
};