// #버그 1
// 현재 버그 발생O 기종(갤럭시S5, LG G3 Cat6) !갤럭시 노트3, 갤럭시S4는 매우 심각, 터치하자마자 gg
// 버그 발생X 기종(갤럭시S3, 갤럭시A5, 갤럭시 노트2, LG G2)
//
// 스타트 후 곧 바로 총알이나 플레이어를 누르면
// Player가 사라지며 Result씬으로 넘어가는 버그가 있습니다.

// #버그 2
// 현재 버그 발생O 기종(갤럭시 노트2)
//
// 게임씬과 결과씬을 자주 왔다갔다 하다보면 팅김현상이 있습니다.

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
		bullet_print(); // 총알 생성 함수
		_time -= setTime - valanceTime; // 초기화
	}
	if (special_time >= 4)
	{
		Spe_bullet_print(); // 특수 총알 생성 함수
		special_time -= 4; // 초기화
	}
	if (P_time > checkTime)
	{
		valanceTime += 0.02;
		checkTime += 7;
	}
	
	// 총알, 플레이어 처리 함수
	bullet_pro();  
	Spe_bullet_pro();
	player_pro(dt);

	bg1->setPositionY(bg1->getPositionY() + 5);
	bg2->setPositionY(bg2->getPositionY() + 5);

	TIME->setString("Time: " + toString(P_time));
}
void HelloWorld::InitEvent()
{
	// 키 리스너
	EventListenerKeyboard *keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	// 터치 리스너
	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void HelloWorld::InitData()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM/Codeko - Crest.wav", true);

	userVec2 = Vec2::ZERO;

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	isOnlyOneTouch = true;

	player = Player::create();
	player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(player, 1);

	bg1 = Sprite::create("UI/bg1.png");
	bg2 = Sprite::create("UI/bg2.png");
	bg1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bg2->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
	this->addChild(bg1, 0);
	this->addChild(bg2, 0);

	bullets = new std::list<Bullet *>();
	Spe_bullets = new std::list<SpecialBullet *>();

	TIME = LabelTTF::create("", "Arial", 18);
	TIME->setColor(Color3B::WHITE);
	TIME->setPosition(visibleSize.width / 2, visibleSize.height - 15);
	this->addChild(TIME, 2);
}

void HelloWorld::fir_bulletprint() // 맨 처음 총알 생성 코드
{
	for (int i = 0, n = 10; i < 15; i++, n += 70) // ↑
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
	for (int i = 0, n = 10; i < 15; i++, n += 70) // ↓
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
	for (int i = 0, n = 50; i < 10; i++, n += 55) // ←
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
	for (int i = 0, n = 50; i < 10; i++, n += 55) // →
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
void HelloWorld::bullet_print() // 총알 생성코드
{
	Bullet *bullet = Bullet::create();
	switch (rand() % 4 + 1)
	{ /*화면 안 에 생성되지않게 */
	case 1: bullet->setPosition(rand() % 801, visibleSize.height + 5); break;   // ↑
	case 2: bullet->setPosition(visibleSize.width + 5, rand() % 601); break;   // →
	case 3: bullet->setPosition(-5, rand() % 601); break;                   // ←
	case 4: bullet->setPosition(rand() % 801, -5); break;                  // ↓
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
void HelloWorld::bullet_pro() // 총알 처리
{
	std::list<Bullet *>::iterator it;

	for (it = bullets->begin(); it != bullets->end(); it++)
	{
		if ((*it)->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			TransitionSlideInT * fade_scene =
				TransitionSlideInT::create(0.5f, ResultScene::createScene());
			
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			UserDefault::getInstance()->setFloatForKey("P_time", P_time);
			UserDefault::getInstance()->flush();

			Director::getInstance()->replaceScene(fade_scene); 
			this->unscheduleUpdate();

			CC_SAFE_DELETE(fade_scene);
		}

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
void HelloWorld::Spe_bullet_print() // 특수 총알 생성코드
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
void HelloWorld::Spe_bullet_pro() // 특수 총알 처리
{
	std::list<SpecialBullet *>::iterator it, jt;

	for (it = Spe_bullets->begin(); it != Spe_bullets->end(); it++)
	{
		if ((*it)->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			this->unscheduleUpdate();

			TransitionSlideInT * fade_scene =
				TransitionSlideInT::create(0.5f, ResultScene::createScene());
			
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

			UserDefault::getInstance()->setFloatForKey("P_time", P_time);
			UserDefault::getInstance()->flush();
			
			Director::getInstance()->replaceScene(fade_scene);
		}

		if (spe_follw_time >= 1)
		{
			location = player->getPosition();
			for (jt = Spe_bullets->begin(); jt != Spe_bullets->end(); jt++)
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

void HelloWorld::player_pro(float dt)
{
	// 배경 스크롤 이동 구문
	if (bg1->getPositionY() >= visibleSize.height + (visibleSize.height / 2))
	{
		bg1->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
	}
	if (bg2->getPositionY() >= visibleSize.height + (visibleSize.height / 2))
	{
		bg2->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
	}

	// 벽 충돌 구문
	if (
		(player->getPositionY() < visibleSize.height - player->getContentSize().height / 2) &&
		(player->getPositionX() > player->getContentSize().width / 2) &&
		(player->getPositionY() > player->getContentSize().height / 2) &&
		(player->getPositionX() < visibleSize.width - player->getContentSize().width / 2)
		)
	{
		player->setPosition(player->getPosition() + (SPEED * userVec2 * dt));
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

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	if (isOnlyOneTouch == true)
	{
		isOnlyOneTouch = false;

		pb = Sprite::create("UI/ParentButton.png");
		pb->setScale(0.6f);
		pb->setPosition(touch->getLocation());
		this->addChild(pb, 1);
	}
	//cb = Sprite::create("UI/ChildButton.png");
	//cb->setPosition(touch->getLocation());
	//this->addChild(cb, 1);

	return true;
}
void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
	// cb가 pb밖으로 나가지 않게 하는 구문
	//if ((sqrtf(pow((touch->getLocation().x - pb->getPositionX()), 2) +
	//	      pow((touch->getLocation().y - pb->getPositionY()), 2)) <= pb->getContentSize().width / 2))
	//{
	//	cb->setPosition(touch->getLocation());	
	//}
	userVec2.x = touch->getLocation().x - pb->getPositionX();
	userVec2.y = touch->getLocation().y - pb->getPositionY();
	userVec2 = getUnitVec2(userVec2);

}
void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	userVec2 = Vec2::ZERO;
	isOnlyOneTouch = true;

	this->removeChild(pb, true);
	//this->removeChild(cb, true);
}

std::string HelloWorld::toString(float value)
{
	std::ostringstream convStream;
	convStream << value;

	return convStream.str();
}