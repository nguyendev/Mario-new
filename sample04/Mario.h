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

class CSprite;
class Mario: public BaseObject
{
private:
	CSprite* _sBig_left;
	CSprite* _sBig_right;
	CSprite* _sSmall_right;
	CSprite* _sBullet;
	CSprite* _sExplosion;
	CSprite* _current;
	float _PositionX_Old;
	float vMax;
	bool isOnTheGround;
	float timeJumped;
	bool isJumping;
	bool isCanJump;
	float waittime;
	float waitDieing;
	float waitRenderFirst;          // Ve khi Mario vua di chuyen
	bool	isChangeDirectionL;		//Đổi hướng 
	bool	isChangeDirectionR;
	bool	isBig;
	float waitChangeDir;
	float waitIncreaseVecY;			//doi de tang toc do trong luc
	float ax;
	float ay;
	char _state;
	D3DXVECTOR2		m_MaxVelocity;
	D3DXVECTOR2		m_MinVelocity;
	D3DXVECTOR2		maxVelocity;
	D3DXVECTOR2		minVelocity;
	LPD3DXFONT	_font;
public:
	
	bool _isVisiableKeyboard;
	Camera* _camera;
	DWORD last_time;
	bool died;
	
	Mario();
	Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sBig_right, CSprite* sBig_left, CSprite* small_right, CSprite* small_left, CSprite* bullet, CSprite* sExplosion, CGameMario* game);
	void Move(float t);
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard);
	void Render();
	void ProcessInput(KeyBoard* _keyboard, float Time);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);

	void TurnLeft(float Time);
	void TurnRight(float Time);
	void Jump(float Time);
	void Stand(float Time);

	~Mario();



	void ChangeState(char state);
};

#endif _MARIO_H_