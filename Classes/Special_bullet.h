#pragma once

#include <random>

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class SpecialBullet : public cocos2d::Sprite
{
public:
	static SpecialBullet* create();

private:
	virtual bool init();
	void update(float dt);

public:
	void SetBulletDirection(Vec2 _direction) { this->m_Direction = _direction; }
	void SetIsDirChangeEnabled(bool _isBool) { this->IsDirChangeEnabled = _isBool; }
	bool GetIsDirChangeEnabled() { return this->IsDirChangeEnabled; }

private:
	Vec2 m_Direction;
	int m_Speed;
	float m_ChangeDirectionRate;

	bool IsDirChangeEnabled;
	float m_CurrentChangeDirectionTime;
};