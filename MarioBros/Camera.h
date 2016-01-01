#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <d3dx9.h>

class BaseObject;
class Camera
{
public:
	float _x;
	float _y;
	float _vx;
	int _width;
	int _height;
	BaseObject* _obj;

	RECT _rect;

	Camera(float x, float y, float width, float height);
	void ResetRect();
	~Camera();
	void Update();
};
#endif
