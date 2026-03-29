#include "game.h"
#define DISP_W BUFFER_W * DISP_SCALE            // 게임 화면의 실제 가로 너비
#define DISP_H BUFFER_H * DISP_SCALE            // 게임 화면의 실제 세로 너비
// --- general ---
extern unsigned char key[ALLEGRO_KEY_MAX];
extern SPRITES sprites;

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int between(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}

float between_f(float lo, float hi)
{
    return lo + ((float)rand() / (float)RAND_MAX) * (hi - lo);
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if (ax1 > bx2) return false;
    if (ax2 < bx1) return false;
    if (ay1 > by2) return false;
    if (ay2 < by1) return false;

    return true;
}


// --- display ---

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

void disp_pre_draw()
{
    al_set_target_bitmap(buffer);
}

void disp_post_draw()
{
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}


// --- keyboard ---

#define KEY_SEEN     1
#define KEY_DOWN     2

void keyboard_init()
{
    memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= ~KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        break;
    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= ~KEY_DOWN;
        break;
    }
}
// --- sprites ---


ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

void sprites_init(void)
{
    sprites._sheet = al_load_bitmap("GameIMG.png");
    must_init(sprites._sheet, "spritesheet");

    /* player: [gender][state][dir] */

    /* male */
    sprites.player[0][0][0] = sprite_grab(5, 10, PLAYER1_W, PLAYER1_H);
    sprites.player[0][0][1] = sprite_grab(48, 10, PLAYER1_W, PLAYER1_H);

    sprites.player[0][1][0] = sprite_grab(10, 82, PLAYER2_W, PLAYER2_H);
    sprites.player[0][1][1] = sprite_grab(45, 78, PLAYER2_W, PLAYER2_H);

    sprites.player[0][2][0] = sprite_grab(178, 80, PLAYER3_W, PLAYER3_H);
    sprites.player[0][2][1] = sprite_grab(230, 80, PLAYER3_W, PLAYER3_H);

    /* female */
    sprites.player[1][0][0] = sprite_grab(95, 10, PLAYER1_W, PLAYER1_H);
    sprites.player[1][0][1] = sprite_grab(140, 8, PLAYER1_W, PLAYER1_H);

    sprites.player[1][1][0] = sprite_grab(92, 81, PLAYER2_W, PLAYER2_H);
    sprites.player[1][1][1] = sprite_grab(138, 80, PLAYER2_W, PLAYER2_H);

    sprites.player[1][2][0] = sprite_grab(178, 5, PLAYER3_W, PLAYER3_H);
    sprites.player[1][2][1] = sprite_grab(228, 5, PLAYER3_W, PLAYER3_H);

    /* item */
    sprites.item[ITEM_HEART] = sprite_grab(4, 200, ITEM_HEART_W, ITEM_HEART_H);
    sprites.item[ITEM_BARRIER] = sprite_grab(52, 196, ITEM_BARRIER_W, ITEM_BARRIER_H);
    sprites.item[ITEM_TREASURE_CHEST] = sprite_grab(10, 155, ITEM_TREASURE_CHEST_W, ITEM_TREASURE_CHEST_H);

    /* enemy */
    sprites.enemy[ENEMY_SPEAR] = sprite_grab(67, 155, ENEMY_SPEAR_W, ENEMY_SPEAR_H);
    sprites.enemy[ENEMY_BOMB] = sprite_grab(105, 145, ENEMY_BOMB_W, ENEMY_BOMB_H);
    sprites.enemy[ENEMY_FIREBALL] = sprite_grab(167, 154, ENEMY_FIREBALL_W, ENEMY_FIREBALL_H);
    sprites.enemy[ENEMY_HOMING] = sprite_grab(212, 148, ENEMY_HOMING_W, ENEMY_HOMING_H);
}

