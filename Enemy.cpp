#include "Enemy.h"


CEnemy::CEnemy(std::string inName, char inTile, int inLevel, int inAttack, int inDefense,
	int inHealth, int inPosX, int inPosY, int inExpValue)
{
	setName(inName);
	setTile(inTile);
	setLevel(inLevel);
	setAttack(inAttack);
	setDefense(inDefense);
	setHealthMax(inHealth);
	setHealthCurrent(inHealth);
	setPosition(inPosX, inPosY);
	setExpValue(inExpValue);
}


CEnemy::~CEnemy(void)
{
}

void CEnemy::initMonster(void){

}

char CEnemy::getMove(int playerX, int playerY){
	int dist;
	int dX = positionX - playerX;
	int dY = positionY - playerY;
	int adX = abs(dX);
	int adY = abs(dY);
	

	dist = adX + adY;
	if (dist < 5){
		if (adX < adY){
			if (dY > 0){
				return 'w';
			} else {
				return 's';
			}
		} else {
			if (dX > 0){
				return 'a';
			} else {
				return 'd';
			}
		}
	} else {
		return '.';
	}
}