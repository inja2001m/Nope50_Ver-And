// #버그 1
// 현재 버그 발생O 기종(갤럭시S5, LG G3 Cat6) !갤럭시 노트3, 갤럭시S4는 매우 심각, 터치하자마자 gg
// 버그 발생X 기종(갤럭시S3, 갤럭시A5, 갤럭시 노트2, LG G2)
//
// 스타트 후 곧 바로 총알이나 플레이어를 누르면
// Player가 사라지며 Result씬으로 넘어가는 버그가 있습니다.

// #버그 2
// 현재 버그 발생O 기종(갤럭시 노트2)
//
// 게임씬과 결과씬을 자주 왔다갔다 하다보면 팅김 현상이 있습니다.

#include "GameScene.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();

    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	InitData();
	InitEvent();
	ShotFirstBullets();

	this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt)
{
	m_CurrentNormalBulletFireTime += dt; 
	m_CurrentSpecialBulletFireTime += dt;
	m_CurrentTime += dt;

	if (m_CurrentNormalBulletFireTime >= NORMAL_BULLET_FIRE_RATE_TIME - m_ValanceTime)
	{
		ShotNormalBullet();
		m_CurrentNormalBulletFireTime -= NORMAL_BULLET_FIRE_RATE_TIME - m_ValanceTime;
	}
	if (m_CurrentSpecialBulletFireTime >= SPECIAL_BULLET_FIRE_RATE_TIME)
	{
		ShotSpecialBullet();
		m_CurrentSpecialBulletFireTime -= SPECIAL_BULLET_FIRE_RATE_TIME;
	}
	if (m_CurrentTime >= m_ValanceTimeUpdateRate)
	{
		m_ValanceTime += 0.02f;
		m_ValanceTimeUpdateRate += m_ValanceTimeUpdateRate;
	}
	
	ProcessNormalBullets();  
	ProcessSpecialBullets();
	WallMovement(dt);

	m_Player->SetVelocity(m_UserVelocity * PLAYER_SPEED);

	m_TimeLabel->setString("Time: " + MyFunction::FloatToString(m_CurrentTime));
}
void GameScene::InitEvent()
{
	EventListenerTouchOneByOne *m_TouchListener = EventListenerTouchOneByOne::create();
	m_TouchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	m_TouchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	m_TouchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_TouchListener, this);
}
void GameScene::InitData()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM/Codeko - Crest.wav", true);

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	m_Joypad = JoyPad::create("UI/ParentButton.png", "UI/ChildButton.png", this);

	m_Player = Player::create();
	m_Player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(m_Player, 1);

	m_Bg1 = Sprite::create("UI/bg1.png");
	m_Bg1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(m_Bg1, 0);
	m_Bg2 = Sprite::create("UI/bg2.png");
	m_Bg2->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
	this->addChild(m_Bg2, 0);

	m_TimeLabel = LabelTTF::create("", "Arial", 18);
	m_TimeLabel->setColor(Color3B::WHITE);
	m_TimeLabel->setPosition(visibleSize.width / 2, visibleSize.height - 15);
	this->addChild(m_TimeLabel, 2);

	m_UserVelocity = Vec2::ZERO;
	m_CurrentNormalBulletFireTime = 0;
	m_CurrentSpecialBulletFireTime = 0;
	m_CurrentTime = 0;
	m_ValanceTimeUpdateRate = 7;
	m_ValanceTime = 0;
}

