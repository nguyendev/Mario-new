#pragma once
#include "SwapAABB.h"
#include "BaseObject.h"

class BaseObject;

class Collision
{
	float veclocity_vx;
	float veclocity_vy;

	static Collision* m_instance;
	float timeCollision;
	Collision();
public:
	static Collision* getInstance();
	DIR isCollision(BaseObject*, BaseObject*);
	D3DXVECTOR2	getVelocity();
	float getTimeCollision(){ return timeCollision; }
};
