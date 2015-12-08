#include "Camera.h"
#include "BaseObject.h"
#include "sprite.h"
class Mario: public BaseObject
{
public:
	DWORD last_time;
	
	Mario(float _x, float _y, float _cameraX, float _cameraY, int _ID, CSprite* _sprite);
	void Move(int t);
	void Update(int t);
	void Render();
	~Mario();
};

