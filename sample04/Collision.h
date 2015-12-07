#include "BaseObject.h"
#include "Global.h"
class Collision
{
public:
	float SweptAABB(BaseObject* b1, BaseObject* b2, float& normalx, float &normaly);
	BaseObject* GetSweptBroadphaseBox(BaseObject *);
	bool AABBCheck(BaseObject* b1, BaseObject * b2);
	Collision(){};
	~Collision(){};

};

