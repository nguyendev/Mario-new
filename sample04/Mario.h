#include "Camera.h"
#include "BaseObject.h"
#include "Collision.h"
#include "Audio.h"
#define GROUND_Y 180
#define JUMP_VELOCITY_BOOST 400.0f
#define FALLDOWN_VELOCITY_DECREASE 200.0f
#define MARIO_SPEED 1000.0f


class BaseObject;
class Mario: public BaseObject
{
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
	CSound *_sound_1up, *_sound_Beep, *_sound_BigJump, *_sound_BowserDie, *_sound_Break, *_sound_Bump, *_sound_Coin, *_sound_Background;
	CSound *_sound_Die, *_sound_EnemyFire, *_sound_FireBall, *_sound_Flagpole, *_sound_GameOver, *_sound_Item, *_sound_Warp;
	CSound	*_sound_Jump, *_sound_Kick, *_sound_Pause, *_sound_Powerup, *_sound_Skid, *_sound_Squish, *_sound_Thwomp, *_sound_Vine;
public:
	DWORD last_time;
	Mario(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite, HWND hwnd);
	void Move(float t);
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void ProcessInput(KeyBoard* _keyboard);
	void CheckCollision(list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void LoadAudio();
	~Mario();
};

