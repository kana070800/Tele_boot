#include "game.h"

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    enemy_explode[0] = al_load_sample("enemy2_bomb.wav");
    must_init(enemy_explode[0], "explode[0] sample");
    enemy_explode[1] = al_load_sample("boom_reze.wav");
    must_init(enemy_explode[1], "explode[1] sample");
    enemy_explode[2] = al_load_sample("enemy1_3.wav");
    must_init(enemy_explode[2], "explode[2] sample");

    enemy_explode[3] = al_load_sample("boss_hit.wav");
    must_init(enemy_explode[3], "explode[3] sample");
    enemy_explode[4] = al_load_sample("boss_razer.wav");
    must_init(enemy_explode[4], "explode[4] sample");

    item[0] = al_load_sample("Item_heart.wav");
    must_init(item[0], "item[0] sample");
    item[1] = al_load_sample("Item_barrier.wav");
    must_init(item[1], "item[1] sample");
    item[2] = al_load_sample("Item_treasure.wav");
    must_init(item[2], "item[2] sample");

    death[0] = al_load_sample("death1.wav");
    must_init(death[0], "death[0] sample");
    death[1] = al_load_sample("death2.wav");
    must_init(death[1], "death[1] sample");

    hit[0] = al_load_sample("hit1.wav");
    must_init(hit[0], "hit[0] sample");
    hit[1] = al_load_sample("hit2.wav");
    must_init(hit[1], "hit[1] sample");
}

void audio_deinit()
{
    al_destroy_sample(enemy_explode[0]);
    al_destroy_sample(enemy_explode[1]);
    al_destroy_sample(enemy_explode[2]);
    al_destroy_sample(enemy_explode[3]);
    al_destroy_sample(enemy_explode[4]);

    al_destroy_sample(item[0]);
    al_destroy_sample(item[1]);
    al_destroy_sample(item[2]);
    al_destroy_sample(death[0]);
    al_destroy_sample(death[1]);
    al_destroy_sample(hit[0]);
    al_destroy_sample(hit[1]);
}