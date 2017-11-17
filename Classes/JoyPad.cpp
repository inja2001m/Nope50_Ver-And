#include "JoyPad.h"

JoyPad * JoyPad::create(const std::string _parentBtnFilename, const std::string _childBtnFilename, Layer *_gameLayer)
{
	JoyPad *pRet = new (std::nothrow)JoyPad();
	if (pRet && pRet->init(_parentBtnFilename, _childBtnFilename, _gameLayer))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
}

bool JoyPad::init(const std::string _parentBtnFilename, const std::string _childBtnFilename, Layer *_gameLayer)
{
	m_ParentBtn = Sprite::create(_parentBtnFilename);
	m_ParentBtn->setVisible(false);
	_gameLayer->addChild(m_ParentBtn, 1);

	m_ChildBtn = Sprite::create(_childBtnFilename);
	m_ChildBtn->setVisible(false);
	_gameLayer->addChild(m_ChildBtn, 1);
	
	_gameLayer->addChild(this);

	return true;
}

void JoyPad::DoTouchBegan(const Vec2 touchPos)
{
	m_ParentBtn->setVisible(true);
	m_ParentBtn->setPosition(touchPos);
	m_ChildBtn->setVisible(true);
	m_ChildBtn->setPosition(touchPos);
}
void JoyPad::DoTouchMoved(const Vec2 touchPos, Vec2 &velocity)
{
	Vec2 dir = touchPos - m_ParentBtn->getPosition();
	float dist = m_ParentBtn->getPosition().getDistance(touchPos);
	float radius = m_ParentBtn->getContentSize().width * 0.5f;
	float speed;

	if (dist <= radius)
	{
		m_ChildBtn->setPosition(touchPos);
		speed = m_ParentBtn->getPosition().getDistance(touchPos);
	}
	else
	{
		m_ChildBtn->setPosition(m_ParentBtn->getPosition() + dir.getNormalized() * radius);
		speed = m_ParentBtn->getPosition().getDistance(m_ChildBtn->getPosition());
	}

	velocity.x = touchPos.x - m_ParentBtn->getPositionX();
	velocity.y = touchPos.y - m_ParentBtn->getPositionY();
	velocity = velocity.getNormalized() * speed;
}
void JoyPad::DoTouchEnded()
{
	m_ParentBtn->setVisible(false);
	m_ChildBtn->setVisible(false);
}
