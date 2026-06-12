#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "fly.h"
#include <iostream>

fly::fly() {
	speed = 2;
	live = false;
	image = al_load_bitmap("fly.png");
}
fly::~fly() {
	al_destroy_bitmap(image);
}
void fly::drawFly() {
	if (live) {
		al_draw_bitmap(image, x, y, 0);
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