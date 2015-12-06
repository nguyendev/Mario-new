#include "Mario.h"
#include "Global.h"


Mario::Mario() :BaseObject(){}

Mario::Mario(float x, float y, float width, float height,float vx, float vy, Sprite* sprite) : BaseObject(x, y, width, height, vx, vy)
{
	_sprite = sprite;
	_ani = new Animation(8, 4, 0.15, sprite);
	_ani->index = 1;
	waitNextImage = 0;
	vMax = 250;
	vx = vy = ax = ay = 0;
	isChangingDirectionToLeft = isChangingDirectionToRight = false;
}

void Mario::Update(BaseObject* _staticObjs[], BaseObject* _dynamicObjs[], Input* input, float TPF)
{
	ProcessInput(input);
	Move(TPF);
	// Smooth the move and recognize if the face is right or not?
	UpdateAnimation(TPF);
	this->Render();
}

void Mario::Move(float TPF)
{

}

void Mario::UpdateAnimation(float TPF)
{
	if (isJumping)
		_ani->SetIndex(6);
	else if (isJumping == false)
	{	
			_ani->Update(3, 5, TPF);
	}

}

void Mario::ProcessInput(Input* input)
{
	if (input->KeyDown(DIK_RIGHT))
	{
		_x+= 5;
	}
	if (input->KeyDown(DIK_LEFT))
	{
		_x-= 5;
	}
	
}

void Mario::Render()
{
	if (isRight)
		_sprite->Draw(_x, _y, _vx, _vy, ZOOM_MARIO, ZOOM_MARIO, _ani->GetRect(_ani->index), DEEP_MARIO);
	else
		_sprite->Draw(_x, _y, _vx, _vy, -ZOOM_MARIO, ZOOM_MARIO, _ani->GetRect(_ani->index), DEEP_MARIO);
}

Mario::~Mario()
{
}
