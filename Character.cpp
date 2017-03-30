#include "Character.h"


CCharacter::CCharacter(void)
{
}


CCharacter::~CCharacter(void)
{
}

int CCharacter::attackRoll(std::mt19937& randomNumberGen){
	std::uniform_int_distribution<int> roll(1,attack+1);
	return roll(randomNumberGen)-1;
}

int CCharacter::defendRoll(std::mt19937& randomNumberGen){
	std::uniform_int_distribution<int> roll(1,defense+1);
	return roll(randomNumberGen)-1;
}

int CCharacter::takeDamage(int damage){
	if (damage < 0){ damage = 0;}
	healthCurrent -= damage;
	if (healthCurrent <= 0){
		healthCurrent = 0;
		return 1;
	}
	return 0;
}