#pragma once
#include "BaseObject.h"
#include "Sprite.h"
#include "Animation.h"

#define DEEP_MARIO 0.5
#define ZOOM_MARIO 2


class Mario : public BaseObject
{
private:
	float waitNextImage;
	int vMax;
	bool isChangingDirectionToLeft;
	bool isChangingDirectionToRight;
public:
	float	vx;
	float	vy;
	float	ax;
	float	ay;
	bool isRight;
	float timeJumped;
	bool isJumping;
	Camera* camera;
	Mario();
	Mario(float x, float y, float width, float height, Sprite* sprite);
	virtual void Render();
	virtual void Update(BaseObject* _staticObjs[], BaseObject* _dynamicObjs[], Input* input, float TPF);
	void UpdateAnimation(float TPF);
	void Move(float TPF);
	void ProcessInput(Input* input);
	~Mario();
};

