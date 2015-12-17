#include "StoneBrick.h"



StoneBrick::StoneBrick() :BaseObject()
{
}
StoneBrick::StoneBrick(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite,int SpriteIndex) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	ResetRect();
}
void StoneBrick::Update()
{
	_m_Position.x += 10;
}
void StoneBrick::Render()
{
	_sprite->setIndex(_SpriteIndex);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
