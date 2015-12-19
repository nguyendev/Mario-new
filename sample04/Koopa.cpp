#include "Koopa.h"
#define KOOPA_SPEED 100.0f

Koopa::Koopa()
{
}
Koopa::Koopa(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Velocity.x = -KOOPA_SPEED;		// demo, if the game is real, it is 0
	_m_Velocity.y = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	ResetRect();
}
void Koopa::Move(float t)
{
	_m_Position.x += _m_Velocity.x * t;
	_m_Position.y += _m_Velocity.y * t;
}
void Koopa::Update(float t, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj)
{

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(t);
		_sprite->Next(0, 1);
		last_time = now;
	}
}
void Koopa::Render()
{
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Koopa::CollisionTemp(BaseObject* obj)
{

}
Koopa::~Koopa()
{
}
