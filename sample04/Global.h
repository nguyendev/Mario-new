#pragma once
#include <windows.h>
#ifndef _GLOBAL_
#define _GLOBAL_

#define PI				3.141592654
#define G				2000
#define WIDTH			800
#define HEIGHT			600
#define YMENU_MAX		405
#define YMENU_MIN		360
#define YMENU			40
#define PIXEL 4
#define ZOOM			2.5
#define MARIO_VOID    "MARIO VOID"


//Load image
#define GOOMBA_IMAGE		"Image\\imgGoomba.bmp"
#define BMARIO_IMAGE		"Image\\imgBigMario.png"
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
#define SMARIO__IMAGE		"Image\\imgSmallMario.png"
#define STAR_IMAGE			"Image\\imgStar.png"

//Deep Object
#define GOOMBA_DEEP			0.5
#define BRICK_DEEP			0.5
#define S_EXPLOSION_DEEP	0.5
#define FIREBULLET_DEEP		0.5
#define FLAG_DEEP			0.5
#define FLOWER_DEEP			0.5
#define FUNGI_DEEP			0.5
#define KOOPA_DEEP			0.5
#define MONEY_DEEP			0.5	
#define NUMBER_DEEP			0.5
#define PIPE_DEEP			0.6
#define PIRHANA_DEEP		0.5
#define MARIO_DEEP			0.4
#define KEYBOARD_BUFFER_SIZE	1024
#define CHANGE_POSY			3


#define ANIMATE_RATE 30		//fixed 60->30


enum DIR
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	NONE
};
enum _COL
{
	BRICK = 18
};
enum _SPRITE
{
	S_GOOMBA,
	S_BMARIO,
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
	S_SMARIO,
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
enum GAME_STATE
{
	GS_MENU,
	GS_PLAYING,
	GS_LOAD,
	GS_SAVE,
	GS_WIN,
	GS_GAMEOVER,
	GS_NEXT_STAGE,
	GS_SUB_STAGE,
	GS_REPLAY,
	GS_RETURN_STAGE,
	GS_ABOUT,
	GS_CONFIRM
};
enum MARIO_STATE
{

};
enum BULLET_STATE
{

};
#endif