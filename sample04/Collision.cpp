#include "Collision.h"


Collision::Collision()
{
}
void Collision::setTimeCol(float time)
{
	timeCol = time;
}
DIR Collision::isCollision(BaseObject *moveObject, BaseObject* dynamicObject)
{
	float timeCollision;

	Box dynamicBox = dynamicObject->getBouding();
	Box moveBox = moveObject->getBouding();

	velocity = moveObject->getVelocity();
	float normalX = 0, normalY = 0;

	// kiem tra va cham không cần biết vận tốc cua doi tuong
	DIR dir = AABB(moveBox, dynamicBox);
	if (dir == DIR::NONE)
	{
		// hệ qui chiếu object2
		moveBox.vx -= dynamicBox.vx;
		moveBox.vy -= dynamicBox.vy;
		dynamicBox.vx = dynamicBox.vy = 0;


		// vật nằm trong không gian của đối tượng 
		if (AABB(dynamicBox, GetSweptBroadPhaseBox(moveBox)) != DIR::NONE)
		{
			timeCollision = SweptAABB(moveBox, dynamicBox, normalX, normalY);
			setTimeCol(timeCollision);
			if (timeCollision > 0.0f && timeCollision < 1.0f)
			{
				// update velocity
				if (abs(velocity.x) >= abs(moveBox.vx * timeCollision + normalX) && normalX != 0.0f)
					velocity.x = moveBox.vx * timeCollision + normalX;

				if (abs(velocity.y) >= abs(moveBox.vy * timeCollision + normalY) && normalY != 0.0f)
					velocity.y = moveBox.vy * timeCollision + normalY;

				//object1->setVelocity(velocity.x, velocity.y);

				if (normalX != 0.0f)
				{
					if (normalX == -1.0f)
						return DIR::LEFT;

					if (normalX == 1.0f)
						return DIR::RIGHT;
				}
				else
				{
					if (normalY != 0.0f)
					{
						if (normalY == 1.0f)
							return DIR::BOTTOM;

						if (normalY == -1.0f)
							return DIR::TOP;
					}
				}
			}
			else
			{
				return DIR::NONE;
			}
		}
		else
		{
			return DIR::NONE;
		}
	}
	else // xảy ra va chạm
	{
		D3DXVECTOR2 position = moveObject->getPosition();

		
		if (dir == DIR::BOTTOM) // bottom
		{
			position.y = dynamicBox.y - moveBox.height - 1;
		}
		else if (dir == DIR::LEFT)  // left
		{
			position.x = dynamicBox.x - moveBox.width - 1;
		}
		else if (dir == TOP) // top
		{
			position.y = dynamicBox.y + dynamicBox.height + 1;
		}
		else if (dir == DIR::RIGHT)
		{
			position.x = dynamicBox.x + dynamicBox.width + 1;
		}

		moveObject->setPosition(position.x, position.y);

		return dir;
	}
}

Collision::~Collision()
{
}
