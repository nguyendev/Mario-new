#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include <list>
#define	GOING_SPEED 0.5
#define DISTANCE_OF_TWO_BAR 200

using namespace std;

class Bridge :public BaseObject
{

private:
	int		_SpriteIndex;
	char	_state;
	float Distance_Of_Two_bar;
public:
	bool	_isNeedDelete;
	bool	_isChanged;
	Bridge();
	Bridge(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	~Bridge();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void CollisionTemp(BaseObject *){};
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
};