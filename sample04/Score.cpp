#include "Score.h"
#include "writer.h"
#include <string.h>
#include <string>

Score::Score() :BaseObject(){}
Score::Score(LPD3DXFONT font, float _x, float _y, int score) : BaseObject(_x, _y, 0, 0)
{
	_font = font;
	distanceMove = 0;
	_vy = -100;
	_isNeedDelete = false;
	_m_Velocity.y = 0;
	_score = score;
}
void Score::Update(float TPF)
{
	_m_Velocity.y = _vy* TPF;
	_m_Position.y += _m_Velocity.y;
	distanceMove -= 1;
	if (distanceMove<-10)
		_isNeedDelete = true;
}
void Score::Render()
{
	string text = to_string(_score);
	wstring ws;
	StringToWString(ws, text);
	D3DXVECTOR3 position(_m_Position.x, _m_Position.y, 0);
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = 1.0f;
	mt._41 = 0;
	mt._42 = 0;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);
	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	DrawTxt(ws, vp_pos.x, vp_pos.y, _font);
}
int Score::GetVar(char* varName)
{
	if (strcmp(varName, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}