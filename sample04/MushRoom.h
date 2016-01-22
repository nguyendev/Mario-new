#pragma once
#include "BaseObject.h"
#include "Camera.h"
#include "Collision.h"
#define X_VELOCITY 0.5
#define Y_VELOCITY 3
#define RISE_TIME  0.1

class MushRoom :public BaseObject
{
private:
	float	timeRised;
	int		_currentSprite;
	char	_state;
public:
	
	DWORD last_time;
	MushRoom();
	MushRoom(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
	~MushRoom();
};

