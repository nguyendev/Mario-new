#ifndef _MARIO_H_
#define _MARIO_H_
#include "Camera.h"
#include "BaseObject.h"
#include "Collision.h"
#include "Audio.h"
#include "sprite.h"
#include "Bullet.h"
#include "MushRoom.h"
#include "GreenMushroom.h"
#include "BrickMushroom.h"
#include "BrickQuestion.h"


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
	bool isShotable;
	float waitbullet;
	bool isShotting;
	float waitShotting;
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
	bool isProtected;
	bool isProtectedHidden;
	float waitProtect;
	float waitProtectHidden;
	float waitRender;
	bool isRender;
	float yTemp;
	float waitInFlag;
	D3DXVECTOR2		_m_PostionOld;
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
	void UpdateSprite(float time);
	void Render();
	void ProcessInput(KeyBoard* _keyboard, float Time);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void CollisionEnemy();

	void TurnLeft(float Time, float Max);
	void TurnRight(float Time, float Max);
	float Jump(float Time);
	void Stand(float Time);
	void sExplosion(float Time);
	void EatCoin(float _x, float _y);
	~Mario();



	void ChangeState(char state);
};

#endif _MARIO_H_