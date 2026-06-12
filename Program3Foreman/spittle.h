#ifndef SPITTLE_H
#define SPITTLE_H
#include "fly.h"
#include "player.h"

class spittle {
public:
	spittle();
	~spittle();
	void drawSpittle();
	void fireSpittle(float angle);
	void updateSpittle();
	void collideSpittle(fly Flies[], int num_Flies, player &myPlayer);
	bool getLive();
	int getX();
	int getY();

private:
	int x, y;
	int speed;
	bool live;
	float radian_angle;
	ALLEGRO_BITMAP* image;
};
#endif