void GameScene::ShotFirstBullets()
{
	Bullet *bullet;
	Point playerPosition = m_Player->getPosition();
	const int nCount = 16;

	for (int i = 0; i <= nCount; ++i)
	{
		float posRate = (float)i / nCount;

		// Generate in top
		bullet = Bullet::create();
		bullet->setPosition(visibleSize.width * posRate, visibleSize.height + PADDING);
		bullet->SetBulletDirection(playerPosition - bullet->getPosition());
		this->addChild(bullet);
		m_NormalBulletsList.push_back(bullet);
	
		// Generate in left
		bullet = Bullet::create();
		bullet->setPosition(-PADDING, visibleSize.height * posRate);
		bullet->SetBulletDirection(playerPosition - bullet->getPosition());
		this->addChild(bullet);
		m_NormalBulletsList.push_back(bullet);

		// Generate in right
		bullet = Bullet::create();
		bullet->setPosition(visibleSize.width + PADDING, visibleSize.height * posRate);
		bullet->SetBulletDirection(playerPosition - bullet->getPosition());
		this->addChild(bullet);
		m_NormalBulletsList.push_back(bullet);

		// Generate in bottom
		bullet = Bullet::create();
		bullet->setPosition(visibleSize.width * posRate, -PADDING);
		bullet->SetBulletDirection(playerPosition - bullet->getPosition());
		this->addChild(bullet);
		m_NormalBulletsList.push_back(bullet);
	}
}
void GameScene::ShotNormalBullet() 
{
	Bullet *bullet = Bullet::create();
	Point playerPosition = m_Player->getPosition();
	
	switch (RandomHelper::random_int(1, 4))
	{ /* 화면 안에 생성되지않게 */
		// Generate in top
	case 1: bullet->setPosition(RandomHelper::random_int(0, (int)visibleSize.width), 
		visibleSize.height + 5);	
		break;		

		// Generate in right
	case 2: bullet->setPosition(visibleSize.width + 5, 
		RandomHelper::random_int(0, (int)visibleSize.height));	
		break;		

		// Generate in left
	case 3: bullet->setPosition(-5, 
		RandomHelper::random_int(0, (int)visibleSize.height));						
		break;		

		// Generate in bottom
	case 4: bullet->setPosition(RandomHelper::random_int(0, (int)visibleSize.width), 
		-5);						
		break;		
	}
	bullet->SetBulletDirection(playerPosition - bullet->getPosition());
	this->addChild(bullet, 1);
	m_NormalBulletsList.push_back(bullet);
}
void GameScene::ProcessNormalBullets()
{
	std::list<Bullet *>::iterator it;
	const Rect playerRect = m_Player->getBoundingBox();

	for (it = m_NormalBulletsList.begin(); it != m_NormalBulletsList.end(); ++it)
	{
		if ((*it)->getBoundingBox().intersectsRect(playerRect))
			CollisionBullet();

		if (((*it)->getPositionX() < -PADDING					||
			(*it)->getPositionX() > visibleSize.width + PADDING	||
			(*it)->getPositionY() < -PADDING					||
			(*it)->getPositionY() > visibleSize.height + PADDING
			))
		{
			(*it)->removeFromParentAndCleanup(true);
			m_NormalBulletsList.erase(it);

			if (!m_NormalBulletsList.empty())
				it = m_NormalBulletsList.begin();
			else
				break;
		}
	}
}

void GameScene::ShotSpecialBullet()
{
	SpecialBullet *bullet = SpecialBullet::create();
	Point playerPosition = m_Player->getPosition();;

	switch (RandomHelper::random_int(1, 4))
	{ /* 화면 안에 생성되지않게 */
		// Generate in top
	case 1: bullet->setPosition(RandomHelper::random_int(0, (int)visibleSize.width), 
		visibleSize.height + 5);	
		break;		

		// Generate in right
	case 2: bullet->setPosition(visibleSize.width + 5, 
		RandomHelper::random_int(0, (int)visibleSize.height));	
		break;		

		// Generate in left
	case 3: bullet->setPosition(-5, 
		RandomHelper::random_int(0, (int)visibleSize.height));						
		break;		

		// Generate in bottom
	case 4: bullet->setPosition(RandomHelper::random_int(0, (int)visibleSize.width), 
		-5);						
		break;		
	}
	bullet->SetBulletDirection(playerPosition - bullet->getPosition());
	this->addChild(bullet, 1);
	m_SpecialBulletsList.push_back(bullet);
}
void GameScene::ProcessSpecialBullets()
{
	std::list<SpecialBullet *>::iterator it;
	Point playerPosition = m_Player->getPosition();
	const Rect playerRect = m_Player->getBoundingBox();

	for (it = m_SpecialBulletsList.begin(); it != m_SpecialBulletsList.end(); ++it)
	{
		if ((*it)->getBoundingBox().intersectsRect(playerRect))
			CollisionBullet();

		if ((*it)->GetIsDirChangeEnabled())
		{
			(*it)->SetBulletDirection(playerPosition - (*it)->getPosition());
			(*it)->SetIsDirChangeEnabled(false);
		}

		if (((*it)->getPositionX() < -PADDING					||
			(*it)->getPositionX() > visibleSize.width + PADDING	||
			(*it)->getPositionY() < -PADDING					||
			(*it)->getPositionY() > visibleSize.height + PADDING
			))
		{
			(*it)->removeFromParentAndCleanup(true);
			m_SpecialBulletsList.erase(it);
			if (!m_SpecialBulletsList.empty())
				it = m_SpecialBulletsList.begin();
			else
				break;
		}
	}
}

void GameScene::WallMovement(float dt)
{
	m_Bg1->setPositionY(m_Bg1->getPositionY() + 5);
	m_Bg2->setPositionY(m_Bg2->getPositionY() + 5);

	if (m_Bg1->getPositionY() >= visibleSize.height + (visibleSize.height / 2))
		m_Bg1->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
	if (m_Bg2->getPositionY() >= visibleSize.height + (visibleSize.height / 2))
		m_Bg2->setPosition(visibleSize.width / 2, -visibleSize.height / 2);
}

void GameScene::CollisionBullet()
{
	GameManager::GetInstance()->m_IsGameOver = true;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	
	this->unscheduleUpdate();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ResultScene::createScene()));
	UserDefault::getInstance()->setFloatForKey("CurrentTime", m_CurrentTime);
	UserDefault::getInstance()->flush();
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	m_Joypad->DoTouchBegan(touch->getLocation());
	return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	m_Joypad->DoTouchMoved(touch->getLocation(), m_UserVelocity);
}
void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	m_UserVelocity = Vec2::ZERO;
	m_Joypad->DoTouchEnded();
}