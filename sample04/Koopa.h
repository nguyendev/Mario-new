#pragma once
#include "BaseObject.h"
#include "Camera.h"
class Koopa :public BaseObject
{
public:
	DWORD last_time;
	Koopa();
	Koopa(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(float t);
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void CollisionTemp(BaseObject *obj);
	~Koopa();
};