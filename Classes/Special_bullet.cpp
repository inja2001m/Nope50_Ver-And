#include "Special_bullet.h"

SpecialBullet::SpecialBullet()
{

}
SpecialBullet::~SpecialBullet()
{

}

SpecialBullet* SpecialBullet::create()
{
	SpecialBullet *pRet = new SpecialBullet();
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
bool SpecialBullet::init()
{
	Sprite::initWithFile("OBJ/SpecialBullet.png");
	Speed = 3;
	this->scheduleUpdate();

	return true;
}

void SpecialBullet::update(float dt)
{
	this->setPosition(
		getPosition().x + cosf(direction) * Speed,
		getPosition().y + sinf(direction) * Speed);
}
