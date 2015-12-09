#include "Collision.h"
#include <limits>
#include <algorithm>

float Collision::SweptAABB(BaseObject* b1, BaseObject* b2, float &normalx, float &normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	//tim khoang cach giua hai vat the o canh gan va canh xa

	if (b1->_vx > 0.0f)
	{
		xInvEntry = b2->_x - (b1->_x + b1->_width);
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
BaseObject* Collision::GetSweptBroadphaseBox(BaseObject *b)
{
	BaseObject* broadphasebox = new BaseObject();
	broadphasebox->_x = b->_vx > 0	? b->_x : b->_x + b->_vx;
	broadphasebox->_y = b->_vy > 0	? b->_y : b->_y + b->_vy;
	broadphasebox->_width = b->_vx > 0 ? b->_vx + b->_width : b->_width - b->_vx;
	broadphasebox->_height = b->_vy > 0 ? b->_vy + b->_height : b->_height - b->_vy;
	return broadphasebox;
}

bool Collision::AABBCheck(BaseObject* b1, BaseObject * b2)
{
	return !(b1->_x + b1->_height<b2->_x || b1->_x>b2->_x + b2->_width || b1->_y + b1->_height<b2->_y || b1->_y>b2->_y + b2->_height);
}


