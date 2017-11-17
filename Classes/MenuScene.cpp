#include "MenuScene.h"

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

	InitData();
	this->scheduleUpdate();

	return true;
}

void MenuScene::InitData()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM/Ahrix - Nova.wav", true);
	
	m_Title = Sprite::create("UI/Title.png");
	m_Title->setPosition(visibleSize.width / 2, visibleSize.height - 180);
	this->addChild(m_Title, 2);

	m_Main = Sprite::create("UI/space01.png");
	m_Main->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(m_Main, 1);
	
	m_Start = MenuItemImage::create("UI/bt_start.png", "UI/bt_start_on.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	m_Start->setPosition(visibleSize.width / 2, visibleSize.height / 2.5);
	m_Start->setTag(1);
	m_Start->setScale(1.5f);

	m_Exit = MenuItemImage::create("UI/bt_exit.png", "UI/bt_exit_on.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	m_Exit->setPosition(visibleSize.width / 2, visibleSize.height / 4);
	m_Exit->setTag(2);
	m_Exit->setScale(1.5f);

	m_StartMenu = Menu::create(m_Start, NULL);
	m_StartMenu->setPosition(Vec2::ZERO);
	this->addChild(m_StartMenu, 2);

	m_ExitMenu = Menu::create(m_Exit, NULL);
	m_ExitMenu->setPosition(Vec2::ZERO);
	this->addChild(m_ExitMenu, 2);

	_time = 0.0f;
	_toggle = 1.0f;
}

void MenuScene::update(float dt)
{
	_time += dt;
	if (_time >= 2.0f)
	{
		_toggle *= -1.0f;
		_time -= 2.0f;
	}
	m_Title->setPositionY(m_Title->getPositionY() + 0.5f * _toggle);
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	MenuItemImage *node = dynamic_cast <MenuItemImage *>(pSender);

	switch (node->getTag())
	{
	case 1:
		this->unscheduleUpdate();
		Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::createScene()));
		break;
	case 2:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}