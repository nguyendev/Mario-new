#include "Bullet.h"
#include "BaseObject.h"
#include "Collision.h"
#include "Global.h"
#include "Sprite.h"
#include "Mario.h"
Bullet::Bullet() :BaseObject(){}
Bullet::Bullet(float x, float y, float _cameraX, float _cameraY, float vx, CSprite *sprite, CSprite* sprite1) : BaseObject(x, y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_sprite1 = sprite1;
	_isNeedDelete = false;
	timedelay = 0;
	timeblow = 0;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_widthRect = _width;
	_heightRect = _height;
	_m_Velocity.x = vx;
	_m_Velocity.y = ay = 0;
	_state = BS_IDLE;
	waitIncreaseVecY = 0;
	_sprite->setIndex(1);
}

Bullet::~Bullet(void)
{

}
void Bullet::Move(float TPF, list<BaseObject*> *staObjs, list<BaseObject*> *dynObjs)
{
	BaseObject* _obj;
	//theo phuong x
	_m_Position.x += _m_Velocity.x*TPF;
	list<BaseObject*>::iterator i;
	for (i = staObjs->begin(); i != staObjs->end(); i++)
	{
		_obj = *i;
		DIR dir = Collision::getInstance()->isCollision(this, _obj);
		float timeCollision = Collision::getInstance()->getTimeCollision();
		if (dir != DIR::NONE)
		{
			if (_obj->_ID >= 17 && _obj->_ID <= 22 || _obj->_ID == 52) //collision with Brick and special brick
			{
				/*_m_Velocity.x = 0;
				SetState("_state", BS_BLOW);*/
			}

		}
		/*if (_obj->_ID >= 20 && _obj->_ID <= 28)
		{
			if (Collision::RectVsRect(rect, obj->rect) == true)
			{
				vx = 0;
				x = xOld;
				SetVar("state", BS_BLOW);///				
			}
		}
		else if (obj->ID == 29)
		{
			if (x >= obj->x + 30)
				SetVar("state", BS_BLOW);
		}*/
	}
	//Theo phương y
	if (_state != BS_BLOW)
	{
		/*waitIncreaseVecY += TPF;
		if (waitIncreaseVecY > 0.3)
		{
			_m_Velocity.y += 1;
			waitIncreaseVecY = 0;
		}
		_m_Position.y += _m_Velocity.y;*/
		//for (i = staObjs->begin(); i != staObjs->end(); i++)
		//{
		//	obj = *i;
		//	if (obj->ID >= 20 && obj->ID <= 29)				//Nếu là thùng, đá , gạch...
		//	if (Collision::RectVsRect(rect, obj->rect) == true)
		//		collisionList->push_back(obj);
		//}

		////Xét va chạm để không bị rơi
		//if (collisionList->size()>0)
		//{
		//	Object* obj;
		//	list<Object*>::iterator i;
		//	for (i = collisionList->begin(); i != collisionList->end(); i++)
		//	{
		//		obj = *i;
		//		if (oldRect.bottom<obj->rect.bottom)
		//		if (obj->y - height<y)
		//		{
		//			y = obj->y - height;
		//			vy = -400;
		//		}
		//	}
		//	ResetRect();
		//}

		////xet va cham doi tuong dong
		//for (i = dynObjs->begin(); i != dynObjs->end(); i++)
		//{
		//	obj = *i;
		//	if (Collision::RectVsRect(rect, obj->rect) == true)
		//	{
		//		switch (obj->ID)
		//		{
		//		case 42:
		//			if (obj->GetVar("state") == ES_ACTIVING)
		//			{
		//				if (vx>0)
		//					obj->Huong = 1;
		//				else obj->Huong = 2;
		//				obj->SetVar("state", ES_FALL);
		//				SetVar("state", BS_BLOW);
		//			}
		//			break;
		//		case 41:
		//			if (obj->GetVar("state") == ES_ACTIVING)
		//			{
		//				if (vx>0)
		//					obj->Huong = 1;
		//				else obj->Huong = 2;
		//				obj->SetVar("state", ES_FALL);
		//				SetVar("state", BS_BLOW);
		//			}
		//			break;
		//		case 33:
		//			obj->SetVar("state", IS_ATE);
		//			SetVar("state", BS_BLOW);
		//			break;
		//		}
		//	}
		
	}
	//xOld = x;
	//yOld = y;

}
void Bullet::ChangeState(char state)
{
	_state = state;
	switch (_state)
	{
	case BS_ACTIVING:
		//_m_Velocity.y = 100;/////thay doi van toc y 
		//_m_Velocity.x = 200;
		break;
	case BS_BLOWED:
		_isNeedDelete = true;
		break;
	}
}
void Bullet::SetState(char* varName, int val)
{
	if (strcmp(varName, "_state") == 0)
	{
		ChangeState(val);
	}
}
int Bullet::GetState(char *varName)
{
	if (strcmp(varName, "_state") == 0)
		return _state;
	if (strcmp(varName, "_isNeedDelete") == 0)
		return _isNeedDelete;
	return -1;
}
void Bullet::Render()
{
	switch (_state)
	{
	case BS_ACTIVING:
		//_sprite->Render(_m_Position.x - 11, _m_Position.y - 12,_cameraX, _cameraY, 0.5);
		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, 0.3);
		break;
	case BS_BLOW:
		_sprite1->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, 0.3);
		break;
	}
}
void Bullet::Update(float TPF, list<BaseObject*>* staObjs, list<BaseObject*>* dynObjs, KeyBoard* input)
{
	switch (_state)
	{
	case BS_ACTIVING:
		Move(TPF, staObjs, dynObjs);
		_sprite->Next(0, 3, TPF);
		break;
	case BS_BLOW:
		//ani = new Animation(3, 1, 0, sprite1);
		timeblow += TPF;
		if (timeblow>0.1)
			_sprite1->setIndex(1);
		if (timeblow>0.2)
			_sprite1->setIndex(2);
		timedelay += TPF;
		if (timedelay>0.3)
			SetState("_state", BS_BLOWED);
		break;
	case BS_BLOWED:
		_isNeedDelete = true;
		break;
	}
}