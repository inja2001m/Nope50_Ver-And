#pragma once

#define visibleSize Director::getInstance()->getVisibleSize()
#define SPEED 3.f
#define PI 3.141592
#define setTime 0.18

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Result.h"
#include "Player.h"
#include "bullet.h"
#include "Special_bullet.h"
#include "JoyPad.h"

#include "My_Defines.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

public:
	void update(float dt);
	void InitData(), InitEvent();

public:
	void fir_bulletprint();
	void bullet_print(), bullet_pro();
	void Spe_bullet_print(), Spe_bullet_pro();
	void playerAndWall_pro(float dt);

	void SafeDeletePointers();

public:
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

public:
	CREATE_FUNC(HelloWorld);

private:
	std::list<Bullet *> *bullets;
	std::list<SpecialBullet *> *Spe_bullets;

private:
	Point location;
	Vec2 userVelocity;

	Player *player;
	Sprite *bg1, *bg2;

	JoyPad m_joypad;

	LabelTTF *timeLabel;

private:
	float _time = 0, special_time = 0, spe_follw_time = 0;
	float P_time = 0, checkTime = 7, valanceTime = 0;

	bool isGameOver;
};

