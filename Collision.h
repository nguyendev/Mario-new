#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "BaseObject.h"
#include "Global.h"

float SweptAABB(BaseObject* b1, BaseObject* b2, float& normalx, float &normaly);
BaseObject* GetSweptBroadphaseBox(BaseObject *);
bool AABBCheck(BaseObject* b1, BaseObject * b2);
DIR AABB(BaseObject* box1, BaseObject* box2);


#endif _COLLISION_H_

