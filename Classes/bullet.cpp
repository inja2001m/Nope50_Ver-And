#include "bullet.h"

Bullet * Bullet::create()
{
	Bullet *pRet = new (std::nothrow)Bullet();
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

	m_Speed = RandomHelper::random_int(100, 200);

	this->scheduleUpdate();

	return true;
}

void Bullet::update(float dt)
{
	if (GameManager::GetInstance()->m_IsGameOver)
		this->unscheduleUpdate();

	this->setPosition(this->getPosition() + m_Direction.getNormalized() * m_Speed * dt);
}
