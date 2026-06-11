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
    const int fishW = 160;
    const int fishH = 200;
    float angle = 0;
    bool done = false;
    bool redraw = false;
    enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
    bool keys[5] = { false, false, false, false, false };
    
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* image = NULL;
    ALLEGRO_BITMAP* fly1 = NULL;
    ALLEGRO_BITMAP* fly2 = NULL;
    ALLEGRO_BITMAP* fish = NULL;
    ALLEGRO_BITMAP* spittle = NULL;

    if (!al_init()) {
        return -1;
    }

    al_init_image_addon();

    image = al_load_bitmap("waterImage.png");
    fish = al_load_bitmap("fish.png");
    fly1 = al_load_bitmap("fly.png");
    fly2 = al_load_bitmap("flysad.png");
    spittle = al_load_bitmap("spittle.png");


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
            float temp;

            if (keys[LEFT]) {
                temp = angle;
                angle -= .1;
                if (angle < -ALLEGRO_PI / 3)
                    angle = temp;
            }
            if (keys[RIGHT]) {
                temp = angle;
                angle += .1;
                if (angle > ALLEGRO_PI / 3)
                    angle = temp;
            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                //shoot somethbing
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }
        
        if (redraw && al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(image, 0, 0, 0);
            //al_draw_bitmap(fish, 400, 800, 0);
            al_draw_rotated_bitmap(fish, (fishW / 2), fishH, (screenW / 2), 800, angle, 0);
            al_draw_bitmap(fly1, 300, screenH / 2, 0);
            al_draw_bitmap(fly2, 200, screenH / 2, 0);
            al_draw_bitmap(spittle, screenW / 2, screenH / 2, 0);
            al_flip_display();
            redraw = false;
        }
    }
}