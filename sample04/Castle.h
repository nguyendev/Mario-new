#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include <list>

using namespace std;

class Castle :public BaseObject
{

private:
	int _SpriteIndex;
public:

	Castle();
	Castle(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex);
	~Castle();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void CollisionTemp(BaseObject *){};
};
