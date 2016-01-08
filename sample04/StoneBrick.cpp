#include "StoneBrick.h"
#include "BaseObject.h"



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
	_widthRect = _width;
	_heightRect = _height;
}
void StoneBrick::Update(float Time, list<BaseObject*>* staticObj, list<BaseObject*>* dynamicObj, KeyBoard* keyboard)
{

}
void StoneBrick::Render()
{
	_sprite->setIndex(_SpriteIndex);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
