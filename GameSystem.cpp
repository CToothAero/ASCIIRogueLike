#include "GameSystem.h"


CGameSystem::CGameSystem(std::mt19937& random)
{
	randomNumberGen = random;
	player.createPlayer();
}


CGameSystem::~CGameSystem(void)
{
}


void CGameSystem::playGame(void){
	CLevel level(randomNumberGen);
	level.loadMap("levelDesign.txt", player);
	
	bool isDone = false;
	while(!isDone){
		level.printMap();
		characterMove(level);
		level.updateMonsters(player);
	}
}

void CGameSystem::characterMove(CLevel& useLevel){
	char input;
	printf("Enter move command: ");
	input = getch();
	useLevel.movePlayer(input, player);
}