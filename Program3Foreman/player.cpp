#include "player.h"

player::player() {
	score = 0;
	gameStatus = 0;
}
player::~player() {
}
void player::updateScore() {
	score += 1;
}
int player::getScore() {
	return score;
}
void player::updateGameStatus() {
	gameStatus += 1;
}
int player::getGameStatus() {
	return gameStatus;
}