#include "ResultScene.h"

Scene* ResultScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ResultScene::create();

	scene->addChild(layer);

	return scene;
}

bool ResultScene::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}
	
	InitEvent();
	InitData();

	this->scheduleUpdate();

	return true;
}

void ResultScene::update(float dt) 
{
	m_TouchWaitTime += dt;
	if (m_TouchWaitTime >= 2.0f && m_IsOnlyOneTouchLabel == false)
	{
		m_IsOnlyOneTouchLabel = true;

		m_TouchLabel = LabelTTF::create("- Touch to Screen -", "Arial", 28);
		m_TouchLabel->setColor(Color3B::GRAY);
		m_TouchLabel->setPosition(visibleSize.width / 2, 50);
		this->addChild(m_TouchLabel);
	}

	if (BEST_TIME < CURRENT_TIME)
	{
		this->initWithColor(Color4B::WHITE);
		UserDefault::getInstance()->setFloatForKey("BestTime", CURRENT_TIME);
		UserDefault::getInstance()->flush();
	}

	m_Time->setString("Time : " + MyFunction::FloatToString(CURRENT_TIME));
	m_BestTime->setString("Best Time : " + MyFunction::FloatToString(BEST_TIME));
}

void ResultScene::InitEvent()
{
	EventListenerTouchOneByOne *m_TouchListener = EventListenerTouchOneByOne::create();
	m_TouchListener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_TouchListener, this);
}
void ResultScene::InitData()
{
	m_TouchWaitTime = 0.0f;
	m_IsOnlyOneTouchLabel = false;

	m_GameOverLabel = LabelTTF::create("GAME OVER", "Arial", 64);
	m_GameOverLabel->setColor(Color3B::GRAY);

	m_Time = LabelTTF::create("Time: 0", "Arial", 32);
	m_Time->setColor(Color3B::GRAY);

	m_BestTime = LabelTTF::create("Best Time: 0", "Arial", 32);
	m_BestTime->setColor(Color3B::GRAY);

	m_GameOverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 1.2);
	m_Time->setPosition(visibleSize.width / 2, visibleSize.height / 1.6);
	m_BestTime->setPosition(visibleSize.width / 2, visibleSize.height / 1.4);

	this->addChild(m_GameOverLabel);
	this->addChild(m_Time);
	this->addChild(m_BestTime);
}

bool ResultScene::onTouchBegan(Touch *touch, Event *event)
{
	if (!(m_TouchWaitTime >= 2.0f))
		return true;

	this->unscheduleUpdate();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::createScene()));
	GameManager::GetInstance()->m_IsGameOver = false;
	
	return true;
}