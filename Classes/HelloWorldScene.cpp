// #���� 1
// ���� ���� �߻�O ����(������S5, LG G3 Cat6) !������ ��Ʈ3, ������S4�� �ſ� �ɰ�, ��ġ���ڸ��� gg
// ���� �߻�X ����(������S3, ������A5, ������ ��Ʈ2, LG G2)
//
// ��ŸƮ �� �� �ٷ� �Ѿ��̳� �÷��̾ ������
// Player�� ������� Result������ �Ѿ�� ���װ� �ֽ��ϴ�.

// #���� 2
// ���� ���� �߻�O ����(������ ��Ʈ2)
//
// ���Ӿ��� ������� ���� �Դٰ��� �ϴٺ��� �ñ� ������ �ֽ��ϴ�.

#include "HelloWorldScene.h"

USING_NS_CC;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	InitData();
	InitEvent();
	fir_bulletprint();

	this->scheduleUpdate();
    return true;
}

void HelloWorld::update(float dt)
{
	_time += dt; special_time += dt; spe_follw_time += dt; P_time += dt;

	if (_time >= setTime - valanceTime)
	{
		bullet_print(); // �Ѿ� ���� �Լ�
		_time -= setTime - valanceTime; // �ʱ�ȭ
	}
	if (special_time >= 4)
	{
		Spe_bullet_print(); // Ư�� �Ѿ� ���� �Լ�
		special_time -= 4; // �ʱ�ȭ
	}
	if (P_time > checkTime)
	{
		valanceTime += 0.02;
		checkTime += 7;
	}
	
	// �Ѿ�, �÷��̾� ó�� �Լ�
	bullet_pro();  
	Spe_bullet_pro();
	playerAndWall_pro(dt);

	if (isGameOver)
		return;

	bg1->setPositionY(bg1->getPositionY() + 5);
	bg2->setPositionY(bg2->getPositionY() + 5);
	timeLabel->setString("Time: " + MyFunction::toString(P_time));
}
void HelloWorld::InitEvent()
{
	// Ű ������
	EventListenerKeyboard *keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	// ��ġ ������
	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void HelloWorld::InitData()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM/Codeko - Crest.wav", true);

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	userVelocity = Vec2::ZERO;
	isGameOver = false;
	bullets = new std::list<Bullet *>();
	Spe_bullets = new std::list<SpecialBullet *>();

	m_joypad.Init("UI/ParentButton.png", "UI/ChildButton.png", this);

	player = Player::create();
	player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(player, 1);

	bg1 = Sprite::create("UI/bg1.png");
	bg1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg1, 0);
	bg2 = Sprite::create("UI/bg2.png");
	bg2->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
	this->addChild(bg2, 0);

	timeLabel = LabelTTF::create("", "Arial", 18);
	timeLabel->setColor(Color3B::WHITE);
	timeLabel->setPosition(visibleSize.width / 2, visibleSize.height - 15);
	this->addChild(timeLabel, 2);
}

