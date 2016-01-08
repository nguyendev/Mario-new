#pragma once
#include "BaseObject.h"
#include "Sprite.h"
#include <list>

using namespace std;
class Mario;
class Bullet : public BaseObject
{
private:
	float vx;
	float vy;
	float ay;
	float timedelay;
	float waitIncreaseVecY;
	float timeblow;
	RECT oldRect;
	bool _isNeedDelete;
	list<BaseObject*>* collisionList;
	CSprite* _sprite1;//explosion
	Mario* mario;
public:
	char _state;
	Bullet(void);
	~Bullet(void);
	Bullet(float x, float y, float cameraX, float cameraY, float vx, CSprite* sprite, CSprite* sprite1);
	void Update(float TPF, list<BaseObject*>* staObjs, list<BaseObject*>* dynObjs, KeyBoard* input);
	void Render();
	void Move(float TPF, list<BaseObject*>* staObjs, list<BaseObject*>* dynObjs);
	void ChangeState(char _state);
	void SetState(char* varName, int val);
	int GetState(char* varName);
};
