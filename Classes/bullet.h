#pragma once

#include <random>

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class Bullet : public cocos2d::Sprite
{
public:
	static Bullet* create();

private:
	virtual bool init();

	void update(float dt);

public:
	void SetBulletDirection(Vec2 _direction) { this->m_Direction = _direction; }

private:
	Vec2 m_Direction;
	int m_Speed;
};