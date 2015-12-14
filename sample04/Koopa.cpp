#include "Koopa.h"


Koopa::Koopa()
{
}
Koopa::Koopa(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_vx = -0.1f;		// demo, if the game is real, it is 0
	_vy = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
}
void Koopa::Move(int t)
{
	_x += _vx * t;
	_y += _vy * t;
}
void Koopa::Update(int t)
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
	_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Koopa::CollisionTemp(BaseObject* obj)
{

}
Koopa::~Koopa()
{
}
