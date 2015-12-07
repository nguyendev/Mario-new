#include "Mario.h"
#include "Global.h"

#define MARIO_SPEED 5
Mario::Mario() :BaseObject(){}

Mario::Mario(float x, float y, float width, float height,int vxObj, int vyObj, float vx, float vy, Sprite* sprite) : BaseObject(x, y, width, height,vxObj, vyObj, vx, vy)
{
	_sprite = sprite;
	_ani = new Animation(8, 4, 0.15, sprite);
	_ani->index = 1;
	waitNextImage = 0;
	vMax = 250;
	_vxObj = 0;
	_vxObj = 0;
	_vxObj_last = 1.0f;

	vx = vy = ax = ay = 0;
	isChangingDirectionToLeft = isChangingDirectionToRight = false;

}

void Mario::Update(BaseObject* _staticObjs[], BaseObject* _dynamicObjs[], Input* input, float TPF)
{
	ProcessInput(input);
	Move(TPF);
	// Smooth the move and recognize if the face is right or not?
	UpdateAnimation(TPF);
	_vx = _x - 400;
	//int vpx = xc;
	if (_vx <= 0) _vx = 0;
	this->Render();
}

void Mario::Move(float TPF)
{
	/*_x += _vxObj*TPF;
	_y += _vyObj*TPF;*/
}

void Mario::UpdateAnimation(float TPF)
{
	//if (isJumping)
	//	_ani->SetIndex(6);
	//else if (isJumping == false)
	//{	
	//		_ani->Update(3, 5, TPF);
	//}

}

void Mario::ProcessInput(Input* input)
{
	if (input->KeyDown(DIK_RIGHT))
	{
		_vxObj = MARIO_SPEED;
		_vxObj_last = _vxObj;
	}
	else
	if (input->KeyDown(DIK_LEFT))
	{
		_vxObj = -MARIO_SPEED;
		_vxObj_last = _vxObj;
	}
	else
	{
		_vxObj = 0;
	}

}

void Mario::Render()
{
	if (_vxObj>0)
		_sprite->Draw(_x, _y, _vx, _vy, ZOOM_MARIO, ZOOM_MARIO, _ani->GetRect(_ani->index), DEEP_MARIO);
	else
		_sprite->Draw(_x, _y, _vx, _vy, -ZOOM_MARIO, ZOOM_MARIO, _ani->GetRect(_ani->index), DEEP_MARIO);
}

Mario::~Mario()
{
}
