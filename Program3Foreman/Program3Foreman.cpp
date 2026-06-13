// Program3Foreman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include "spittle.h"
#include "fly.h"
#include "player.h"


int main(int argc, char** argv) {

    const float fps = 60;
    int currentTime = 0;
    const int screenW = 600;
    const int screenH = 900;
    const int fishW = 160;
    const int fishH = 200;
    float angle = 0;
    bool done = false;
    bool finish = false;
    bool redraw = false;
    const int Num_spittles = 20;
    const int Num_flies = 10;
    enum KEYS { LEFT, RIGHT, SPACE };
    bool keys[5] = { false, false, false };
    
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* image = NULL;
    ALLEGRO_BITMAP* fish = NULL;

    if (!al_init()) {
        return -1;
    }
    al_init_ttf_addon();
    al_init_font_addon();
    al_init_image_addon();

    spittle Spittles[Num_spittles];
    fly Flies[Num_flies];
    player myPlayer;
    ALLEGRO_FONT* font = al_load_font("Cat.ttf", 30, 0);

    image = al_load_bitmap("waterImage.png");
    fish = al_load_bitmap("fish.png");


    display = al_create_display(screenW, screenH);
    timer = al_create_timer(1.0 / fps);
    al_install_keyboard();
    al_install_mouse();

    event_queue = al_create_event_queue();
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    srand(time(0));
    int random;
    al_start_timer(timer);

    while (!done) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            random = rand() % 500;
            redraw = true;
            float temp;
            currentTime += 1;

            //drop about once a second
            if (currentTime % 60 == 0) {
                for (int i = 0; i < Num_flies; i++) {
                    if (!Flies[i].getLive()) {
                        Flies[i].dropFly(random);
                        break;
                    }
                }
            }
            for (int i = 0; i < Num_flies; i++) {
                Flies[i].updateFly(myPlayer);
            }
            for (int i = 0; i < Num_spittles; i++) {
                Spittles[i].updateSpittle();
            }
            if (myPlayer.getGameStatus() == 5) {
                done = true;
                finish = true;
            }

            if (keys[LEFT]) {
                temp = angle;
                angle -= .05;
                if (angle < -ALLEGRO_PI / 3) // pi / 3 for 60 degree range 
                    angle = temp;
            }
            if (keys[RIGHT]) {
                temp = angle;
                angle += .05;
                if (angle > ALLEGRO_PI / 3) // 60 on both sides
                    angle = temp;
            }
            if (keys[SPACE]) {
                for (int i = 0; i < Num_spittles; i++) {
                    //puts a gap between shots so all are not fired at once
                    if ((!Spittles[i].getLive()) && (currentTime % 10 == 0)) {
                        Spittles[i].fireSpittle(angle);
                        break;
                    }
                }
            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
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
            
            std::string scoreBoard = std::to_string(myPlayer.getScore());
            al_draw_text(font, al_map_rgb(0, 0, 0), 50, 860, 0, scoreBoard.c_str());

            al_draw_rotated_bitmap(fish, (fishW / 2) - 5, fishH/2, (screenW / 2), 750, angle, 0);
            for (int i = 0; i < Num_spittles; i++) {
                Spittles[i].drawSpittle();
            }
            for (int i = 0; i < Num_flies; i++) {
                Flies[i].drawFly(Flies[i].getVersion());
            }
            for (int i = 0; i < Num_spittles; i++) {
                Spittles[i].collideSpittle(Flies, Num_flies, myPlayer);
            }
            al_flip_display();
            redraw = false;
        }
    }

    //end of game loop for attacking animation
    while (finish) {
        int complete = 0;
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(image, 0, 0, 0);
        al_draw_rotated_bitmap(fish, (fishW / 2) - 5, fishH / 2, (screenW / 2), 750, angle, 0);
        for (int i = 0; i < Num_flies; i++) {
            Flies[i].killFish();
            Flies[i].drawFly(Flies[i].getVersion());
            if (Flies[i].getX() == 240) 
                complete += 1;
        }
        al_flip_display();
        if (complete == 5) //waits till all flies are in place
            finish = false;
    }
    //shows score at end
    al_clear_to_color(al_map_rgb(0, 0, 0));
    std::string scoreBoard = std::to_string(myPlayer.getScore());
    al_draw_text(font, al_map_rgb(255, 255, 255), screenW/2-150, screenH/2, 0, "You scored: ");
    al_draw_text(font, al_map_rgb(255, 255, 255), screenW/2, screenH/2, 0, scoreBoard.c_str());
    al_flip_display();
    al_rest(5);
}