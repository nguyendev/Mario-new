#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Camera.h"
#include "Star.h"
#include "GreenMushroom.h"
#include <list>
#define TIME_FLICKER 0.3		// thời gian nhấp nháy
//CHỨA ITEM ĐẶC BIỆT LÀ SAO VÀ NẤM XANH.
// XÉT THEO ID: NẾU ID BẰNG 50 thì là nấm xanh, 52 là sao.
using namespace std;

class SpecialBrick :public BaseObject
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
	// tiền xu
	BaseObject* Item;						// là item đặc biệt như sao, nấm xanh.
	bool	isContainItem;					// còn đang chứa đồ
public:
	bool	_isBright;
	bool	_isNeedDelete;
	bool	_isChanged;
	SpecialBrick();
	SpecialBrick(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, CSprite* ItemSprite);
	~SpecialBrick();
	void Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void CollisionTemp(BaseObject *){};
	void SetState(char* Name, int val);
	int GetState(char* Name);
	void ChangeState(char state);
};
