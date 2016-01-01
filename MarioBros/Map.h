
#ifndef _MAP_H_
#define _MAP_H_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Global.h"
#include "Pipe.h"
#include "Sprite.h"
#include "background.h"

class Game;
class Map
{
public:
	Map(char* filename, bool isBright, Game* game);
	~Map();
};
#endif
