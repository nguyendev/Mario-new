#include "Camera.h"
#include "BaseObject.h"
#include "Collision.h"
#define GROUND_Y 180
#define JUMP_VELOCITY_BOOST 400.0f
#define FALLDOWN_VELOCITY_DECREASE 200.0f
#define MARIO_SPEED 1000.0f

class Mario: public BaseObject
{
	float	yTemp;
	float	ax;
	float	ay;
	float	vyOld;
	float vMax;
public:
	DWORD last_time;
	Mario(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(float t);
	void Update(float t,list<BaseObject*>* staticObj);
	void Render();
	void ProcessInput(KeyBoard* _keyboard);
	void CollisionTemp(BaseObject *obj, float t);
	void GetCollisionWith(BaseObject *obj,float normalx,float normaly);
	~Mario();
};

