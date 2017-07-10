#pragma once

#define visibleSize Director::getInstance()->getVisibleSize()
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	Sprite * Title;
	float time = 0, sw = 1;
	virtual bool init();
	void initData();
	void update(float dt);
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MenuScene);
};


