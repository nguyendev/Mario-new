#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "BaseObject.h"
#include <list>
using namespace std;

class Castle:public BaseObject
{
public:
	Castle();
	Castle(float _x, float _y,float width,float height,int _ID,Sprite* _sprite);
	void Render();
	void ResetRect();
	
};