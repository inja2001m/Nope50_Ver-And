#pragma once
#include "cocos2d.h"
#define PI 3.141592
USING_NS_CC;

class SpecialBullet : public cocos2d::Sprite
{
public:
	SpecialBullet();
	virtual ~SpecialBullet();

	static SpecialBullet* create();
	virtual bool init();
	float direction;
	void update(float dt);
	int Speed;
};