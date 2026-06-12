#include "player.h"

player::player() {
	score = 0;
	gameAlive = 0;
}
player::~player() {
}
void player::updateScore() {
	score += 1;
}
int player::getScore() {
	return score;
}