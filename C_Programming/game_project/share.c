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
    sprites._sheet = al_load_bitmap("GameIMG2.png");
    must_init(sprites._sheet, "spritesheet");

    /* player: [gender][state][dir] */

    /* male */
    sprites.player[0][0][0] = sprite_grab(15 + 44, 11, PLAYER1_W, PLAYER1_H);
    sprites.player[0][0][1] = sprite_grab(55 + 44, 12, PLAYER1_W, PLAYER1_H);

    sprites.player[0][1][0] = sprite_grab(2 + 44, 82, PLAYER2_W, PLAYER2_H);
    sprites.player[0][1][1] = sprite_grab(52 + 44, 83, PLAYER2_W, PLAYER2_H);
    
    sprites.player[0][2][0] = sprite_grab(242 + 44, 11, PLAYER3_W, PLAYER3_H);
    sprites.player[0][2][1] = sprite_grab(185 + 44, 10, PLAYER3_W, PLAYER3_H);

    /* female */
    sprites.player[1][0][0] = sprite_grab(100 + 44, 11, PLAYER1_W, PLAYER1_H);
    sprites.player[1][0][1] = sprite_grab(140 + 44, 10, PLAYER1_W, PLAYER1_H);

    sprites.player[1][1][0] = sprite_grab(98 + 44, 80, PLAYER2_W, PLAYER2_H);
    sprites.player[1][1][1] = sprite_grab(145 + 44, 80, PLAYER2_W, PLAYER2_H);

    sprites.player[1][2][0] = sprite_grab(240 + 44, 78, PLAYER3_W, PLAYER3_H);
    sprites.player[1][2][1] = sprite_grab(185 + 44, 78, PLAYER3_W, PLAYER3_H);

    /* item */
    sprites.item[ITEM_HEART] = sprite_grab(203 + 45, 155, ITEM_HEART_W, ITEM_HEART_H);
    sprites.item[ITEM_BARRIER] = sprite_grab(243 + 45, 151, ITEM_BARRIER_W, ITEM_BARRIER_H);
    sprites.item[ITEM_TREASURE_CHEST] = sprite_grab(282 + 45, 153, ITEM_TREASURE_CHEST_W, ITEM_TREASURE_CHEST_H);

    /* enemy */
    sprites.enemy[ENEMY_SPEAR] = sprite_grab(52 + 45, 154, ENEMY_SPEAR_W, ENEMY_SPEAR_H);
    sprites.enemy[ENEMY_BOMB] = sprite_grab(84 + 45, 145, ENEMY_BOMB_W, ENEMY_BOMB_H);
    sprites.enemy[ENEMY_FIREBALL] = sprite_grab(131 + 45, 153, ENEMY_FIREBALL_W, ENEMY_FIREBALL_H);
    sprites.enemy[ENEMY_HOMING] = sprite_grab(165 + 45, 151, ENEMY_HOMING_W, ENEMY_HOMING_H);
    /* fx */
    sprites.enemy2_bomb[0] = sprite_grab(6 + 45, 194, 38, 40);
    sprites.enemy2_bomb[1] = sprite_grab(46 + 45, 192, 54, 42);
    sprites.enemy2_bomb[2] = sprite_grab(102 + 45, 190, 40, 44);
    sprites.enemy2_bomb[3] = sprite_grab(146 + 45, 187, 33, 47);
    sprites.enemy2_bomb[4] = sprite_grab(182 + 45, 187, 34, 47);

    sprites.enemy4_bomb[0] = sprite_grab(228 + 45, 195, 40, 36);
    sprites.enemy4_bomb[1] = sprite_grab(273 + 45, 197, 36, 35);
    sprites.enemy4_bomb[2] = sprite_grab(9 + 45, 246, 34, 30);
    sprites.enemy4_bomb[3] = sprite_grab(50 + 45, 246, 35, 37);
    sprites.enemy4_bomb[4] = sprite_grab(90 + 45, 240, 30, 47);

    /* fx 보물상자_챌린지 */
    sprites.chest_challenge[0] = sprite_grab(168, 256, 32, 22);
    sprites.chest_challenge[1] = sprite_grab(7, 292, 54, 47);
    sprites.chest_challenge[2] = sprite_grab(14, 140, 77, 53);
    sprites.chest_challenge[3] = sprite_grab(320, 237, 77, 53);
    sprites.chest_challenge[4] = sprite_grab(60, 320, 33, 23);
    /* fx 보물상자_보스 */
    sprites.chest_boss[0] = sprite_grab(65, 284, 57, 35);
    sprites.chest_boss[1] = sprite_grab(122, 300, 57, 88);
    sprites.chest_boss[2] = sprite_grab(208, 246, 105, 79);
    sprites.chest_boss[3] = sprite_grab(320, 300, 70, 44);

    /*레이저*/
    sprites._sheet = al_load_bitmap("razer_IMG.png");

    sprites.enemy_razer = sprite_grab(121, 12, ENEMY_RAZER_W, ENEMY_RAZER_H);

    sprites.razer_before_fx = sprite_grab(125, 85, 710, 40);

    sprites.razer_fx[0] = sprite_grab(145, 145, 73, 77);
    sprites.razer_fx[1] = sprite_grab(144, 240, 163, 83);
    sprites.razer_fx[2] = sprite_grab(342, 232, 366, 96);

    sprites.razer_after_fx = sprite_grab(149, 385, 228, 79);
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

    for (int i = 0; i < ENEMY2_FX_FRAMES; i++) {
        if (sprites.enemy2_bomb[i]) {
            al_destroy_bitmap(sprites.enemy2_bomb[i]);
            sprites.enemy2_bomb[i] = NULL;
        }
    }

    for (int i = 0; i < ENEMY4_FX_FRAMES; i++) {
        if (sprites.enemy4_bomb[i]) {
            al_destroy_bitmap(sprites.enemy4_bomb[i]);
            sprites.enemy4_bomb[i] = NULL;
        }
    }

    if (sprites.enemy_razer) {
        al_destroy_bitmap(sprites.enemy_razer);
        sprites.enemy_razer = NULL;
    }

    if (sprites.razer_before_fx) {
        al_destroy_bitmap(sprites.razer_before_fx);
        sprites.razer_before_fx = NULL;
    }

    for (int i = 0; i < ENEMY_RAZER_FRAMES; i++) {
        if (sprites.razer_fx[i]) {
            al_destroy_bitmap(sprites.razer_fx[i]);
            sprites.razer_fx[i] = NULL;
        }
    }

    for (int i = 0; i < CHEST_CHALLENGE_FRAMES; i++) {
        if (sprites.chest_challenge[i]) {
            al_destroy_bitmap(sprites.chest_challenge[i]);
            sprites.chest_challenge[i] = NULL;
        }
    }

    for (int i = 0; i < CHEST_BOSS_FRAMES; i++) {
        if (sprites.chest_boss[i]) {
            al_destroy_bitmap(sprites.chest_boss[i]);
            sprites.chest_boss[i] = NULL;
        }
    }

    if (sprites.razer_after_fx) {
        al_destroy_bitmap(sprites.razer_after_fx);
        sprites.razer_after_fx = NULL;
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
    sprites.player[0][0][0] = sprite_grab(5+52, 10, PLAYER1_W, PLAYER1_H);
    sprites.player[0][0][1] = sprite_grab(48+52, 10, PLAYER1_W, PLAYER1_H);

    sprites.player[0][1][0] = sprite_grab(10+52, 82, PLAYER2_W, PLAYER2_H);
    sprites.player[0][1][1] = sprite_grab(45+52, 78, PLAYER2_W, PLAYER2_H);

    sprites.player[0][2][0] = sprite_grab(178+52, 80, PLAYER3_W, PLAYER3_H);
    sprites.player[0][2][1] = sprite_grab(230+52, 80, PLAYER3_W, PLAYER3_H);

    //여자
    sprites.player[1][0][0] = sprite_grab(95+52, 10, PLAYER1_W, PLAYER1_H);
    sprites.player[1][0][1] = sprite_grab(140+52, 8, PLAYER1_W, PLAYER1_H);

    sprites.player[1][1][0] = sprite_grab(92+52, 81, PLAYER2_W, PLAYER2_H);
    sprites.player[1][1][1] = sprite_grab(138+52, 80, PLAYER2_W, PLAYER2_H);

    sprites.player[1][2][0] = sprite_grab(178+52, 5, PLAYER3_W, PLAYER3_H);
    sprites.player[1][2][1] = sprite_grab(228+52, 5, PLAYER3_W, PLAYER3_H);

    // 아이템 (하트, 베리어, 보물 순)
    sprites.item[0] = sprite_grab(4+52, 200, ITEM1_W, ITEM1_H);
    sprites.item[1] = sprite_grab(52+52, 196, ITEM2_W, ITEM2_H);
    sprites.item[2] = sprite_grab(10+52, 155, ITEM3_W, ITEM3_H);

    // 적
    sprites.enemy[0] = sprite_grab(67+52, 155, ENEMY_DAGGER_W, ENEMY_DAGGER_H);
    sprites.enemy[1] = sprite_grab(105+52, 145, ENEMY_BOMB_W, ENEMY_BOMB_H);
    sprites.enemy[2] = sprite_grab(167+52, 154, ENEMY_FIREBALL_W, ENEMY_FIREBALL_H);
    sprites.enemy[3] = sprite_grab(212+52, 148, ENEMY_HOMING_W, ENEMY_HOMING_H);
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