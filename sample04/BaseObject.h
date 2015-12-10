#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_

#include <d3dx9.h>
#include <list>
#include <fstream>
#include "KeyBoard.h"
using namespace std;

class CSprite;
class BaseObject
{
public:
	// Thông tin cơ bản
	float _x;		//postion x
	float _y;		//postion y
	float _vx;
	float _vy;
	float _width;
	float _height;
	float _vx_last;	// last vx of mario before stop ( to determine the direction of mario )
	float _cameraX;
	float _cameraY;
	int _ID;
	RECT _rect;

	//Information render
	CSprite* _sprite;

	BaseObject();
	BaseObject(float xWorld, float yWorld, float cameraX, float cameraY);
	~BaseObject();
	virtual void ProcessInput(KeyBoard* keyboard){};
	virtual void Update(int t){};
	virtual void Render(){};
};

#endif