#include "BaseObject.h"
#include "Animation.h"
#include "Sprite.h"
class Cloud: public BaseObject
{
public:
	Cloud();
	Cloud(float _x, float _y, float width, float height,float vx, float vp, int ID, Sprite* sprite);
	void Render();
	~Cloud();
};

