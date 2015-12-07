#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <d3dx9.h>

class BaseObject;
class Camera
{
public:

	RECT _rect;

	Camera();
	~Camera();
	void Update(BaseObject* _obj);
};
#endif
