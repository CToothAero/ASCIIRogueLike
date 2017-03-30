#pragma once

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <random>
#include <conio.h>

class CGameSystem
{
public:
	CGameSystem(std::mt19937& random);
	~CGameSystem(void);

	void playGame(void);
	void characterMove(CLevel& useLevel);

private:
	CPlayer player;
	
	std::mt19937 randomNumberGen;
};

