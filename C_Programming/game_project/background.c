#include "game.h"

void background(int n)
{/*
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return;
    }*/
    char filename[256];
    snprintf(filename, sizeof(filename), "%d.png", n);
    ALLEGRO_BITMAP* image = al_load_bitmap(filename);

    if (!image) {
        printf("couldn't load images : %s\n", filename);
        return;
    }
    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(image);
    float img_height = al_get_bitmap_height(image);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(image, 0, 0, img_width, img_height, 0, 0, screen_width, screen_height, 0);
    al_flip_display();
    al_destroy_bitmap(image);

}