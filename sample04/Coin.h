#pragma once
#include "BaseObject.h"
#include "Camera.h"
#define MAX_TIME_FLY 0.9
class Coin :public BaseObject		// must render in RenderFrame() of class GameMario 
{
private:
	float timeFly;					// thời gian bay
	float _timeOfEachSprite;
	char _state;
	int _currentSprite;
	int _NumberOfCoins;
	const float RecentX = _m_Position.x;		// lấy vị trí mặc định của đồng xu
	const float RecentY = _m_Position.y;
public:
	DWORD last_time;
	Coin();
	Coin(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int NumberOfCoins);
	void Update(float TPF, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
	~Coin();
};

