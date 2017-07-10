#pragma once

#define visibleSize Director::getInstance()->getVisibleSize()
#define this_Time  UserDefault::getInstance()->getFloatForKey("P_time", 0)
#define best_Time UserDefault::getInstance()->getFloatForKey("best_time", 0)

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class ResultScene : public cocos2d::LayerColor
{
private:
	LabelTTF *score, *b_score;
	float touchWaitTime;
	bool isOnlyOneTouchLabel;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

public:
	virtual bool onTouchBegan(Touch *touch, Event *event);

public:
	void initData(), InitEvent();
	void update(float dt);
	std::string toString(float value);

	CREATE_FUNC(ResultScene);
};


