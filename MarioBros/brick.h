#ifndef _BRICK_H_
#define _BRICK_H_
#include "BaseObject.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>
#include "Global.h"
#include "Camera.h"
class Brick :public BaseObject
{
public:
	Brick();
	Brick(float x, float y, float _width, float _height, int ID, Sprite* sprite);
	virtual void Render();
	void ResetWhenReload(Sprite* sprite);
};

#endif _BRICK_H_