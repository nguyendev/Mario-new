#include "Collision.h"
#include <limits>
#include <algorithm>

float SweptAABB(BaseObject* b1, BaseObject* b2, float &normalx, float &normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	//tim khoang cach giua hai vat the o canh gan va canh xa

	if (b1->_vx > 0.0f)
	{
		xInvEntry = abs(b2->_x - (b1->_x + b1->_width));
		xInvExit = (b2->_x + b2->_width) - b1->_x;
	}
	else
	{
		xInvEntry = (b2->_x + b2->_width) - b1->_x;
		xInvExit = b2->_x - (b1->_x + b1->_width);
	}

	if (b1->_vy > 0.0f)
	{
		yInvEntry = b2->_y - (b1->_y + b1->_height);
		yInvExit = (b2->_y + b2->_height) - b1->_y;
	}
	else
	{
		yInvEntry = (b2->_y + b2->_height) - b1->_y;
		yInvExit = b2->_y - (b1->_y + b1->_height);
	}


	float xEntry, yEntry;
	float xExit, yExit;

	if (b1->_vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1->_vx;
		xExit = xInvExit / b1->_vx;
	}

	if (b1->_vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1->_vx;
		yExit = yInvExit / b1->_vy;
	}

	//find the earliest / last times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	//if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else// if there was a collision
	{
		//calculate normal of collided surface
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
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}
		//return the time of collision
		return entryTime;
	}
}
BaseObject* GetSweptBroadphaseBox(BaseObject *b)
{
	BaseObject* broadphasebox = new BaseObject();
	broadphasebox->_vx = b->_vx;
	broadphasebox->_vy = b->_vy;
	broadphasebox->_x = b->_vx > 0 ? b->_x : b->_x + b->_vx;
	broadphasebox->_y = b->_vy > 0 ? b->_y : b->_y + b->_vy;
	broadphasebox->_width = b->_vx > 0 ? b->_vx + b->_width : b->_width - b->_vx;
	broadphasebox->_height = b->_vy > 0 ? b->_vy + b->_height : b->_height - b->_vy;
	return broadphasebox;
}

bool AABBCheck(BaseObject* b1, BaseObject * b2)
{
	return !(b1->_x + b1->_height<b2->_x || b1->_x>b2->_x + b2->_width || b1->_y + b1->_height<b2->_y || b1->_y>b2->_y + b2->_height);
}


DIR AABB(BaseObject* box1, BaseObject* box2)
{
	float l = box2->_x - (box1->_x + box1->_width);
	float r = box1->_x - (box2->_x + box2->_width);
	float t = box1->_y - (box2->_height + box2->_y);
	float b = box2->_y - (box1->_height + box1->_y);

	// check that there was a collision
	if (l > 0 || r > 0 || t > 0 || b > 0)
		return DIR::NONE;


	// co va cham khong can biet va cham ben nao
	if (b < 0 && box1->_y > box2->_y) return DIR::BOTTOM;
	if (t < 0 && box1->_y + box1->_height < box2->_y + box2->_height) return DIR::TOP;
	if (l <= 0 && box1->_x < box2->_x) return DIR::LEFT;
	if (r <= 0 && box1->_x + box1->_width > box2->_x + box2->_width) return DIR::RIGHT;

}
