#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "spittle.h"
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
		std::cout << "NO IM AGE ";
	}
	if (live)
		al_draw_bitmap(image, x, y, 0);
}

void spittle::fireSpittle() {
	if (!live) {
		x = 300;
		y = 800;
		live = true;
	}
}
void spittle::updateSpittle() {
	y -= 5;
	if (y <= 0) {
		live = false;
	}
}
bool spittle::getLive() {
	return live;
}