void sprites_deinit(void)
{
    for (int gender = 0; gender < 2; gender++) {
        for (int state = 0; state < 3; state++) {
            for (int dir = 0; dir < 2; dir++) {
                if (sprites.player[gender][state][dir]) {
                    al_destroy_bitmap(sprites.player[gender][state][dir]);
                    sprites.player[gender][state][dir] = NULL;
                }
            }
        }
    }

    for (int i = 0; i < ITEM_TYPE_N; i++) {
        if (sprites.item[i]) {
            al_destroy_bitmap(sprites.item[i]);
            sprites.item[i] = NULL;
        }
    }

    for (int i = 0; i < ENEMY_TYPE_N; i++) {
        if (sprites.enemy[i]) {
            al_destroy_bitmap(sprites.enemy[i]);
            sprites.enemy[i] = NULL;
        }
    }

    if (sprites._sheet) {
        al_destroy_bitmap(sprites._sheet);
        sprites._sheet = NULL;
    }
}
/*
ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

void sprites_init()
{
    sprites._sheet = al_load_bitmap("GameIMG.png");
    must_init(sprites._sheet, "spritesheet");

    // 남자
    sprites.player[0][0][0] = sprite_grab(5, 10, PLAYER1_W, PLAYER1_H);
    sprites.player[0][0][1] = sprite_grab(48, 10, PLAYER1_W, PLAYER1_H);

    sprites.player[0][1][0] = sprite_grab(10, 82, PLAYER2_W, PLAYER2_H);
    sprites.player[0][1][1] = sprite_grab(45, 78, PLAYER2_W, PLAYER2_H);

    sprites.player[0][2][0] = sprite_grab(178, 80, PLAYER3_W, PLAYER3_H);
    sprites.player[0][2][1] = sprite_grab(230, 80, PLAYER3_W, PLAYER3_H);

    //여자
    sprites.player[1][0][0] = sprite_grab(95, 10, PLAYER1_W, PLAYER1_H);
    sprites.player[1][0][1] = sprite_grab(140, 8, PLAYER1_W, PLAYER1_H);

    sprites.player[1][1][0] = sprite_grab(92, 81, PLAYER2_W, PLAYER2_H);
    sprites.player[1][1][1] = sprite_grab(138, 80, PLAYER2_W, PLAYER2_H);

    sprites.player[1][2][0] = sprite_grab(178, 5, PLAYER3_W, PLAYER3_H);
    sprites.player[1][2][1] = sprite_grab(228, 5, PLAYER3_W, PLAYER3_H);

    // 아이템 (하트, 베리어, 보물 순)
    sprites.item[0] = sprite_grab(4, 200, ITEM1_W, ITEM1_H);
    sprites.item[1] = sprite_grab(52, 196, ITEM2_W, ITEM2_H);
    sprites.item[2] = sprite_grab(10, 155, ITEM3_W, ITEM3_H);

    // 적
    sprites.enemy[0] = sprite_grab(67, 155, ENEMY_DAGGER_W, ENEMY_DAGGER_H);
    sprites.enemy[1] = sprite_grab(105, 145, ENEMY_BOMB_W, ENEMY_BOMB_H);
    sprites.enemy[2] = sprite_grab(167, 154, ENEMY_FIREBALL_W, ENEMY_FIREBALL_H);
    sprites.enemy[3] = sprite_grab(212, 148, ENEMY_HOMING_W, ENEMY_HOMING_H);
}

void sprites_deinit()
{
    al_destroy_bitmap(sprites.player[0][0][0]);
    al_destroy_bitmap(sprites.player[0][0][1]);
    al_destroy_bitmap(sprites.player[0][1][0]);
    al_destroy_bitmap(sprites.player[0][1][1]);
    al_destroy_bitmap(sprites.player[0][2][0]);
    al_destroy_bitmap(sprites.player[0][2][1]);
    al_destroy_bitmap(sprites.player[1][0][0]);
    al_destroy_bitmap(sprites.player[1][0][1]);
    al_destroy_bitmap(sprites.player[1][1][0]);
    al_destroy_bitmap(sprites.player[1][1][1]);
    al_destroy_bitmap(sprites.player[1][2][0]);
    al_destroy_bitmap(sprites.player[1][2][1]);

    al_destroy_bitmap(sprites.enemy[0]);
    al_destroy_bitmap(sprites.enemy[1]);
    al_destroy_bitmap(sprites.enemy[2]);
    al_destroy_bitmap(sprites.enemy[3]);

    al_destroy_bitmap(sprites.item[0]);
    al_destroy_bitmap(sprites.item[1]);
    al_destroy_bitmap(sprites.item[2]);

    al_destroy_bitmap(sprites._sheet);
}
*/
// --- audio ---
/*
ALLEGRO_SAMPLE* sample_shot;
ALLEGRO_SAMPLE* sample_explode[2];

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    sample_shot = al_load_sample("shot.flac");
    must_init(sample_shot, "shot sample");

    sample_explode[0] = al_load_sample("explode1.flac");
    must_init(sample_explode[0], "explode[0] sample");
    sample_explode[1] = al_load_sample("explode2.flac");
    must_init(sample_explode[1], "explode[1] sample");
}

void audio_deinit()
{
    al_destroy_sample(sample_shot);
    al_destroy_sample(sample_explode[0]);
    al_destroy_sample(sample_explode[1]);
}*/