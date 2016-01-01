﻿#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "BaseObject.h"
#include <list>

using namespace std;

class MuchMoneyBrick :public BaseObject
{
private:
	char	_state;
	bool	_isContainCoin;
	// biến xử lý độ nảy viên gạch
	float	_moveupTime;	// thời gian đi lên của viên gạch
	bool	isFalling;

	// lưu vị trí cố định của gạch
	const float Recent_X = _m_Position.x;
	const float Recent_Y = _m_Position.y;

	// số lượng tiền trong 1 viên gạch
	int NumberOfCoins;					
public:
	bool	_isBright;
	bool	_isNeedDelete;
	bool	_isChanged;
	MuchMoneyBrick();
	MuchMoneyBrick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int _SpriteIndex);
	~MuchMoneyBrick();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void CollisionTemp(BaseObject *){};
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
};
