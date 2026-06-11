#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "spittle.h"

spittle::spittle() {
	speed = 10;
	live = false;
	image = al_load_bitmap("spittle.png");
}
spittle::~spittle() {
	al_destroy_bitmap(image);
}

void spittle::drawSpittle() {
	if (live)
		al_draw_bitmap(image, x, y, 0);
}

void spittle::fireSpittle() {

}
