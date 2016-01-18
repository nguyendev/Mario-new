#pragma once
#include "BaseObject.h"
#include "Camera.h"
#define X_VELOCITY 0.5
#define Y_VELOCITY 2
#define WAITING_TIME_TO_LIVE 4

class BaseObject;
class Koopa :public BaseObject
{
private:
	char	_state;
	float	waitIdle;
	float	_waitingTimeToLiveAgain;
	float	_waitingTimeToChangeState;
	int		_currentSprite;
public:

	DWORD last_time;
	Koopa();
	Koopa(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move();
	void Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);		// need to fix.
	void CheckCollisionMove(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
	~Koopa();

};