void HelloWorld::fir_bulletprint() // �� ó�� �Ѿ� ���� �ڵ�
{
	for (int i = 0, n = 10; i < 15; ++i, n += 70) // ��
	{
		Bullet *bullet = Bullet::create();
		bullet->setPosition(n, visibleSize.height - 5);
		location = player->getPosition();
		float direction = atan2f(
			location.x - bullet->getPosition().x,
			bullet->getPosition().y - location.y
			) - PI / 2;
		bullet->direction = direction;
		this->addChild(bullet);
		bullets->push_back(bullet);
	}
	for (int i = 0, n = 10; i < 15; ++i, n += 70) // ��
	{
		Bullet *bullet = Bullet::create();
		bullet->setPosition(n, 5);
		location = player->getPosition();
		float direction = atan2f(
			location.x - bullet->getPosition().x,
			bullet->getPosition().y - location.y
			) - PI / 2;
		bullet->direction = direction;
		this->addChild(bullet);
		bullets->push_back(bullet);
	}
	for (int i = 0, n = 50; i < 10; ++i, n += 55) // ��
	{
		Bullet *bullet = Bullet::create();
		bullet->setPosition(5, visibleSize.height - n);
		location = player->getPosition();
		float direction = atan2f(
			location.x - bullet->getPosition().x,
			bullet->getPosition().y - location.y
			) - PI / 2;
		bullet->direction = direction;
		this->addChild(bullet);
		bullets->push_back(bullet);
	}
	for (int i = 0, n = 50; i < 10; ++i, n += 55) // ��
	{
		Bullet *bullet = Bullet::create();
		bullet->setPosition(visibleSize.width - 5, visibleSize.height - n);
		location = player->getPosition();
		float direction = atan2f(
			location.x - bullet->getPosition().x,
			bullet->getPosition().y - location.y
			) - PI / 2;
		bullet->direction = direction;
		this->addChild(bullet);
		bullets->push_back(bullet);
	}
}
void HelloWorld::bullet_print() // �Ѿ� �����ڵ�
{
	Bullet *bullet = Bullet::create();
	switch (rand() % 4 + 1)
	{ /* ȭ�� �� �� ���������ʰ� */
	case 1: bullet->setPosition(rand() % 801, visibleSize.height + 5); break;   // ��
	case 2: bullet->setPosition(visibleSize.width + 5, rand() % 601); break;	// ��
	case 3: bullet->setPosition(-5, rand() % 601); break;						// ��
	case 4: bullet->setPosition(rand() % 801, -5); break;						// ��
	}
	location = player->getPosition();
	float direction = atan2f(
		location.x - bullet->getPosition().x,
		bullet->getPosition().y - location.y
		) - PI / 2;
	bullet->direction = direction;
	this->addChild(bullet, 1);
	bullets->push_back(bullet);
}
void HelloWorld::bullet_pro() // �Ѿ� ó��
{
	std::list<Bullet *>::iterator it;

	if (isGameOver)
		return;

	for (it = bullets->begin(); it != bullets->end(); ++it)
	{
		if ((*it)->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			SafeDeletePointers();
			this->unscheduleUpdate();

			TransitionSlideInT * fade_scene =
				TransitionSlideInT::create(0.5f, ResultScene::createScene());
			
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			UserDefault::getInstance()->setFloatForKey("P_time", P_time);
			UserDefault::getInstance()->flush();

			Director::getInstance()->replaceScene(fade_scene);

		}
		if (isGameOver)
			break; 

		if (!bullets->empty() && 
			((*it)->getPositionX() < -5 ||
			(*it)->getPositionX() > visibleSize.width + 5 ||
			(*it)->getPositionY() < -5 ||
			(*it)->getPositionY() > visibleSize.height + 5))
		{
			(*it)->removeFromParentAndCleanup(true);
			bullets->erase(it);
			if (!bullets->empty())
				it = bullets->begin();
		}
	}
}
void HelloWorld::Spe_bullet_print() // Ư�� �Ѿ� �����ڵ�
{
	SpecialBullet *SBullet = SpecialBullet::create();

	switch (rand() % 4 + 1)
	{
	case 1: SBullet->setPosition(rand() % 801, visibleSize.height + 5); break;   
	case 2: SBullet->setPosition(visibleSize.width + 5, rand() % 601); break;   
	case 3: SBullet->setPosition(-5, rand() % 601); break;                   
	case 4: SBullet->setPosition(rand() % 801, -5); break;                  
	}
	location = player->getPosition();
	float direction = atan2f(
		location.x - SBullet->getPosition().x,
		SBullet->getPosition().y - location.y
		) - PI / 2;
	SBullet->direction = direction;
	this->addChild(SBullet, 1);
	Spe_bullets->push_back(SBullet);
}
void HelloWorld::Spe_bullet_pro() // Ư�� �Ѿ� ó��
{
	std::list<SpecialBullet *>::iterator it, jt;

	if (isGameOver)
		return;

	for (it = Spe_bullets->begin(); it != Spe_bullets->end(); ++it)
	{
		if ((*it)->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			SafeDeletePointers();
			this->unscheduleUpdate();

			TransitionSlideInT * fade_scene =
				TransitionSlideInT::create(0.5f, ResultScene::createScene());
			
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

			UserDefault::getInstance()->setFloatForKey("P_time", P_time);
			UserDefault::getInstance()->flush();
			
			Director::getInstance()->replaceScene(fade_scene);
		}

		if (isGameOver)
			break;

		if (spe_follw_time >= 1)
		{
			location = player->getPosition();
			for (jt = Spe_bullets->begin(); jt != Spe_bullets->end(); ++jt)
			{
				float direction = atan2f(
					location.x - (*jt)->getPosition().x,
					(*jt)->getPosition().y - location.y
					) - PI / 2;
				(*jt)->direction = direction;
			}
			spe_follw_time -= 1;
		}
		if (!Spe_bullets->empty() && 
			((*it)->getPositionX() < -5 ||
			(*it)->getPositionX() > visibleSize.width + 5 ||
			(*it)->getPositionY() < -5 ||
			(*it)->getPositionY() > visibleSize.height + 5))
		{
			(*it)->removeFromParentAndCleanup(true);
			Spe_bullets->erase(it);
			if (!Spe_bullets->empty())
				it = Spe_bullets->begin();
			else
				break;
		}
	}
}

void HelloWorld::playerAndWall_pro(float dt)
{
	if (isGameOver)
		return;
	
	// ��� ��ũ�� �̵� ����
	if (bg1->getPositionY() >= visibleSize.height + (visibleSize.height / 2))
		bg1->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
	if (bg2->getPositionY() >= visibleSize.height + (visibleSize.height / 2))
		bg2->setPosition(visibleSize.width / 2, -visibleSize.height / 2);

	// �� �浹 ����
	if (
		(player->getPositionY() < visibleSize.height - player->getContentSize().height / 2) &&
		(player->getPositionX() > player->getContentSize().width / 2) &&
		(player->getPositionY() > player->getContentSize().height / 2) &&
		(player->getPositionX() < visibleSize.width - player->getContentSize().width / 2))
	{
		player->setPosition(player->getPosition() + (SPEED * userVelocity * dt));
	}
	else
	{
		if (player->getPositionY() > visibleSize.height - player->getContentSize().height / 2)
			player->setPositionY((visibleSize.height - player->getContentSize().height / 2) - 1);

		if (player->getPositionY() < player->getContentSize().height / 2)
			player->setPositionY((player->getContentSize().height / 2) + 1);

		if (player->getPositionX() < player->getContentSize().width / 2)
			player->setPositionX((player->getContentSize().width / 2) + 1);

		if (player->getPositionX() > visibleSize.width - player->getContentSize().width / 2)
			player->setPositionX((visibleSize.width - player->getContentSize().width / 2) - 1);
	}
}

void HelloWorld::SafeDeletePointers()
{
	isGameOver = true;
	bullets->clear();
	Spe_bullets->clear();
	player->removeFromParentAndCleanup(true);
	bg2->removeFromParentAndCleanup(true);
	bg1->removeFromParentAndCleanup(true);
	timeLabel->removeFromParentAndCleanup(true);
	m_joypad.release();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	m_joypad.DoTouchBegan(touch->getLocation());
	return true;
}
void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
	m_joypad.DoTouchMoved(touch->getLocation(), userVelocity);
}
void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	userVelocity = Vec2::ZERO;
	m_joypad.DoTouchEnded();
}