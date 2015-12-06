#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_

#include <d3dx9.h>
#include <list>
#include <fstream>
using namespace std;

class Sprite;
class Animation;
class Input;
class Game;
class BaseObject
{
public:
	// Thông tin cơ bản
	float _x;		//postion x
	float _y;		//postion y
	float _width;	// width screen
	float _height;	//	height screen

	int _ID;
	char _direction;

	RECT _rect;
	Game* _game;

	//Information render
	Sprite* _sprite;
	Animation* _ani;

	BaseObject();
	BaseObject(float x, float y, float width, float height);
	~BaseObject();

	virtual void ResetRect();
	virtual void ResetWhenReload(Sprite* sprite){};
	virtual void SetVar(char* Name, int val){};
	virtual int	 GetVar(char* Name){ return -1; };
	virtual void Update(BaseObject* _staticObjs[], BaseObject* _dynamicObjs[], Input* input, float TPF){};
	virtual void Render(){};
	virtual void Save(fstream *fs){};
	virtual void Load(fstream *fs){};
};

#endif