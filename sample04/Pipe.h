#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include <list>
using namespace std;

class Pipe :public BaseObject
{
private:
	int _SpriteIndex;
public:
	Pipe();
	Pipe(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex);
	~Pipe();
	void Render();
	void CollisionTemp(BaseObject *){};
};

