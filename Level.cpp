#include "Level.h"


CLevel::CLevel(std::mt19937 random)
{
	randomNumberGen = random;
}


CLevel::~CLevel(void)
{
}

void CLevel::loadMap(std::string fileName, CPlayer& player){
	std::ifstream mapFile;
	mapFile.open(fileName);
	if (mapFile.fail()){
		std::perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}
	std::string line;
	while(std::getline(mapFile, line)){
		levelData.push_back(line);
	}
	mapFile.close();

	char tile;
	for (int i = 0; i < levelData.size(); i++){
		for (int j = 0; j < levelData[i].size(); j++){
			tile = levelData[i][j];
			switch (tile){
			case '@'://player
				player.setPosition(j,i);
				break;
			case 'g'://goblin
				enemies.push_back(CEnemy("Goblin",'g',2,3,2,5,j,i,50));
				break;
			case 's'://snake
				enemies.push_back(CEnemy("Snake",'s',1,1,1,2,j,i,10));
				break;
			case 'B':	//Bandit
				enemies.push_back(CEnemy("Bandit",'B',3,5,3,10,j,i,100));
				break;
			case 'O':	//Ogre
				enemies.push_back(CEnemy("Ogre",'O',5,10,8,20,j,i,150));
				break;
			case 'D':	//Dragon
				enemies.push_back(CEnemy("Dragon",'D',10,20,20,50,j,i,500));
			}
		}
	}
}

void CLevel::printMap(void){
	printf("%s",std::string(25,'\n').c_str());
	for (int i = 0; i < levelData.size(); i++){
		printf("%s\n", levelData[i].c_str());
	}
	printf("\n");
}

void CLevel::movePlayer(char input, CPlayer& player){
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	switch (input){
	case 'W':	//Up
	case 'w':
		processMove(player, playerX, playerY-1);
		break;
	case 'S':
	case 's':
		processMove(player, playerX, playerY+1);
		break;
	case 'A':
	case 'a':
		processMove(player, playerX-1, playerY);
		break;
	case 'D':
	case 'd':
		processMove(player, playerX+1, playerY);
		break;
	}
}

void CLevel::updateMonsters(CPlayer& player){
	char aiMove;
	int playerX, playerY;
	int enemyX, enemyY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < enemies.size(); i++){
		aiMove = enemies[i].getMove(playerX, playerY);
		enemies[i].getPosition(enemyX, enemyY);
		switch (aiMove){
		case 'w':
			processMonsterMove(player, i, enemyX, enemyY-1);
			break;
		case 's':
			processMonsterMove(player, i, enemyX, enemyY+1);
			break;
		case 'a':
			processMonsterMove(player, i, enemyX-1, enemyY);
			break;
		case 'd':
			processMonsterMove(player, i, enemyX+1, enemyY);
			break;
		}
	}
}

void CLevel::processMove(CPlayer& player, int targetX, int targetY){
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);
	switch (moveTile){
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void CLevel::processMonsterMove(CPlayer& player, int enemyIndex, int targetX, int targetY){
	int playerX, playerY;
	int enemyX, enemyY;
	enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);
	switch (moveTile){
	case '.':
		enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, enemies[enemyIndex].getTile());
		break;
	case '#':
		break;
	case '@':
		battlePlayer(player, enemyIndex);
		break;
	default:
		break;
	}
}

void CLevel::battleMonster(CPlayer& player, int targetX, int targetY){
	int enemyX, enemyY;
	int playerX, playerY;
	player.getPosition(playerX, playerY);
	int attackRoll, defendRoll, attackResult;
	std::string enemyName, playerName;
	playerName = player.getName();

	for (int i = 0; i < enemies.size(); i++){
		enemies[i].getPosition(enemyX, enemyY);
		if ((targetX == enemyX)&&(targetY == enemyY)){
			enemyName = enemies[i].getName();
			attackRoll = player.attackRoll(randomNumberGen);
			defendRoll = enemies[i].defendRoll(randomNumberGen);
			printf("\n%s attacks %s: %i attack - %i defense\n",
				playerName.c_str(), enemyName.c_str(), attackRoll, defendRoll);
			attackResult = enemies[i].takeDamage(attackRoll-defendRoll);
			printf("%s health %i / %i\n",
				enemyName.c_str(), enemies[i].getHealthCurrent(), enemies[i].getHealthMax());

			if (attackResult){
				setTile(targetX, targetY, '.');
				printf("%s is dead! %s gained %i exp!",
					enemyName.c_str(), playerName.c_str(), enemies[i].getExpValue());
				player.addExperience(enemies[i].getExpValue());
				enemies[i] = enemies.back();
				enemies.pop_back();
				i--;

				system("PAUSE");
				return;
			}

			attackRoll = enemies[i].attackRoll(randomNumberGen);
			defendRoll = player.defendRoll(randomNumberGen);
			printf("\n%s attacks %s: %i attack - %i defense\n",
				enemyName.c_str(), playerName.c_str(), attackRoll, defendRoll);
			attackResult = player.takeDamage(attackRoll - defendRoll);
			printf("%s health %i / %i\n",
				playerName.c_str(), player.getHealthCurrent(), player.getHealthMax());

			if (attackResult){
				setTile(playerX, playerY, 'x');
				printf("\nYou died!\n");
				system("PAUSE");
				exit(0);
				return;
			}
			system("PAUSE");
		}
	}
}

void CLevel::battlePlayer(CPlayer& player, int enemyIndex){
	printMap();
	int enemyX, enemyY;
	int playerX, playerY;
	player.getPosition(playerX, playerY);
	int attackRoll, defendRoll, attackResult;
	std::string enemyName, playerName;
	playerName = player.getName();
	enemyName = enemies[enemyIndex].getName();
	enemies[enemyIndex].getPosition(enemyX, enemyY);

	attackRoll = enemies[enemyIndex].attackRoll(randomNumberGen);
	defendRoll = player.defendRoll(randomNumberGen);
	printf("%s attacks %s: %i attack - %i defense\n",
		enemyName.c_str(), playerName.c_str(), attackRoll, defendRoll);
	attackResult = player.takeDamage(attackRoll - defendRoll);
	printf("%s health %i / %i\n",
		playerName.c_str(), player.getHealthCurrent(), player.getHealthMax());

	if (attackResult){
		setTile(playerX, playerY, 'x');
		printf("\nYou died!\n");
		system("PAUSE");
		exit(0);
		return;
	}

	attackRoll = player.attackRoll(randomNumberGen);
	defendRoll = enemies[enemyIndex].defendRoll(randomNumberGen);
	printf("%s attacks %s: %i attack - %i defense\n",
		playerName.c_str(), enemyName.c_str(), attackRoll, defendRoll);
	attackResult = enemies[enemyIndex].takeDamage(attackRoll-defendRoll);
	printf("%s health %i / %i\n",
		enemyName.c_str(), enemies[enemyIndex].getHealthCurrent(), enemies[enemyIndex].getHealthMax());

	if (attackResult){
		setTile(enemyX, enemyY, '.');
		printf("%s is dead! %s gained %i exp!",
			enemyName.c_str(), playerName.c_str(), enemies[enemyIndex].getExpValue());
		player.addExperience(enemies[enemyIndex].getExpValue());
		enemies[enemyIndex] = enemies.back();
		enemies.pop_back();

		system("PAUSE");
		return;
	}
	system("PAUSE");
}