﻿#pragma once
#include <windows.h>
#ifndef _GLOBAL_
#define _GLOBAL_

#define PI				3.141592654
#define G				10000
#define	VMAX			100
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
#define CASTLE_IMAGE		"Image\\imgCastle.png"
#define CLOUD_IMAGE			"Image\\imgCloud.png"
#define GRASS_IMAGE			"Image\\imgGrass.png"
#define MOUNTAIN_IMAGE		"Image\\imgMountain.png"

//Deep Object
#define GOOMBA_DEEP			0.5
#define BRICK_DEEP			0.4
#define S_EXPLOSION_DEEP	0.5
#define FIREBULLET_DEEP		0.5
#define FLAG_DEEP			0.5
#define FLOWER_DEEP			0.5
#define FUNGI_DEEP			0.5
#define KOOPA_DEEP			0.5
#define MONEY_DEEP			0.5	
#define NUMBER_DEEP			0.5
#define PIPE_DEEP			0.5
#define PIRHANA_DEEP		0.5
#define MARIO_DEEP			0.3
#define CASTLE_DEEP			0.5
#define CLOUD_DEEP			0.5
#define GRASS_DEEP			0.4
#define MOUNTAIN_DEEP		0.5
#define KEYBOARD_BUFFER_SIZE	1024
#define CHANGE_POSY			3


#define ANIMATE_RATE 60		//fixed 60->30


enum DIR
{
	NONE = 0,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};
enum _COL
{
	ID_BRICK_01 = 18,
	ID_BRICK_02 = 19,
	ID_CLOUD_LV_01 = 25,
	ID_CLOUD_LV_02 = 26,
	ID_CLOUD_LV_03 = 27,
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
	S_STAR,
	S_CASTLE,
	S_CLOUD,
	S_GRASS,
	S_MOUNTAIN
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
enum FSM_Mario
{
	STAND = 0,
	RUN,
	JUMP,
	FALL,
	SIT,
	DEAD,
	STAR
};

enum ENEMY_STATE
{
	ES_ACTIVING,
	ES_IDLE,			//Khi Goomba hoặc Koopa bị dậm
	ES_MOVE_SHELL_LEFT,		//Khi Koopa di chuyển trong mai rùa.
	ES_MOVE_SHELL_RIGHT,
	ES_FALL,				//Khi Goomba hoặc Koopa bị rơi (chuẩn bị chết)
	ES_DIED
};
enum class StatusObject
{
	ALIVE,
	DEAD
};

#endif