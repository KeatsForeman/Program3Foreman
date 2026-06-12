#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "fly.h"
#include <iostream>

fly::fly() {
	speed = 2;
	live = false;
	boundx = 100;
	boundy = 80;
	version = 0;
	images[0] = al_load_bitmap("fly.png");
	images[1] = al_load_bitmap("flySad.png");
}
fly::~fly() {
	al_destroy_bitmap(images[0]);
	al_destroy_bitmap(images[1]);
}
void fly::drawFly(int v) {
	if (live) {
		al_draw_bitmap(images[v], x, y, 0);
	}
}
void fly::dropFly(int xx) {
	x = xx;
	y = 0;
	live = true;
}
void fly::updateFly() {
	y += speed;
	if (y > 720) {
		version = 0;
		live = false;
	}
}
void fly::setLive(bool new_live) {
	live = new_live;
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
void fly::setVersion(int v) {
	version = v;
}
int fly::getVersion() {
	return version;
}