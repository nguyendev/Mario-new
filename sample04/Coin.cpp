#include "Coin.h"


Coin::Coin()
{
}
Coin::Coin(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_m_Position.x = x;
	_m_Position.y = y;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	timeFly = 0;
}
void Coin::Activate(float TPF)
{
		if (timeFly < 8){	// flying up

			Render();
			_m_Position.y -= 8;
			_sprite->Next(TPF);
			timeFly++;
		}
		if (timeFly >= 8 && timeFly < 16){	// falling down
			Render();
			_sprite->Next(TPF);
			_m_Position.y += 8;
			timeFly++;
		}
		if (timeFly == 16)
			_sprite->setIndex(7);
}
void Coin::Render()
{
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, ITEM_DEEP);
}
Coin::~Coin()
{
}