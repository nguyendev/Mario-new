#include "BaseObject.h"
#include "Animation.h"
#include "Sprite.h"
class Mountain:public BaseObject
{
public:
	Mountain();
	Mountain(float _x, float _y, float width, float height, float _vx, float _vy, int ID, Sprite* sprite);
	void Render();
	~Mountain();
};

