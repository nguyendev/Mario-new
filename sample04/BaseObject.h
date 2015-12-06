#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_

#include <d3dx9.h>
#include <list>
#include <fstream>
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

	int _ID;

	RECT _rect;

	//Information render

	CSprite* _sprite;
	BaseObject();
	BaseObject(float x, float y);
	~BaseObject();

	virtual void Update(){};
	virtual void Render(){};
};

#endif