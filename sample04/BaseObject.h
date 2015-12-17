#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_

#include <d3dx9.h>
#include <list>
#include <fstream>
#include "KeyBoard.h"
#include "sprite.h"
#include "SweptAABB.h"

using namespace std;

class CSprite;
class QuadTree;
class CGameMario;
class BaseObject
{
protected:
	D3DXVECTOR2		_m_Position;
	D3DXVECTOR2		_m_Velocity;
public:
	// Thông tin cơ bản
	float _width;
	float _height;
	float _vx_last;	// last vx of mario before stop ( to determine the direction of mario )
	float _cameraX;
	float _cameraY;
	int _ID;
	RECT _rect;

	//test-------

	void				setPositionX(float);
	float				getPositionX(){ return _m_Position.x; }

	void				setPositionY(float);
	float				getPositionY(){ return _m_Position.y; }

	void				setPosition(float, float);
	D3DXVECTOR2			getPosition(){ return _m_Position; }

	void				setVelocity(float, float);
	D3DXVECTOR2			getVelocity(){ return _m_Velocity; }

	Box					getBouding();
	//----------
	CGameMario* _game;
	//Information render
	CSprite* _sprite;
	QuadTree* _oldNode;
	BaseObject* obj;
	BaseObject();
	BaseObject(float x, float y, float cameraX, float cameraY);
	~BaseObject();
	virtual void ProcessInput(KeyBoard* keyboard){};
	virtual void Update(float t,list<BaseObject*>* staticObj){};
	virtual void Render(){};
	virtual void CollisionTemp(BaseObject *, float t){};
	virtual void ResetRect();
};

#endif