#include "BaseObject.h"
#include "Animation.h"
#include "Sprite.h"
class Cloud: public BaseObject
{
public:
	Cloud();
	Cloud(float _x, float _y, float width, float height, int ID, Sprite* sprite);
	void Render();
	~Cloud();
};

