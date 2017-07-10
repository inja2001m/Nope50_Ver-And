#include "Player.h"

Player* Player::create()
{
	Player *pRet = new Player();
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

	return true;
}