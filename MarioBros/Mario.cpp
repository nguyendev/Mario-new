#include "Mario.h"
#include "Global.h"


Mario::Mario() :BaseObject(){}

Mario::Mario(float x, float y, float width, float height, Sprite* sprite) : BaseObject(x, y, width, height)
{
	_sprite = sprite;
	_ani = new Animation(8, 4, 0.15, sprite);
	_ani->index = 1;
	waitNextImage = 0;
	vMax = 250;
	vx = vy = ax = ay = 0;
	isChangingDirectionToLeft = isChangingDirectionToRight = false;
	camera = new Camera(0, 0, 800, 600);
}

void Mario::Update(BaseObject* _staticObjs[], BaseObject* _dynamicObjs[], Input* input, float TPF)
{
	ProcessInput(input);
	Move(TPF);
	// Smooth the move and recognize if the face is right or not?
	if (vx > 0)
	{
		ax = -G / 4;
		isRight = true;
	}
	else if (vx < 0)
	{
		ax = G / 4;
		isRight = false;
	}

	// y direction
	if (vy>0)
	{
		isJumping = true;
		timeJumped = 10;
	}
	else if (vy == 0)
		isJumping = false;
	UpdateAnimation(TPF);
	this->Render();
}

void Mario::Move(float TPF)
{
	//In x direction
	vx += ax*TPF;
	if (vx > vMax)
		vx = vMax;
	else if (vx < -vMax)
		vx = -vMax;
	_x += vx*TPF + 0.5*ax*TPF*TPF;
	// không đi quá camera
	if (_x<camera->_x)									//Không cho đi quá Camera
		_x = camera->_x;
	if (_x>camera->_x + WIDTH - TILE_SIZE)
		_x = camera->_x + WIDTH - TILE_SIZE;
	// In y direction
	/*ay = G;
	vy += ay*TPF;
	_y += vy*TPF + 0.5*ay*TPF*TPF;*/


	if (vy>0)
	{
		isJumping = true;
		timeJumped = 10;
	}
	//Reset accelarate
	if (vx*ax<0)
	{
		if (vx>-50 && vx<50)
		{
			vx = 0;
			ax = 0;
		}
	}
}

void Mario::UpdateAnimation(float TPF)
{
	if (isJumping)
		_ani->SetIndex(6);
	else if (isJumping == false)
	{
		if (vx != 0)
		{
			_ani->Update(3, 5, TPF);
		}
		else
			_ani->SetIndex(1);
	}

}

void Mario::ProcessInput(Input* input)
{
	if (input->KeyDown(DIK_RIGHT))
	{
		ax = G / 3;
		if (input->KeyDown(DIK_Z))
		{
			vMax = 400;
		}
		else
		{
			vMax = 250;
		}
	}
	if (input->KeyDown(DIK_LEFT))
	{
		ax = -G / 3;
		if (input->KeyDown(DIK_Z))
		{
			vMax = 400;
		}
		else
		{
			vMax = 250;
		}
	}
	if (input->KeyDown(DIK_SPACE))
	{
		if (timeJumped < 0.2)
		{
			vy = -700;
			isJumping = true;
		}
	}
}

void Mario::Render()
{
	if (isRight)
		_sprite->Draw(_x, _y, 0, 600, ZOOM_MARIO, ZOOM_MARIO, _ani->GetRect(_ani->index), DEEP_MARIO);
	else
		_sprite->Draw(_x, _y, 0, 600, - ZOOM_MARIO, ZOOM_MARIO, _ani->GetRect(_ani->index), DEEP_MARIO);
}

Mario::~Mario()
{
}
