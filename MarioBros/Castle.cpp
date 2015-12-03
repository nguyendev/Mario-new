#include "Castle.h"
#include "BaseObject.h"
#include "GLobal.h"
#include "Animation.h"
#include "Sprite.h"

Castle::Castle():BaseObject(){}
Castle::Castle(float _x, float _y,float width,float height,int ID,Sprite* sprite):BaseObject(_x,_y,width,height)
{
	_sprite	=sprite;
	_ID	=ID;	
	_ani=new Animation(1,1,0,_sprite);
	ResetRect();
}
void Castle::Render()
{
	_sprite->Draw(_x,_y,1,1,_ani->GetRect(1),1);	//Cửa sổ
}
void Castle::ResetRect()
{

}