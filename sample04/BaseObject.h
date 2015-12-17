#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_

#include <d3dx9.h>
#include <list>
#include <fstream>
#include "KeyBoard.h"
#include "sprite.h"

using namespace std;

class CSprite;
class QuadTree;
class CGameMario;
class BaseObject
{
public:
	// Thông tin cơ bản
	float _x;		//postion x
	float _y;		//postion y
	float _vx;		//speed horizontal
	float _vy;		//speed vertical
	float _width;
	float _height;
	float _vx_last;	// last vx of mario before stop ( to determine the direction of mario )
	float _cameraX;
	float _cameraY;
	int _ID;
	RECT _rect;
	CGameMario* _game;
	//Information render
	CSprite* _sprite;
	QuadTree* _oldNode;
	BaseObject* obj;
	BaseObject();
	BaseObject(float xWorld, float yWorld, float cameraX, float cameraY);
	~BaseObject();
	virtual void ProcessInput(KeyBoard* keyboard){};
	virtual void Update(float t){};
	virtual void Render(){};
	virtual void CollisionTemp(BaseObject *, float t){};
	virtual void ResetRect();
};

#endif