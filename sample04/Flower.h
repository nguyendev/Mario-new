#pragma once
#include "BaseObject.h"
#include "Camera.h"
#include "Collision.h"
#define Y_VELOCITY -1.5

class Flower :public BaseObject
{
private:
	float timeRised;
public:

	bool Activated;		// true if the flower activated
	DWORD last_time;
	Flower();
	Flower(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);		// need to fix.
	void Render();
	~Flower();
};

