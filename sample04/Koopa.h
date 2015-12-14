#pragma once
#include "BaseObject.h"
#include "Camera.h"
class Koopa :public BaseObject
{
public:
	DWORD last_time;
	Koopa();
	Koopa(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(int t);
	void Update(int t);
	void Render();
	void CollisionTemp(BaseObject *obj);
	~Koopa();
};