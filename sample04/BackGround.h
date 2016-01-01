#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "FloorBrick.h"
#include "IronBrick.h"
#include "StoneBrick.h";
#include <list>

using namespace std;

class BackGround :public BaseObject
{

private:
	int _SpriteIndex;
public:

	BackGround();
	BackGround(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	~BackGround();
	void Update();
	void Render();
	void CollisionTemp(BaseObject *){};
};