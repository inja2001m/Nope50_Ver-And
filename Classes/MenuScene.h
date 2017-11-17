#pragma once

#include "cocos2d.h"
#include "GameScene.h"

#define visibleSize Director::getInstance()->getVisibleSize()

USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

private:
	virtual bool init();
	void update(float dt);

private:
	void InitData();
	
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	CREATE_FUNC(MenuScene);

private:
	Sprite *m_Title;
	Sprite *m_Main;

	MenuItemImage *m_Start;
	MenuItemImage *m_Exit;

	Menu *m_StartMenu;
	Menu *m_ExitMenu;

private:
	float _time;
	float _toggle;
};


