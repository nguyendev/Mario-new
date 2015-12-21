#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "StoneBrick.h"
#include "FloorBrick.h"
#include <list>

using namespace std;

class Brick :public BaseObject
{

private: 
	int _SpriteIndex;
	char	_state;
	bool	_isContainCoin;
	float	_xBreak1;		//Tham số của các mảnh vỡ. 1 là mảnh trên, 2 là mảnh dưới
	float	_yBreak1;
	float	_xBreak2;
	float	_yBreak2;
	float	_vyBreak1;
	float	_vyBreak2;
	float	_vxBreak1;
	float	_vxBreak2;
	float	_ayBreak;
	float	_angle;
public:
	bool	_isBright;
	bool	_isNeedDelete;
	bool	_isChanged;
	Brick();
	Brick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex, bool _isBright);
	~Brick();
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void CollisionTemp(BaseObject *){};
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
};