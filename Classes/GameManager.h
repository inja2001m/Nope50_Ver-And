#pragma once

#include "BaseSingleton.h"

class GameManager : public BaseSingleton<GameManager>
{
public:
	GameManager() = default;
	~GameManager() = default;

public:
	bool m_IsGameOver = false;
};