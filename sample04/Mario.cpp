#include "Mario.h"
#include "Global.h"
#include "Collision.h"
Collision* checkCollision;

Mario::Mario(float x, float y, float cameraX, float cameraY, int ID, CSprite* sprite) :BaseObject(x, y, cameraX, cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
	_vx_last = 1.0f;
	ResetRect();
	checkCollision = new Collision();
}


Mario::~Mario()
{
}
void Mario::Move(float TPF)
{
	//Theo phương x
	_m_Velocity.x += ax*TPF;
	if (_m_Velocity.x > vMax) 
		_m_Velocity.x = vMax;	
	else if (_m_Velocity.x < -vMax) 
		_m_Velocity.x = -vMax;
	_m_Position.x += _m_Velocity.x * TPF + 1 / 2 * ax*TPF*TPF;
	//_m_Position.x += _m_Velocity.x * TPF;
	_m_Position.y += _m_Velocity.y * TPF;
	if (_m_Position.x < Camera::_cameraX)									//Không cho đi quá Camera
		_m_Position.x = Camera::_cameraX;
	if (_m_Position.x > Camera::_cameraX + WIDTH)
		_m_Position.x = Camera::_cameraX + WIDTH;

	//Theo phương y
	ay = G/2;
	_m_Velocity.y += ay*TPF;
	_m_Position.y += _m_Velocity.y*TPF + 1.0 / 2 * ay*TPF*TPF;
}
void Mario::Update(float TPF, list<BaseObject*>* staticObj)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Move(TPF);
		if (_m_Velocity.x > 0) _sprite->Next();
		if (_m_Velocity.x < 0) _sprite->Next();
		last_time = now;
	}
	list<BaseObject*>::iterator i;
	for (i = staticObj->begin(); i != staticObj->end(); i++)
	{
		obj = *i;
		DIR dir = checkCollision->isCollision(this, obj);
		//if (dir == DIR::LEFT && dir == DIR::TOP)
		//	this->setVelocity(this->getVelocity().x * -1, this->getVelocity().y);
		if (dir == DIR::TOP || dir == DIR::BOTTOM)
			this->setVelocity(this->getVelocity().x, this->getVelocity().y * -1);
		else if (dir == DIR::LEFT || dir == DIR::RIGHT)
			this->setVelocity(this->getVelocity().x * -1, this->getVelocity().y);
		
	}
}

void Mario::Render()
{
	if (_m_Velocity.x > 0)			_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_m_Velocity.x < 0)		_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else if (_vx_last < 0) _sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
	else					_sprite->Render(_m_Position.x, _m_Position.y, Camera::_cameraX, Camera::_cameraY, MARIO_DEEP);
}
void Mario::ProcessInput(KeyBoard* _keyboard)
{
	if (_keyboard->KeyDown(DIK_RIGHT))
	{
		//m_Velocity.x = MARIO_SPEED;
		//_vx_last = getVelocity().x;
		ax = G / 3;
		vMax = VMAX;
	}
	else if (_keyboard->KeyDown(DIK_LEFT))
	{
		//_m_Velocity.x = -MARIO_SPEED;
		//_vx_last = getVelocity().x;
		ax = -G / 3;
		vMax = VMAX;
	}
	else if (_keyboard->KeyPress(DIK_SPACE))
	{
		
	}
	else
	{
		ax = 0;
		ay = 0;
		_m_Velocity.x = 0;
		_m_Velocity.y = 0;
		_sprite->Reset();
	}
}
void Mario::CollisionTemp(BaseObject* obj, float t)
{
	//float normalx = 0;
	//float normaly = 0;
	//BaseObject *a = new BaseObject();
	//a->_m_Position.x = this->_m_Position.x;
	//a->_m_Position.y = this->_m_Position.y;
	//a->_width = this->_width;
	//a->_height = this->_height;
	//a->_m_Velocity.x = this->_m_Velocity.x * t;
	//a->_m_Velocity.y = this->_m_Velocity.y * t;
	//BaseObject *b = new BaseObject();
	//b->_m_Position.x = obj->_m_Position.x;
	//b->_m_Position.y = obj->_m_Position.y;
	//b->_width = obj->_width;
	//b->_height = obj->_height;
	//b->_m_Velocity.x = 0;
	//b->_m_Velocity.y = 0;
	//BaseObject* temp = GetSweptBroadphaseBox(a);
	//if (AABBCheck(temp, b))
	//{
	//	float collecsionTime = SweptAABB(a, b, normalx, normaly);
	//	if (collecsionTime < 1.0f && collecsionTime > 0)
	//	{
	//			GetCollisionWith(b,normalx, normaly);
	//	}
	//	//
	//	//	
	//	//if (AABB(this, obj) == RIGHT);
	//	////mario->m_Position.x = testBrick->m_Position.x + testBrick->_width+1;
	//	//if (AABB(this, obj) == TOP);
	//	//if (AABB(this, obj) == BOTTOM);
	//}
	DIR dir = checkCollision->isCollision(this, obj);
	
	if (dir == DIR::TOP || dir == DIR::BOTTOM)
		this->setVelocity(this->getVelocity().x, this->getVelocity().y * -1);
	else if (dir == DIR::LEFT || dir == DIR::RIGHT)
		this->setVelocity(this->getVelocity().x * -1, this->getVelocity().y);
		
//	this->set
}

void Mario::GetCollisionWith(BaseObject* b,float normalx,float normaly)
{

//		if (normalx == -1)
//		{
////			m_Position.x = obj->m_Position.x - this->_width;
//		}
//	
}
