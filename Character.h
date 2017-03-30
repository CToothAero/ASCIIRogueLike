#pragma once
#include <string>
#include <random>

class CCharacter
{
public:
	CCharacter(void);
	~CCharacter(void);

	//Combat
	int attackRoll(std::mt19937& randomNumberGen);
	int defendRoll(std::mt19937& randomNumberGen);
	int takeDamage(int damage);

	//Setters
	void setPosition(int x, int y){positionX = x; positionY = y;}
	void setName(std::string newName){name = newName;}
	void setTile(char newValue){tile = newValue;}
	void setLevel(int newValue){level = newValue;}
	void setAttack(int newValue){attack = newValue;}
	void setDefense(int newValue){defense = newValue;}
	void setHealthMax(int newValue){healthMax = newValue;}
	void setHealthCurrent(int newValue){healthCurrent = newValue;}

	//Getters
	void getPosition(int& x, int& y){x = positionX; y = positionY;}
	std::string getName(void){return name;}
	char getTile(void){return tile;}
	int getLevel(void){return level;}
	int getAttack(void){return attack;}
	int getDefense(void){return defense;}
	int getHealthMax(void){return healthMax;}
	int getHealthCurrent(void){return healthCurrent;}

protected:
	//Properties
	std::string name;
	char tile;
	int level;
	int attack;
	int defense;
	int healthMax;
	int healthCurrent;

	//Position on Map
	int positionX;
	int positionY;
};

