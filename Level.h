#pragma once
#include <vector>
#include <fstream>
#include <random>
#include "Player.h"
#include "Enemy.h"

class CLevel
{
public:
	CLevel(std::mt19937 random);
	~CLevel(void);

	//Map
	void loadMap(std::string fileName, CPlayer& player);
	void printMap(void);

	//Movement
	void movePlayer(char input, CPlayer& player);
	void updateMonsters(CPlayer& player);

	//Map Tile
	char getTile(int x, int y){return levelData[y][x];}
	void setTile(int x, int y, char tile){levelData[y][x] = tile;}

private:
	std::vector<std::string> levelData;
	std::vector<CEnemy> enemies;
	std::mt19937 randomNumberGen;

	void processMove(CPlayer& player, int targetX, int targetY);
	void processMonsterMove(CPlayer& player, int enemyIndex, int targetX, int targetY);
	void battleMonster(CPlayer& player, int targetX, int targetY);
	void battlePlayer(CPlayer&player, int enemyIndex);
};

