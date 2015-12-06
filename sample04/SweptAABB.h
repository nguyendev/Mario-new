#pragma once
#include <limits>
#include <algorithm>
using namespace std;
struct Box
{
	//position of top-left corner
	float x, y;

	//dimensions
	float w, h;

	//velocity
	float vx, vy;
};
class AABB
{
public:
	float SweptAABB(Box b1, Box b2, float& normalx, float &normaly);
	AABB();
	~AABB();
	void Co();
};

