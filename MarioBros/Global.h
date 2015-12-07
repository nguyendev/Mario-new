#pragma once
#ifndef _GLOBAL_
#define _GLOBAL_

#define PI				3.141592654
#define TILE_SIZE		40
#define ZOOM			2.5
#define G				2000
#define WIDTH			800
#define HEIGHT			600
#define YMENU_MAX		405
#define YMENU_MIN		360
#define YMENU			40
#define PIXEL 4

enum _SPRITE
{
	S_CLOUD,
	S_SCENE,
	S_BASIC,
	S_GRASS,
	S_MOUNTAIN,
	S_SMARIO,
	S_BMARIO,
};
enum ITEM_STATE
{

};
enum TERRAIN_STATE
{
};
enum ENEMY_STATE
{

};
enum MENU_STATE
{
	MS_MENU,
	MS_PLAYING,
};
enum MARIO_STATE
{

};
enum BULLET_STATE
{

};
#endif