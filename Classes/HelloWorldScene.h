#pragma once

#define visibleSize Director::getInstance()->getVisibleSize()
#define SPEED 250.f
#define PI 3.141592
#define setTime 0.18

#include "cocos2d.h"
#include "Player.h"
#include "bullet.h"
#include "Special_bullet.h"
#include "Result.h"
#include "Vector"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
	std::list<Bullet *> *bullets;
	std::list<SpecialBullet *> *Spe_bullets;

private:
	Point location;
	Vec2 userVec2;
	Player *player;
	Sprite *bg1, *bg2, *pb;
	//Sprite *cb;
	LabelTTF *TIME;
	bool isOnlyOneTouch;
	float _time = 0, special_time = 0, spe_follw_time = 0;
	float P_time = 0, checkTime = 7, valanceTime = 0;

public:	
    static cocos2d::Scene* createScene();
    virtual bool init();

public:
	void update(float dt);
	void InitData(), InitEvent();
	void fir_bulletprint(), bullet_print(), bullet_pro();
	void Spe_bullet_print(), Spe_bullet_pro();
	void player_pro(float dt);

public:
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

public:
	Vec2 getUnitVec2(Vec2 vec)
	{
		Vec2 temp;
		float size;

		size = sqrt(vec.x * vec.x + vec.y * vec.y);

		temp.x = vec.x / size;
		temp.y = vec.y / size;

		return temp;
	}
	std::string toString(float value);

    CREATE_FUNC(HelloWorld);
};

