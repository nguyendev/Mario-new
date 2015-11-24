#ifndef _PIPE_H_
#define _PIPE_H_
#include "BaseObject.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>
#include "Global.h"
#include "Camera.h"

class Pipe:public BaseObject
{
public:
	Pipe();
	Pipe(float x, float y, float _width, float _height, int ID, Sprite* sprite);
	virtual void Render();
	void ResetWhenReload(Sprite* sprite);
};

#endif _PIPE_H_