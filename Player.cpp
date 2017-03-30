#include "Player.h"


CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::createPlayer(void){
	setName("Mud");
	setTile('@');
	setLevel(1);
	setAttack(5);
	setDefense(2);
	setHealthMax(10);
	setHealthCurrent(10);
	setExperience(0);
}

void CPlayer::levelUp(void){
	setLevel(getLevel() + 1);
	setGoal();

	if ((level%2) == 0){
		setAttack(getAttack()+1);
		setDefense(getDefense()+1);
		setHealthMax(getHealthMax()+5);
		setHealthCurrent(getHealthMax());
	} else {
		setAttack(getAttack()+2);
		setHealthMax(getHealthMax()+10);
		setHealthCurrent(getHealthMax()-5);

	}
}

void CPlayer::addExperience(int newValue){
	setExperience(getExperience() + newValue);
	
	while (getExperience() > getGoal()){
		printf("\nLevel Up");
		levelUp();
	}
}