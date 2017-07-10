#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
	static Player* create();
	virtual bool init();
};