#pragma once

#include "cocos2d.h"

USING_NS_CC;

class JoyPad : Layer
{
public:
	static JoyPad *create(const std::string _parentBtnFilename, const std::string _childBtnFilename, Layer *_gameLayer);


private:
	virtual bool init(const std::string _parentBtnFilename, const std::string _childBtnFilename, Layer *_gameLayer);

public:
	void DoTouchBegan(const Vec2 touchPos);
	void DoTouchMoved(const Vec2 touchPos, Vec2 &velocity);
	void DoTouchEnded();

private:
	Sprite *m_ParentBtn;
	Sprite *m_ChildBtn;
};