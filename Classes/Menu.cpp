#include "Menu.h"
//#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initData();
	this->scheduleUpdate();
	return true;
}

void MenuScene::initData()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM/Ahrix - Nova.wav", true);
	Title = Sprite::create("UI/Title.png");
	Sprite* Main = Sprite::create("UI/space01.png");
	MenuItemImage *Start = MenuItemImage::create("UI/bt_start.png", "UI/bt_start_on.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	MenuItemImage *Exit = MenuItemImage::create("UI/bt_exit.png", "UI/bt_exit_on.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	Start->setTag(1);
	Exit->setTag(2);

	Main->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	Title->setPosition(visibleSize.width / 2, visibleSize.height - 180);
	Start->setPosition(visibleSize.width / 2, visibleSize.height / 2.5);
	Exit->setPosition(visibleSize.width / 2, visibleSize.height / 4);

	Start->setScale(1.5f);
	Exit->setScale(1.5f);

	Menu *StartMenu = Menu::create(Start, NULL);
	Menu *ExitMenu = Menu::create(Exit, NULL);
	StartMenu->setPosition(Vec2::ZERO);
	ExitMenu->setPosition(Vec2::ZERO);

	this->addChild(Main, 1);
	this->addChild(Title, 2);
	this->addChild(StartMenu, 2);
	this->addChild(ExitMenu, 2);
}

void MenuScene::update(float dt)
{
	time += dt;
	if (time > 2)
	{
		sw *= -1;
		time = 0;
	}
	Title->setPositionY(Title->getPositionY() + 0.5 * sw);
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	MenuItemImage *node = dynamic_cast <MenuItemImage *>(pSender);

	TransitionSlideInB * fade_scene =
		TransitionSlideInB::create(0.3f, HelloWorld::createScene());

	switch (node->getTag())
	{
	case 1:
		Director::getInstance()->replaceScene(fade_scene);
		break;
	case 2:
		Director::getInstance()->end();
	}
}
