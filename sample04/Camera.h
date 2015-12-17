#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "BaseObject.h"
#include "QuadTree.h"
class Camera
{
public:
	static float _cameraX;
	static float _cameraY;
	float _width;
	float _height;

	RECT _rect;
	Camera(){};
	void Update(BaseObject* mario, QuadTree* quadTree);
	~Camera();
	Camera(float _x, float _y, float _width, float _height);
	void ResetRect();
};

#endif _CAMERA_H
