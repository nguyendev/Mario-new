#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "BaseObject.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>
#include "Global.h"
#include "Camera.h"

class BackGround :public BaseObject
{
public:
	BackGround();
	BackGround(float x, float y, float _width, float _height, int ID, Sprite* sprite);
	void Render();

};

#endif _BACKGROUND_H_