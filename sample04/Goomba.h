#pragma once
#include "BaseObject.h"
#include "Camera.h"
#define X_VELOCITY 0.5
#define Y_VELOCITY 2
#define TIME_FLICKER 0.3		// thời gian nhấp nháy
#define WAITING_TIME_TO_DIE 0.5

class BaseObject;
class Goomba :public BaseObject
{
private:
	char	_state;
	float	waitIdle;
	int		_currentSprite;
	float _waitingTimeToDie;
	float _timeToFlicker;
public:

	DWORD last_time;
	Goomba();
	Goomba(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move();
	void Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);		// need to fix.
	void Render();
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
	~Goomba();

};

