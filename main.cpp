#include "GameSystem.h"
#include <random>
#include <ctime>

std::mt19937 randomRoller(time(NULL));

int main (void){
	CGameSystem game(randomRoller);

	game.playGame();

	return 0;
}