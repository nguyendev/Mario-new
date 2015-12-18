#pragma once
#include "SweptAABB.h"
#include "BaseObject.h"
#include "Global.h"

class Collision
{
private:
	D3DXVECTOR2 velocity;
	static Collision* m_instance;
	Collision(){};
public:
	static Collision* getInstance();
	DIR isCollision(BaseObject*, BaseObject*);
	D3DXVECTOR2		getVelocity(){ return velocity; };
	~Collision(){};
	float timeCol;
	void		setTimeCol(float);
	float		getTimeCol(){ return timeCol; }
};

