#include "Camera.h"
#include "BaseObject.h"
#include "Collision.h"
#define GROUND_Y 180
#define JUMP_VELOCITY_BOOST 400.0f
#define FALLDOWN_VELOCITY_DECREASE 200.0f
#define MARIO_SPEED 1000.0f


class BaseObject;
class Mario: public BaseObject
{
	float	yTemp;
	float	ax;
	float	ay;
	float	vyOld;
	float vMax;
	bool isOnTheGround;
	float _timejump;
	bool isCanJump;
	bool isJumping;
public:
	DWORD last_time;
	Mario(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(float t);
	void Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj);
	void Render();
	void ProcessInput(KeyBoard* _keyboard);
	void CollisionStatic(float t, list<BaseObject*>* staticObj);
	~Mario();
};

