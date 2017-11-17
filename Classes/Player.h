#pragma once

#include "cocos2d.h"
#include "GameManager.h"

#define visibleSize Director::getInstance()->getVisibleSize()

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
	static Player* create();

private:
	virtual bool init();
	void update(float dt);

private:
	void Movement(const float dt);

public:
	void SetVelocity(Vec2 _velocity) { this->m_Veloticy = _velocity; }

private: 
	Vec2 m_Veloticy;
};