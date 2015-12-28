#pragma once
#include "BaseObject.h"
#include "Camera.h"
class Coin :public BaseObject		// must render in RenderFrame() of class GameMario 
{
private:
	float timeFly;
public:
	DWORD last_time;
	Coin();
	Coin(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Activate();
	void Render();

	~Coin();
};

