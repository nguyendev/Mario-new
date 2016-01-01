#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_

#include <d3dx9.h>
#include <list>
#include <fstream>
#include "SwapAABB.h"
#include "KeyBoard.h"
#include "sprite.h"
using namespace std;

extern class KeyBoard;
extern class CGameMario;
extern class CSprite;
extern class QuadTree;
extern class CGame;
class BaseObject
{
protected:
	D3DXVECTOR2		_m_Position;
	D3DXVECTOR2		_m_Velocity;
	bool			m_isActive;

	StatusObject	m_status;
public:
	// Thông tin cơ bản
	float _width;
	float _height;
	float _widthRect;
	float _heightRect;
	float _vx_last;	// last vx of mario before stop ( to determine the direction of mario )
	float _cameraX;
	float _cameraY;
	bool _isNeedDelete;
	int _ID;
	RECT _rect;
	CGameMario* _game;
	CSprite* _sprite;
	QuadTree* _oldNode;
	BaseObject* obj;

	void				setPositionX(float);
	float				getPositionX(){ return _m_Position.x; }

	void				setPositionY(float);
	float				getPositionY(){ return _m_Position.y; }

	void				setPosition(float, float);
	D3DXVECTOR2			getPosition(){ return _m_Position; }

	void				setVelocity(float, float);
	D3DXVECTOR2			getVelocity(){ return _m_Velocity; }

	void				setStatusObject(StatusObject);
	StatusObject		getStatusOBject(){ return m_status; }

	Box					getBouding();

	BaseObject();
	BaseObject(float x, float y, float cameraX, float cameraY);
	~BaseObject();
	virtual void	SetState(char* varName, int val){};
	virtual int		GetState(char* varName){ return -1; };
	virtual void	Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyborad){};
	virtual void	Render(){};
};

#endif