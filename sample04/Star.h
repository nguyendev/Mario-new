#pragma once
#include "BaseObject.h"
#include "Camera.h"
#include "Collision.h"
#define X_VELOCITY 2
#define Y_VELOCITY 1.5

class Star :public BaseObject
{
private:
	float timeJump;
	char  _state;
public:
	DWORD last_time;
	Star();
	Star(float _x, float _y,float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move();
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);		// need to fix.
	void Render();
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
	~Star();
};

