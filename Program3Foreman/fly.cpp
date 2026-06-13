#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "fly.h"
#include <iostream>

//constructor
fly::fly() {
	speed = 2;
	live = false;
	boundx = 50;
	boundy = 40;
	version = 0;
	images[0] = al_load_bitmap("fly.png");
	images[1] = al_load_bitmap("flySad.png");
	images[2] = al_load_bitmap("angryFly2.png");
}
//deconstructor
fly::~fly() {
	al_destroy_bitmap(images[0]);
	al_destroy_bitmap(images[1]);
}
//draws fly bitmaps
//takes int parameter that determines which image to use
void fly::drawFly(int v) {
	if (live) {
		al_draw_bitmap(images[v], x, y, 0);
	}
}
//initializes fly drops
//takes int parameter which determines the left/right position
void fly::dropFly(int xx) {
	x = xx;
	y = 0;
	version = 0;
	live = true;
}
//updates the y position of the fly, and tracks whether unhit flies have reached the bottom, and updates gameSatus
//takes player reference as parameter 
void fly::updateFly(player &myPlayer) {
	if (live) {
		if (version == 0) {
			y += speed;
			if (y > 800) {
				version = 2;
				y = 800;
				myPlayer.updateGameStatus();
			}
		}
		else if (version == 1) {
			y += speed;
			if (y > 800) {
				version = 0;
				live = false;
			}
		}
	}
}
//moves angry flies to fish at end
void fly::killFish() {
	if (version == 2) {
		if (x > 243)
			x -= 3;
		else if (x < 237)
			x += 3;
		else 
			x = 240;
	}
}
//sets the status of the fly
//takes boolean parameter
void fly::setLive(bool new_live) {
	live = new_live;
}
void fly::setVersion(int v) {
	version = v;
}
bool fly::getLive() {
	return live;
}
int fly::getX() {
	return x;
}
int fly::getY() {
	return y;
}
int fly::getBoundx() {
	return boundx;
}
int fly::getBoundy() {
	return boundy;
}
int fly::getVersion() {
	return version;
}