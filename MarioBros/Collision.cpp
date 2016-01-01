#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}
bool Collision::IsCollision(RECT rect, RECT rect2)
{
	bool c1 = (rect.left >= rect2.left)
		&& (rect.right <= rect2.right)
		&& (rect.top >= rect2.top)
		&& (rect.bottom <= rect2.bottom);

	float dh = (fabs((float)(rect2.top - rect.bottom)) > fabs((float)(rect2.bottom - rect.top))) ? fabs((float)(rect2.top - rect.bottom)) : fabs((float)(rect2.bottom - rect.top));
	float dw = (fabs((float)(rect2.left - rect.right)) > fabs((float)rect2.right - rect.left)) ? fabs((float)(rect2.left - rect.right)) : fabs((float)(rect2.right - rect.left));

	return ((dw <= ((rect2.right - rect2.left) + (rect.right - rect.left))) &&
		(dh <= ((rect2.bottom - rect2.top) + (rect.bottom - rect.top))) || c1);
}
EDirect Collision::GetCollisionDir(RECT _rect1, RECT _rect2)
{

	if (IsCollision(_rect1, _rect2))
	{
		float top = abs(_rect1.top - _rect2.bottom);
		float botom =abs(_rect1.bottom - _rect2.top);
		float left = abs(_rect1.left - _rect2.right);
		float right = abs(_rect1.right - _rect2.left);
		float rs = min(min(right, left), min(top,botom));
		if (rs == top)
		{
			return Top;
		}
		if (rs == botom)
		{
			return Bottom;
		}
		if (rs == left)
		{
			return Left;
		}
		if (rs == right)
		{
			return Right;
		}
	}
	return None;
}