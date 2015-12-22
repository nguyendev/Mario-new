#ifndef _MARIO_H_
#define _MARIO_H_
#include "Camera.h"
#include "BaseObject.h"
#include "Collision.h"
#include "Audio.h"
#include "sprite.h"
#define GROUND_Y 180
#define JUMP_VELOCITY_BOOST 400.0f
#define FALLDOWN_VELOCITY_DECREASE 200.0f
#define MARIO_SPEED 1000.0f

class Sprite;
class Mario: public BaseObject
{
	
	Sprite* sBig;
	float _PositionX_Old;
	float vMax;
	bool isOnTheGround;
	float _timejump;
	bool isCanJump;
	bool isJumping;
	float waittime;
	D3DXVECTOR2		m_MaxVelocity;
	D3DXVECTOR2		m_MinVelocity;
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 minVelocity;
	LPD3DXFONT	_font;
public:
	Camera* _camera;
	DWORD last_time;
	Mario();
	Mario(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, CGameMario* game);
	void Move(float t);
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void ProcessInput(KeyBoard* _keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);

	void	ResetRect(){};
	~Mario();
};

#endif _MARIO_H_