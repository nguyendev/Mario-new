#pragma once
#include "BaseObject.h"
#include "Camera.h"
#include "Collision.h"
#define MAX_TIME_FLY 0.6
#define TIME_FLICKER 0.3		// thời gian nhấp nháy
class Coin :public BaseObject		// must render in RenderFrame() of class GameMario 
{
private:
	float timeFly;					// thời gian bay
	float _timeToFlick;				// thời gian nháy
	char	_state;
	int		_currentSprite;
	const float RecentX = _m_Position.x;		// lấy vị trí mặc định của đồng xu
	const float RecentY = _m_Position.y;
public:
	int _NumberOfCoins;
	DWORD last_time;
	Coin();
	Coin(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int NumberOfCoins);
	void Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);		// need to fix.
	void Render();
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
	~Coin();
};

