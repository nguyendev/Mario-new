#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "MushRoom.h"
#include <list>
#define TIME_FLICKER 0.3		// thời gian nhấp nháy

using namespace std;

class BrickMushroom :public BaseObject
{
private:
	char	_state;
	float	_timeToFlicker;
	// xử lý sprite của từng viên gạch
	int		_currentSprite;
	// biến xử lý độ nảy viên gạch
	float	_moveupTime;	// thời gian đi lên của viên gạch
	bool	isFalling;
	// lưu vị trí cố định của gạch
	const float Recent_X = _m_Position.x;
	const float Recent_Y = _m_Position.y;
public:
	// biến xem có phải là hoa ko
	
	bool	_isBright;
	bool	_isNeedDelete;
	bool	_isChanged;
	BrickMushroom();
	BrickMushroom(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	~BrickMushroom();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void CollisionTemp(BaseObject *){};
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
};
