#pragma once
#include "cocos2d.h"
#define PI 3.141592
USING_NS_CC;

class Bullet : public cocos2d::Sprite
{
public:
	Bullet();
	virtual ~Bullet();
	
	static Bullet* create();
	virtual bool init();
	float direction;
	void update(float dt);
	int Speed;
};