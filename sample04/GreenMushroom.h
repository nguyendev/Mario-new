#pragma once
#include "BaseObject.h"
#include "Camera.h"
#include "Collision.h"
#define X_VELOCITY 2
#define Y_VELOCITY 1.5

class GreenMushRoom :public BaseObject
{
private:
	float timeRised;
public:
	bool Activated;
	DWORD last_time;
	GreenMushRoom();
	GreenMushRoom(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move();
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);		// need to fix.
	void Render();
	~GreenMushRoom();
};

