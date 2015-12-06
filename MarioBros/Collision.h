#pragma once
#include <d3dx9.h>
#include "Global.h"
#include "BaseObject.h"

class Collision
{
public:
	float SweptAABB(BaseObject* b1, BaseObject* b2, float& normalx, float &normaly);
	BaseObject* GetSweptBroadphaseBox(BaseObject *);
	bool AABBCheck(BaseObject* b1, BaseObject * b2);
	Collision(){};
	~Collision(){};
	
};

