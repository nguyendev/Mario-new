#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include <list>

using namespace std;

class Grass :public BaseObject
{

private:
	int _SpriteIndex;
public:

	Grass();
	Grass(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex);
	~Grass();
	void Update();
	void Render();
	void CollisionTemp(BaseObject *){};
};

