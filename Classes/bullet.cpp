#include "bullet.h"

Bullet::Bullet()
{

}
Bullet::~Bullet()
{

}

Bullet* Bullet::create()
{
	Bullet *pRet = new Bullet();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
}
bool Bullet::init()
{
	Sprite::initWithFile("OBJ/bullet.png");
	Speed = rand() % 2 + 2;
	this->scheduleUpdate();

	return true;
}

void Bullet::update(float dt)
{
	this->setPosition(
		getPosition().x + cosf(direction) * Speed,
		getPosition().y + sinf(direction) * Speed);
}
