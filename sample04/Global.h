#pragma once
#include <Windows.h>
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
#define MARIO_VOID    "MARIO VOID"

#define GOOMBA_IMAGE		"Image\\imgGoomba.bmp"
#define BMARIO_IMAGE_01		"Image\\ImgBigMario_01.png"
#define BMARIO_IMAGE_02		"Image\\ImgBigMario_02.png"
#define BRICK_IMAGE			"Image\\imgBrick.png"
#define S_EXPLOSION_IMAGE	"Image\\ImgExplosion.png"
#define FIREBULLET_IMAGE	"Image\\ImgFireBullet.png"
#define FLAG_IMAGE			"Image\\imgFlag.png"
#define FLOWER_IMAGE		"Image\\imgFlower.png"
#define FUNGI_IMAGE			"Image\\imgFungi.png"
#define KOOPA_IMAGE			"Image\\imgKoopa.bmp"
#define MONEY_IMAGE			"Image\\imgMoney.png"
#define NUMBER_IMAGE		"Image\\imgNumber.bmp"
#define PIPE_IMAGE			"Image\\imgPipe.bmp"
#define PIRHANA_IMAGE		"Image\\imgPirhana.png"
#define SMARIO__IMAGE_01	"Image\\imgSmallMario_01.png"
#define SMARIO__IMAGE_02	"Image\\imgSmallMario_02.png"
#define STAR_IMAGE			"Image\\imgStar.png"


enum _SPRITE
{
	S_GOOMBA,
	S_BMARIO_01,
	S_BMARIO_02,
	S_BRICK,
	S_EXPLOSION,
	S_FIREBULLET,
	S_FLAG,
	S_FLOWER,
	S_FUNGI,
	S_KOOPA,
	S_MONEY,
	S_NUMBER,
	S_PIPE,
	S_PIRHANA,
	S_SMARIO_01,
	S_SMARIO_02,
	S_STAR
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