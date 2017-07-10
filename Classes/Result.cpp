#include "Result.h"

USING_NS_CC;

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
	initData();
	schedule(schedule_selector(ResultScene::update));

	return true;
}

void ResultScene::update(float dt) 
{
	touchWaitTime += dt;
	if (touchWaitTime > 2.f && isOnlyOneTouchLabel == false)
	{
		isOnlyOneTouchLabel = true;

		LabelTTF *touch = LabelTTF::create("- Touch to Screen -", "Arial", 28);
		touch->setColor(Color3B::GRAY);
		touch->setPosition(visibleSize.width / 2, 50);
		this->addChild(touch);
	}

	score->setString("Time : " + toString(this_Time));
	if (best_Time < this_Time)
	{
		this->initWithColor(Color4B::WHITE);
		UserDefault::getInstance()->setFloatForKey("best_time", this_Time);
	}
	UserDefault::getInstance()->flush();
	b_score->setString("Best Time : " + toString(best_Time));
}

void ResultScene::InitEvent()
{
	// 터치 리스너
	auto *listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
void ResultScene::initData()
{
	touchWaitTime = 0.f;
	isOnlyOneTouchLabel = false;

	LabelTTF *GAME_OVER = LabelTTF::create("GAME OVER", "Arial", 64);
	GAME_OVER->setColor(Color3B::GRAY);

	score = LabelTTF::create("Time: 0", "Arial", 32);
	score->setColor(Color3B::GRAY);

	b_score = LabelTTF::create("Best Time: 0", "Arial", 32);
	b_score->setColor(Color3B::GRAY);

	GAME_OVER->setPosition(visibleSize.width / 2, visibleSize.height / 1.2);
	score->setPosition(visibleSize.width / 2, visibleSize.height / 1.6);
	b_score->setPosition(visibleSize.width / 2, visibleSize.height / 1.4);

	this->addChild(GAME_OVER);
	this->addChild(score);
	this->addChild(b_score);
}

bool ResultScene::onTouchBegan(Touch *touch, Event *event)
{
	if (touchWaitTime > 2.f)
	{
		TransitionSlideInT * fade_scene =
			TransitionSlideInT::create(0.5f, HelloWorld::createScene());

		Director::getInstance()->replaceScene(fade_scene);
	}
	return true;
}

std::string ResultScene::toString(float value)
{
	std::ostringstream convStream;
	convStream << value;

	return convStream.str();
}