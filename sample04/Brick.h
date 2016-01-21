#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "StoneBrick.h"
#include "FloorBrick.h"
#include <list>
#define MAX_MOVEUP_TIME 0.15
#define SPEED_OF_BRICK_PIECE_X 0.5
#define SPEED_OF_BRICK_PIECE_Y 2.0
#define Y_VELOCITY_UP 1

using namespace std;

class Brick :public BaseObject
{

private: 
	int _SpriteIndex;
	char	_state;
	bool	_isContainCoin;
	// biến xử lý độ nảy viên gạch
	float	_moveupTime;	// thời gian đi lên của viên gạch
	bool	isFalling;
	// lưu vị trí cố định của gạch
	const float Recent_X = _m_Position.x;	
	const float Recent_Y = _m_Position.y;
	//4 viên gạch nhỏ
	BaseObject* SmallPiece1;
	BaseObject* SmallPiece2;
	// tâm viên gạch theo Ox
	float CenterX;
public:
	bool	_isBright;
	bool	_isNeedDelete;
	bool	_isChanged;
	Brick();
	Brick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, int SpriteIndex, bool _isBright);
	~Brick();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void CollisionTemp(BaseObject *){};
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
};