#include "JoyPad.h"

JoyPad::JoyPad()
{

}

void JoyPad::release()
{
	if (!m_parentBtn)
	{
		m_parentBtn->removeFromParentAndCleanup(true);
		//m_parentBtn->release(); 
	}
	if (!m_childBtn)
	{
		m_childBtn->removeFromParentAndCleanup(true);
		//m_childBtn->release();
	}
}

void JoyPad::Init(const std::string parentBtnFilename, const std::string childBtnFilename, Layer *gameLayer)
{
	m_parentBtn = Sprite::create(parentBtnFilename);
	m_childBtn = Sprite::create(childBtnFilename);

	m_parentBtn->setVisible(false);
	gameLayer->addChild(m_parentBtn, 1);
	m_childBtn->setVisible(false);
	gameLayer->addChild(m_childBtn, 1);
}

void JoyPad::DoTouchBegan(const Vec2 touchPos)
{
	m_parentBtn->setVisible(true);
	m_parentBtn->setPosition(touchPos);
	m_childBtn->setVisible(true);
	m_childBtn->setPosition(touchPos);
}
void JoyPad::DoTouchMoved(const Vec2 touchPos, Vec2 &velocity)
{
	Vec2 dir = touchPos - m_parentBtn->getPosition();
	float dist = m_parentBtn->getPosition().getDistance(touchPos);
	float radius = m_parentBtn->getContentSize().width / 2;
	float speed;

	if (dist <= radius)
	{
		m_childBtn->setPosition(touchPos);
		speed = m_parentBtn->getPosition().getDistance(touchPos);
	}
	else
	{
		m_childBtn->setPosition(m_parentBtn->getPosition() + MyFunction::getUnitVec2(dir) * radius);
		speed = m_parentBtn->getPosition().getDistance(m_childBtn->getPosition());
	}

	velocity.x = touchPos.x - m_parentBtn->getPositionX();
	velocity.y = touchPos.y - m_parentBtn->getPositionY();
	velocity = MyFunction::getUnitVec2(velocity) * speed;
}
void JoyPad::DoTouchEnded()
{
	m_parentBtn->setVisible(false);
	m_childBtn->setVisible(false);
}
