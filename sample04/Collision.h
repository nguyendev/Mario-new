#pragma once
#include "SweptAABB.h"
#include "BaseObject.h"
#include "Global.h"

class Collision
{
	D3DXVECTOR2 velocity;

public:
	Collision();
	DIR isCollision(BaseObject*, BaseObject*);
	D3DXVECTOR2		getVelocity(){ return velocity; };
	~Collision();
	float timeCol;
	void		setTimeCol(float);
	float		getTimeCol(){ return timeCol; }
};

