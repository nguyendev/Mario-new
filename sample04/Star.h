#pragma once
#include "BaseObject.h"
#include "Camera.h"
#include "Collision.h"
#define X_VELOCITY 1.5
#define Y_VELOCITY 2.5
#define RISE_TIME  0.08
#define TIME_JUMPING 0.2	// thời gian 1 lần nảy của sao

class Star :public BaseObject
{
private:
	float timeRised;
	char  _state;
	int _currentSprite;
	float timeJumping;
public:

	DWORD last_time;
	Star();
	Star(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
	~Star();
};

