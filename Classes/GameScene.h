#pragma once

#include <random>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ResultScene.h"
#include "Player.h"
#include "bullet.h"
#include "Special_bullet.h"
#include "JoyPad.h"
#include "GameManager.h"
#include "My_Utils.h"

#define visibleSize Director::getInstance()->getVisibleSize()
#define PLAYER_SPEED 3.0f
#define NORMAL_BULLET_FIRE_RATE_TIME 0.18f
#define SPECIAL_BULLET_FIRE_RATE_TIME 4.0f
#define PADDING 15.0f

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

private:
	void update(float dt);
	void InitData();
	void InitEvent();

private:
	void ShotFirstBullets();
	void ShotNormalBullet();
	void ProcessNormalBullets();
	void ShotSpecialBullet();
	void ProcessSpecialBullets();
	void CollisionBullet();

private:
	void WallMovement(float dt);

private:
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

public:
	CREATE_FUNC(GameScene);

private:
	std::list<Bullet *> m_NormalBulletsList;
	std::list<SpecialBullet *> m_SpecialBulletsList;

private:
	Vec2 m_UserVelocity;
	Player *m_Player;
	Sprite *m_Bg1, *m_Bg2;
	JoyPad *m_Joypad;
	LabelTTF *m_TimeLabel;

private:
	float m_CurrentNormalBulletFireTime;
	float m_CurrentSpecialBulletFireTime;
	float m_CurrentTime;
	float m_ValanceTimeUpdateRate;
	float m_ValanceTime;
};

