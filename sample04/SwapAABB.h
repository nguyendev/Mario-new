#ifndef _SWEPTAABB_
#define _SWEPTAABB_

#include "d3d9.h"
#include "Global.h"
#include <limits>

using namespace std;

// tao mot khong gian boi doi tuong cung van toc
static Box GetSweptBroadPhaseBox(Box b)
{
	Box broadphasebox(0, 0, 0, 0);

	broadphasebox.x = b.vx > 0 ? b.x : (float)(b.x + b.vx);
	broadphasebox.y = b.vy > 0 ? b.y : b.y + (float)b.vy;
	broadphasebox.width = b.vx > 0 ? b.vx + b.width : abs(b.vx - b.width);
	broadphasebox.height = b.vy > 0 ? b.vy + b.height : abs(b.vy - b.height);

	return broadphasebox;
}

// kiểm tra vật có nằm ngoài vùng
// kiểm tra va chạm khi chưa có vận tốc
static DIR AABB(Box box1, Box box2)
{
	float l = box2.x - (box1.x + box1.width);
	float r = box1.x - (box2.x + box2.width);
	float t = box1.y - (box2.height + box2.y);
	float b = box2.y - (box1.height + box1.y);

	// check that there was a collision
	if (l > 0 || r > 0 || t > 0 || b > 0)
		return DIR::NONE;


	//// co va cham khong can biet va cham ben nao
	if (b <= 0 && box1.y < box2.y) return DIR::BOTTOM;
	if (t <= 0 && box1.y + box1.height > box2.y + box2.height) return DIR::TOP;
	if (l <= 0 && box1.x < box2.x) return DIR::LEFT;
	if (r <= 0 && box1.x + box1.width > box2.x + box2.width) return DIR::RIGHT;
	//RECT *_rect1 = Rectangle( , *_rect2, *_rect;
	//_rect1->left = box1.x;
	//_rect1->right = box1.x + box1.width;
	//_rect1->top = box1.y;
	//_rect1->bottom = box1.y + box1.height;
	//
	//_rect2->left = box2.x;
	//_rect2->right = box2.x + box2.width;
	//_rect2->top = box2.y;
	//_rect2->bottom = box2.y + box2.height;
	////	// co va cham khong can biet va cham ben nao
	//if (IntersectRect(_rect, _rect1, _rect2))
	//{
	//	float top = abs(_rect1->top - _rect2->bottom);
	//	float botom = abs(_rect1->bottom - _rect2->top);
	//	float left = abs(_rect1->left - _rect2->right);
	//	float right = abs(_rect1->right - _rect2->left);
	//	float rs = min(min(right, left), min(top, botom));
	//	if (rs == top)
	//	{
	//		return DIR::TOP;
	//	}
	//	if (rs == botom)
	//	{
	//		return DIR::BOTTOM;
	//	}
	//	if (rs == left)
	//	{
	//		return DIR::LEFT;
	//	}
	//	if (rs == right)
	//	{
	//		return DIR::RIGHT;
	//	}
	}
	
	
//}

// thuat toan xet va cham
static float SweptAABB(Box b1, Box b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.width);
		xInvExit = (b2.x + b2.width) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.width) - b1.x;
		xInvExit = b2.x - (b1.x + b1.width);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.height);
		yInvExit = (b2.y + b2.height) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.height) - b1.y;
		yInvExit = b2.y - (b1.y + b1.height);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = (float)xInvEntry / b1.vx;
		xExit = (float)xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = (float)yInvEntry / b1.vy;
		yExit = (float)yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.20f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f) // top
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else // bottom
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

#endif