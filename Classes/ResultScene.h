#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "GameManager.h"

#define visibleSize Director::getInstance()->getVisibleSize()
#define CURRENT_TIME  UserDefault::getInstance()->getFloatForKey("CurrentTime", 0)
#define BEST_TIME UserDefault::getInstance()->getFloatForKey("BestTime", 0)

USING_NS_CC;

class ResultScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

private:
	virtual bool init();
	void update(float dt);

private:
	void InitData();
	void InitEvent();

private:
	virtual bool onTouchBegan(Touch *touch, Event *event);

private:
	CREATE_FUNC(ResultScene);

private:
	LabelTTF *m_Time;
	LabelTTF *m_BestTime;
	LabelTTF *m_GameOverLabel;
	LabelTTF *m_TouchLabel;
	
	float m_TouchWaitTime;
	bool m_IsOnlyOneTouchLabel;
};