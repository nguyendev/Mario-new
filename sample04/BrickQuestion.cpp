#include "BrickQuestion.h"
#include "Global.h"


BrickQuestion::BrickQuestion() :BaseObject()
{
}
BrickQuestion::BrickQuestion(float x, float y, float _cameraX, float _cameraY, int ID, CSprite* sprite, int SpriteIndex) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_SpriteIndex = SpriteIndex;
	_widthRect = _width;
	_heightRect = _height;
}
void BrickQuestion::Update()
{
}
void BrickQuestion::Render()
{
	_sprite->setIndex(_SpriteIndex);
	_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);

}
