#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "spittle.h"
#include "fly.h"
#include <iostream>

spittle::spittle() {
	speed = 10;
	live = false;
	radian_angle = 0;
	image = al_load_bitmap("spittle.png");
}
spittle::~spittle() {
	al_destroy_bitmap(image);
}

void spittle::drawSpittle() {
	if (!image) {
		std::cout << "NO IMAGE ";
	}
	if (live)
		al_draw_bitmap(image, x, y, 0);
}

void spittle::fireSpittle(float angle) {
	if (!live) {
		x = 300;
		y = 800;
		radian_angle = angle;
		live = true;
	}
}
void spittle::updateSpittle() {
	x -= (5 * cos(radian_angle + ALLEGRO_PI/2));
	y -= (5 * sin(radian_angle + ALLEGRO_PI/2));
	if ((y <= 0) || (x <= 0) || (x >= 570)) {
		live = false;
	}
}
void spittle::collideSpittle(fly Flies[], int Num_Flies) {
	if (live) {
		for (int i = 0; i < Num_Flies; i++) {
			if (Flies[i].getLive()) {
				if (Flies[i].getY() > y) {
					Flies[i].setLive(false);
					live = false;
				}
			}
		}
	}
}
bool spittle::getLive() {
	return live;
}
int spittle::getX() {
	return x;
}
int spittle::getY() {
	return y;
}