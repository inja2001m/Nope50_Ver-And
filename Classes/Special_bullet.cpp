#include "Special_bullet.h"

SpecialBullet * SpecialBullet::create()
{
	SpecialBullet *pRet = new (std::nothrow)SpecialBullet();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
}
bool SpecialBullet::init()
{
	Sprite::initWithFile("OBJ/SpecialBullet.png");

	m_ChangeDirectionRate = RandomHelper::random_int(50, 200) * 0.01f;
	m_Speed = RandomHelper::random_int(150, 300);
	m_CurrentChangeDirectionTime = 0.0f;
	IsDirChangeEnabled = false;

	this->scheduleUpdate();

	return true;
}

void SpecialBullet::update(float dt)
{
	if (GameManager::GetInstance()->m_IsGameOver)
		this->unscheduleUpdate();

	m_CurrentChangeDirectionTime += dt;
	if (m_CurrentChangeDirectionTime >= m_ChangeDirectionRate)
	{
		IsDirChangeEnabled = true;
		m_CurrentChangeDirectionTime -= m_ChangeDirectionRate;
	}

	this->setPosition(this->getPosition() + m_Direction.getNormalized() * m_Speed * dt);
}
