#pragma once
#include <d3dx9.h>
enum EDirect
{
	Left,
	Right,
	Top,
	Bottom,
	None
};
class Collision
{
public:
	Collision();
	~Collision();
	bool IsCollision(RECT , RECT); //nhận diện va chạm giữa 2 vật
	EDirect GetCollisionDir(RECT, RECT); //xác định hướng của va chạm để xử lý
};

