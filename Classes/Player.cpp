#include "Player.h"

Player * Player::create()
{
	Player *pRet = new (std::nothrow)Player();
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

bool Player::init()
{
	Sprite::initWithFile("OBJ/Player.png");

	this->scheduleUpdate();

	return true;
}

void Player::update(float dt)
{
	if (GameManager::GetInstance()->m_IsGameOver)
		this->unscheduleUpdate();

	Movement(dt);
}

void Player::Movement(const float dt)
{
	if ((this->getPositionY() < visibleSize.height - this->getContentSize().height / 2) &&
		(this->getPositionX() > this->getContentSize().width / 2) &&
		(this->getPositionY() > this->getContentSize().height / 2) &&
		(this->getPositionX() < visibleSize.width - this->getContentSize().width / 2))
	{
		this->setPosition(this->getPosition() + m_Veloticy * dt);
	}
	else
	{
		if (this->getPositionY() > visibleSize.height - this->getContentSize().height / 2)
			this->setPositionY((visibleSize.height - this->getContentSize().height / 2) - 1);

		if (this->getPositionY() < this->getContentSize().height / 2)
			this->setPositionY((this->getContentSize().height / 2) + 1);

		if (this->getPositionX() < this->getContentSize().width / 2)
			this->setPositionX((this->getContentSize().width / 2) + 1);

		if (this->getPositionX() > visibleSize.width - this->getContentSize().width / 2)
			this->setPositionX((visibleSize.width - this->getContentSize().width / 2) - 1);
	}
}