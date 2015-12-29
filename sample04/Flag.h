#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include <list>

using namespace std;

class Flag :public BaseObject
{

private:
	int _SpriteIndex;
public:

	Flag();
	Flag(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex);
	~Flag();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard){};
	void Render();
	void CollisionTemp(BaseObject *){};
};