#pragma once
#include "BaseObject.h"
#include "Camera.h"
class Goomba:public BaseObject
{
private:
	char	state;
	float	waitIdle;
	float	vx;
	float	vy;
	float	ay;
public:
	DWORD last_time;
	Goomba();
	Goomba(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(float t);
	void Collision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void CollisionTemp(BaseObject *obj);
	~Goomba(){};
};

