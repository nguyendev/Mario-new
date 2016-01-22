#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "Coin.h"
#include <list>
#define TIME_FLICKER 0.3		// thời gian nhấp nháy
#define MAX_MOVEUP_TIME 0.15		// thời gian đi lên của viên gạch
#define SPEED_OF_BRICK_PIECE_X 0.5	// vận tốc mảnh gạch
#define SPEED_OF_BRICK_PIECE_Y 2.0	
#define Y_VELOCITY_UP 1				// vận tốc đi lên của viên gạch
using namespace std;

class BrickQuestion :public BaseObject
{
private:
	char	_state;
	bool	_isContainCoin;
	float	_timeToFlicker;
	// xử lý sprite của từng viên gạch
	int		_currentSprite;
	// biến xử lý độ nảy viên gạch
	float	_moveupTime;	// thời gian đi lên của viên gạch
	bool	isFalling;
	// lưu vị trí cố định của gạch
	const float Recent_X = _m_Position.x;
	const float Recent_Y = _m_Position.y;
	// tiền xu
	BaseObject* coin;
	int _NumberOfCoins;
public:
	bool	_isBright;
	bool	_isNeedDelete;
	bool	_isChanged;
	BrickQuestion();
	BrickQuestion(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, CSprite* CoinSprite, int NumberOfCoins);
	~BrickQuestion();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void CollisionTemp(BaseObject *){};
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
};
