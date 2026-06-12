#ifndef PLAYER_H
#define PLAYER_H

class player {
public:
	player();
	~player();
	void updateScore();
	int getScore();

private:
	int score;
	int gameAlive;
};
#endif