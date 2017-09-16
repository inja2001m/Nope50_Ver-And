#pragma once

#include "cocos2d.h"
#include "My_Defines.h"

using namespace cocos2d;

class JoyPad
{
public:
	JoyPad();
	JoyPad(const JoyPad &other) = default;
	~JoyPad() = default;

	void release();

public:
	void Init(const std::string parentBtnFilename, const std::string childBtnFilename, Layer *gameLayer);

public:
	void DoTouchBegan(const Vec2 touchPos);
	void DoTouchMoved(const Vec2 touchPos, Vec2 &velocity);
	void DoTouchEnded();

private:
	Sprite *m_parentBtn;
	Sprite *m_childBtn;
};