#pragma once

#include "Sprite.h"
#include "BaseObject.h"
#include <list>
using namespace std;

class Score :public BaseObject
{
public:
	float	distanceMove;
	bool	_isNeedDelete;
	float _vy;
	int		_score;
	LPD3DXFONT	_font;
	Score();
	Score(LPD3DXFONT font, float _x, float _y, int _score);
	void Update(float TPF);
	void Render();
	int	GetVar(char* varName);
};