#include <windows.h>
#include "GameMario.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGameMario g(hInstance,L"Mario Sample - A larger world",GAME_SCREEN_RESOLUTION_800_600_24,0,60);
	
	g.Init();
	g.Run();

	return 0;
}


