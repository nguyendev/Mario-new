#include "Camera.h"
#include "BaseObject.h"
#include "sprite.h"
#include "Collision.h"
#define GROUND_Y 180
#define JUMP_VELOCITY_BOOST 0.4f
#define FALLDOWN_VELOCITY_DECREASE 0.5f
#define MARIO_SPEED 0.2f

class Mario: public BaseObject
{
public:
	DWORD last_time;
	
	Mario(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(int t);
	void Update(int t);
	void Render();
	void ProcessInput(KeyBoard* _keyboard);
	void CollisionTemp(BaseObject *);
	~Mario();
};

