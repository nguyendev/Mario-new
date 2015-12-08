#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "BaseObject.h"
class Camera
{
public:
	static float _cameraX;
	static float _cameraY;
	Camera();
	void Update(BaseObject* mario);
	~Camera();
};

#endif _CAMERA_H
