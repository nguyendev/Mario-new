#include "Score.h"
#include "Writer.h"
#include <string.h>
#include <string>

Score::Score() :BaseObject(){}
Score::Score(CSprite* sprite, float _x, float _y, float camerax, float cameray, int score) : BaseObject(_x, _y, camerax, cameray)
{
	
	_sprite = sprite;
	distanceMove = 0;
	_vy = -10;
	_isNeedDelete = false;
	_m_Velocity.y = 0;
	_score = score;
}
void Score::Update(float TPF)
{
	_m_Velocity.y = _vy* TPF;
	_m_Position.y += _m_Velocity.y;
	distanceMove -= 1;
	if (distanceMove<-100)
		_isNeedDelete = true;
}
void Score::Render()
{
	DrawNumber(_sprite, _score, _m_Position.x, _m_Position.y,Camera::_cameraX,Camera::_cameraY);
}
int Score::GetVar(char* varName)
{
	if (strcmp(varName, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}