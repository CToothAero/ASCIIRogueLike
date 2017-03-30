#pragma once
#include "character.h"
class CPlayer :
	public CCharacter
{
public:
	CPlayer(void);
	~CPlayer(void);

	//Character Creation
	void createPlayer(void);

	//Experience
	void levelUp(void);
	void addExperience(int newValue);

	//Setters
	void setExperience(int newValue){experienceTotal = newValue;}
	void setGoal(void){experienceGoal = 10*level;}

	//Getters
	int getExperience(void){return experienceTotal;}
	int getGoal(void){return experienceGoal;}


private:
	//Properties
	int experienceTotal;
	int experienceGoal;
};

