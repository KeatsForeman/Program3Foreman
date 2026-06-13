#ifndef PLAYER_H
#define PLAYER_H

class player {
public:
	player();
	~player();
	void updateScore();
	int getScore();
	void updateGameStatus();
	int getGameStatus();

private:
	int score;
	int gameStatus;
};
#endif