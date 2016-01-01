#include "Map.h"
#include "BaseObject.h"
#include "Game.h"


Map::Map(char* filename, bool isBright, Game* game)
{
	int ID;
	int a[30000], n;
	srand((unsigned)time(NULL));
	FILE *outf = fopen(filename, "r");
	if (outf == NULL)
	{

		return;
	}

	int x, y;
	n = 0;
	BaseObject* obj = NULL;
	while (fscanf(outf, "%d" "%d" "%d", &ID, &x, &y) > 0)
	{
		switch (ID)
		{
		case 10:
			//obj = new Pipe(x, y, 80, 80, ID, game->_sprites[S_PIPE]);
			break;
		}
	}
	fclose(outf);
	obj = new Pipe(10, 10, 80, 80, 1010, game->_sprites[S_PIPE]);
	obj->Render();
	BaseObject* obj1 = NULL;
	obj1 = new BackGround(0, 0, 300, 300, 2000, game->_sprites[S_BACKGROUND]);
	obj1->Render();
}
Map::~Map()
{
}


