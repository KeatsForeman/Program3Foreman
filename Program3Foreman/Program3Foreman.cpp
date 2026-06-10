// Program3Foreman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>


int main(int argc, char** argv){
    
    const float fps = 60;
    const int screenW = 600;
    const int screenH = 900;
    const int frogSize = 50;
    float angle = 0;
    bool done = false;
    bool redraw = false;
    
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* image = NULL;
    ALLEGRO_BITMAP* fly1 = NULL;
    ALLEGRO_BITMAP* fly2 = NULL;
    ALLEGRO_BITMAP* frog = NULL;

    if (!al_init()) {
        return -1;
    }

    al_init_image_addon();

    image = al_load_bitmap("fantasy.png");
    frog = al_load_bitmap("arrow1.png");
    fly1 = al_load_bitmap("attacking.png");



    display = al_create_display(screenW, screenH);
    timer = al_create_timer(1.0 / fps);
    al_install_keyboard();
    al_install_mouse();

    event_queue = al_create_event_queue();
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);

    while (!done) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            angle += .1;

        }
        if (redraw) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(image, 0, 0, 0);
            //al_draw_bitmap(frog, 400, 800, 0);
            al_draw_rotated_bitmap(frog, (frogSize / 2), frogSize / 2, (screenW / 2 - (frogSize / 2)), 800, angle, 0);
            al_draw_bitmap(fly1, 300, screenH / 2, 0);
            al_flip_display();
            redraw = false;
        }
    }
}