#pragma once
#include "character.h"
class CEnemy :
	public CCharacter
{
public:
	CEnemy(std::string inName, char inTile, int inLevel, int inAttack, int inDefense,
		int inHealth, int inPosX, int inPosY, int inExpValue);
	~CEnemy(void);

	//Setup
	void initMonster(void);

	//Movement
	char getMove(int playerX, int playerY);

	//Setters
	void setExpValue(int newValue){experienceValue = newValue;}

	//Getters
	int getExpValue(void){return experienceValue;}

private:
	//Properties
	int experienceValue;
};

