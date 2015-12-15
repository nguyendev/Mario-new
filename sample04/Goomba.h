#pragma once
#include "BaseObject.h"
#include "Camera.h"
class Goomba:public BaseObject
{
public:
	DWORD last_time;
	Goomba();
	Goomba(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(float t);
	void Update(float t);
	void Render();
	void CollisionTemp(BaseObject *obj);
	~Goomba();
};

