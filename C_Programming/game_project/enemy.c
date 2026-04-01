#include "game.h"

/* -------------------- size tables -------------------- */

extern const int ITEM_W[];
extern const int ITEM_H[];
extern const int PLAYER_W[];
extern const int PLAYER_H[];
extern const int ENEMY_W[];
extern const int ENEMY_H[];

/* -------------------- global resources -------------------- */

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buffer;
extern Enemy enemy[MAX_ENEMIES];
extern SPRITES sprites;
extern long frame;
extern int flag_mode;
extern DORO_s doro;

#define ENEMY1_AUDIO_CYCLE 50
#define ENEMY5_W 50




/* -------------------- sprite -------------------- */


/* -------------------- enemy -------------------- */
/* 맵 범위 */

Enemy enemy1[ENEMY1_N];
Enemy enemy2[ENEMY2_N];
Enemy enemy3[ENEMY3_N*3];
Enemy enemy4[ENEMY4_N];
Enemy enemy5[ENEMY5_N];

/* -------------------- 공통 -------------------- */
// 맴 범위
bool out_of_map(float x, float y)
{
    return (x < MAP_LEFT || x > MAP_RIGHT || y < MAP_TOP || y > MAP_BOTTOM);
}

// 속도 설정
void set_velocity(float x1, float y1, float x2, float y2, float speed, float* dx, float* dy)
{
    float vx = x2 - x1;
    float vy = y2 - y1;
    float len = sqrtf(vx * vx + vy * vy);

    if (len == 0.0f)
        len = 1.0f;

    *dx = vx / len * speed;
    *dy = vy / len * speed;
}

// 적 스폰 위치
void spawn_enemy(float* x, float* y)
{
    int side = rand() % 4;

    switch (side)
    {
    case 0: // 위
        *x = between_f(MAP_LEFT, MAP_RIGHT);
        *y = MAP_TOP;
        break;

    case 1: // 아래
        *x = between_f(MAP_LEFT, MAP_RIGHT);
        *y = MAP_BOTTOM;
        break;

    case 2: // 왼쪽
        *x = MAP_LEFT;
        *y = between_f(MAP_TOP, MAP_BOTTOM);
        break;

    default: // 오른쪽
        *x = MAP_RIGHT;
        *y = between_f(MAP_TOP, MAP_BOTTOM);
        break;
    }
}

/* -------------------- enemy1 -------------------- */
void enemy1_init(void)
{
    for (int i = 0; i < ENEMY1_N; i++)
        enemy1[i].active = false;
}

bool enemy1_add(void)
{
    for (int i = 0; i < ENEMY1_N; i++)
    {
        if (enemy1[i].active)
            continue;

        spawn_enemy(&enemy1[i].x, &enemy1[i].y);

        float target_x = between_f(MAP_LEFT, MAP_RIGHT);
        float target_y = between_f(MAP_TOP, MAP_BOTTOM);

        set_velocity(
            enemy1[i].x, enemy1[i].y,
            target_x, target_y,
            ENEMY1_SPEED,
            &enemy1[i].dx, &enemy1[i].dy
        );

        enemy1[i].frame = 0;
        enemy1[i].active = true;
        return true;
    }

    return false;
}

void enemy1_update(void)
{
    if (frame % ENEMY1_SPAWN_CYCLE == 0)
        enemy1_add();

    if (frame % ENEMY1_AUDIO_CYCLE == 0) {
        al_play_sample(enemy_explode[2], 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    for (int i = 0; i < ENEMY1_N; i++)
    {
        if (!enemy1[i].active)
            continue;

        enemy1[i].x += enemy1[i].dx;
        enemy1[i].y += enemy1[i].dy;

        if (out_of_map(enemy1[i].x, enemy1[i].y))
        {
            enemy1[i].active = false;
            continue;
        }

        enemy1[i].frame++;
    }
}

bool enemy1_collide(int x, int y, int w, int h)
{
    for (int i = 0; i < ENEMY1_N; i++)
    {
        if (!enemy1[i].active)
            continue;

        int sw = ENEMY_SPEAR_W;
        int sh = ENEMY_SPEAR_H;

        float ex1 = enemy1[i].x - sw / 2.0f;
        float ey1 = enemy1[i].y - sh / 2.0f;
        float ex2 = ex1 + sw;
        float ey2 = ey1 + sh;

        if (collide(x, y, x + w, y + h, ex1, ey1, ex2, ey2))
        {
            enemy1[i].active = false;
            return true;
        }
    }

    return false;
}

void enemy1_draw(void)
{
    for (int i = 0; i < ENEMY1_N; i++)
    {
        if (!enemy1[i].active)
            continue;

        al_draw_bitmap(
            sprites.enemy[ENEMY_SPEAR],
            enemy1[i].x - ENEMY_SPEAR_W / 2,
            enemy1[i].y - ENEMY_SPEAR_H / 2,
            0
        );
    }
}

/* -------------------- enemy2 -------------------- */
void enemy2_init(void)
{
    for (int i = 0; i < ENEMY2_N; i++)
        enemy2[i].active = false;
}

void enemy2_update(void)
{
    int new_quota = (frame % ENEMY2_SPAWN_CYCLE == 0) ? 1 : 0;

    for (int i = 0; i < ENEMY2_N; i++)
    {
        if (!enemy2[i].active)
        {
            if (new_quota > 0)
            {
                enemy2[i].x = between(MAP_LEFT + 10, MAP_RIGHT - ENEMY_W[ENEMY_BOMB] - 10);
                enemy2[i].y = between(MAP_TOP + 10, MAP_BOTTOM - ENEMY_H[ENEMY_BOMB] - 10);
                enemy2[i].timer = ENEMY2_TIMER;
                enemy2[i].blink = 0;
                enemy2[i].frame = 0;
                enemy2[i].active = true;
                new_quota--;
            }
            continue;
        }

        // 60초 남았을 때 blink
        if (enemy2[i].timer <= 60)
            enemy2[i].blink++;

        enemy2[i].timer--;
        enemy2[i].frame++;

        if (enemy2[i].timer <= 0)
        {
            int cx = (int)(enemy2[i].x + ENEMY_W[ENEMY_BOMB] / 2);
            int cy = (int)(enemy2[i].y + ENEMY_H[ENEMY_BOMB] / 2);
            al_play_sample(enemy_explode[0], 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            fx_add(0, cx, cy);
            enemy3_add(cx, cy);
            enemy2[i].active = false;
        }
    }
}

void enemy2_draw(void)
{
    for (int i = 0; i < ENEMY2_N; i++)
    {
        if (!enemy2[i].active)
            continue;

        if (enemy2[i].timer <= 60)
        {
            if ((enemy2[i].blink / 5) % 2 == 0)
                continue;
        }

        al_draw_bitmap(
            sprites.enemy[ENEMY_BOMB],
            enemy2[i].x,
            enemy2[i].y,
            0
        );
    }
}

/* -------------------- enemy3 -------------------- */
static const float enemy3_dir[8][2] = {
    {  1.0f,    0.0f    },
    { -1.0f,    0.0f    },
    {  0.0f,    1.0f    },
    {  0.0f,   -1.0f    },
    {  0.7071f, 0.7071f },
    {  0.7071f,-0.7071f },
    { -0.7071f, 0.7071f },
    { -0.7071f,-0.7071f }
};

void enemy3_init(void)
{
    for (int i = 0; i < ENEMY3_N; i++)
        enemy3[i].active = false;
}

bool enemy3_add(int x, int y)
{
    int created = 0;

    for (int d = 0; d < 8; d++)
    {
        for (int i = 0; i < ENEMY3_N; i++)
        {
            if (enemy3[i].active)
                continue;

            enemy3[i].x = (float)x;
            enemy3[i].y = (float)y;
            enemy3[i].dx = enemy3_dir[d][0] * ENEMY3_SPEED;
            enemy3[i].dy = enemy3_dir[d][1] * ENEMY3_SPEED;
            enemy3[i].frame = 0;
            enemy3[i].active = true;
            created++;
            break;
        }
    }

    return (created == 8);
}

void enemy3_update(void)
{
    for (int i = 0; i < ENEMY3_N; i++)
    {
        if (!enemy3[i].active)
            continue;

        enemy3[i].x += enemy3[i].dx;
        enemy3[i].y += enemy3[i].dy;

        if (out_of_map(enemy3[i].x, enemy3[i].y))
        {
            enemy3[i].active = false;
            continue;
        }

        enemy3[i].frame++;
    }
}

bool enemy3_collide(int x, int y, int w, int h)
{
    for (int i = 0; i < ENEMY3_N; i++)
    {
        if (!enemy3[i].active)
            continue;

        int sw = ENEMY_FIREBALL_W;
        int sh = ENEMY_FIREBALL_H;

        float ex1 = enemy3[i].x - sw / 2.0f;
        float ey1 = enemy3[i].y - sh / 2.0f;
        float ex2 = ex1 + sw;
        float ey2 = ey1 + sh;

        if (collide(x, y, x + w, y + h, ex1, ey1, ex2, ey2))
        {
            enemy3[i].active = false;
            return true;
        }
    }

    return false;
}

void enemy3_draw(void)
{
    for (int i = 0; i < ENEMY3_N; i++)
    {
        if (!enemy3[i].active)
            continue;

        al_draw_bitmap(
            sprites.enemy[ENEMY_FIREBALL],
            enemy3[i].x - ENEMY_FIREBALL_W / 2,
            enemy3[i].y - ENEMY_FIREBALL_H / 2,
            0
        );
    }
}

/* -------------------- enemy4 -------------------- */
void enemy4_init(void)
{
    for (int i = 0; i < ENEMY4_N; i++)
        enemy4[i].active = false;
}

bool enemy4_add(void)
{
    for (int i = 0; i < ENEMY4_N; i++)
    {
        if (enemy4[i].active)
            continue;

        if (flag_mode == 1) {
            enemy4[i].x = doro.x + between_f(-200, 200);
            enemy4[i].y = doro.y + between_f(-200, 200);
        }
        else if (flag_mode == 2) {
            spawn_enemy(&enemy4[i].x, &enemy4[i].y);
        }
        enemy4[i].dx = 0.0f;
        enemy4[i].dy = 0.0f;
        enemy4[i].timer = ENEMY4_TIMER;
        enemy4[i].blink = 0;
        enemy4[i].frame = 0;
        enemy4[i].active = true;
        return true;
    }

    return false;
}

void enemy4_update(float player_x, float player_y)
{
    if (frame % ENEMY4_SPAWN_CYCLE == 0)
        enemy4_add();

    for (int i = 0; i < ENEMY4_N; i++)
    {
        if (!enemy4[i].active)
            continue;

        set_velocity(
            enemy4[i].x, enemy4[i].y,
            player_x, player_y,
            ENEMY4_SPEED,
            &enemy4[i].dx, &enemy4[i].dy
        );

        enemy4[i].x += enemy4[i].dx;
        enemy4[i].y += enemy4[i].dy;

        enemy4[i].timer--;
        enemy4[i].frame++;

        if (enemy4[i].timer <= 60)
            enemy4[i].blink++;

        if (enemy4[i].timer <= 0)
        {
            al_play_sample(enemy_explode[1], 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            fx_add(1, enemy4[i].x, enemy4[i].y);
            enemy4[i].active = false;
            continue;
        }

        if (out_of_map(enemy4[i].x, enemy4[i].y))
        {
            enemy4[i].active = false;
            continue;
        }
    }
}

bool enemy4_collide(int x, int y, int w, int h)
{
    for (int i = 0; i < ENEMY4_N; i++)
    {
        if (!enemy4[i].active)
            continue;

        int sw = ENEMY_HOMING_W;
        int sh = ENEMY_HOMING_H;

        float ex1 = enemy4[i].x - sw / 2.0f;
        float ey1 = enemy4[i].y - sh / 2.0f;
        float ex2 = ex1 + sw;
        float ey2 = ey1 + sh;

        if (collide(x, y, x + w, y + h, ex1, ey1, ex2, ey2))
        {
            enemy4[i].active = false;
            return true;
        }
    }

    return false;
}

void enemy4_updatex(float player_x, float player_y)
{


    for (int i = 0; i < ENEMY4_N; i++)
    {
        if (!enemy4[i].active)
            continue;

        set_velocity(
            enemy4[i].x, enemy4[i].y,
            player_x, player_y,
            ENEMY4_SPEED,
            &enemy4[i].dx, &enemy4[i].dy
        );

        enemy4[i].x += enemy4[i].dx;
        enemy4[i].y += enemy4[i].dy;

        enemy4[i].timer--;
        enemy4[i].frame++;

        if (enemy4[i].timer <= 60)
            enemy4[i].blink++;

        if (enemy4[i].timer <= 0)
        {
            al_play_sample(enemy_explode[1], 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            fx_add(true, enemy4[i].x, enemy4[i].y);
            enemy4[i].active = false;
            continue;
        }

        if (out_of_map(enemy4[i].x, enemy4[i].y))
        {
            enemy4[i].active = false;
            continue;
        }
    }
}

void enemy4_draw(void)
{
    for (int i = 0; i < ENEMY4_N; i++)
    {
        if (!enemy4[i].active)
            continue;

        if (enemy4[i].timer <= 60)
        {
            if ((enemy4[i].blink / 5) % 2 == 0)
                continue;
        }

        al_draw_bitmap(
            sprites.enemy[ENEMY_HOMING],
            enemy4[i].x - ENEMY_HOMING_W / 2,
            enemy4[i].y - ENEMY_HOMING_H / 2,
            0
        );
    }
}



/*-------------------------enemy 5--------------------------------*/
void enemy5_init() {
        for (int i = 0; i < ENEMY5_N; i++)
			enemy5[i].active = false;
}
bool enemy5_add(int x, int y) {

    for (int i = 0; i < ENEMY5_N; i++)
    {
        if (enemy5[i].active)
            continue;

        enemy5[i].x = x;
        enemy5[i].y = y;

        enemy5[i].timer = 50;
        enemy5[i].active = true;
        return true;
    }

    return false;
}

void enemy5_update() {
    for (int i = 0; i < ENEMY5_N; i++)
    {
        if (!enemy5[i].active)
            continue;

        enemy5[i].timer--;

        if (enemy5[i].timer <= 0) {
            // 공격이 끝나면 잔상(fx 4)을 추가
            fx_add(4, enemy5[i].x, enemy5[i].y + 55);
            enemy5[i].active = false;

            continue;
        }
    }
}

bool enemy5_collide(int x, int y, int w, int h)
{
    for (int i = 0; i < ENEMY5_N; i++)
    {
        if (!enemy5[i].active)
            continue;

        int sw = 800;
		int sh = ENEMY5_W;            //레이저의 너비

        float ex1 = enemy5[i].x;
        float ey1 = enemy5[i].y;
        float ex2 = ex1 + sw;
        float ey2 = ey1 + sh;

        if (collide(x, y, x + w, y + h, ex1, ey1, ex2, ey2))
        {
            enemy4[i].active = false;
            return true;
        }
    }

    return false;
}

void enemy5_draw() {
    for (int i = 0; i < ENEMY5_N; i++)
    {
        if (!enemy5[i].active)
            continue;
        
        al_draw_scaled_bitmap(sprites.enemy_razer, 0, 0, ENEMY_RAZER_W, ENEMY_RAZER_H, enemy5[i].x, enemy5[i].y, 800, ENEMY5_W, 0);

    }
}


/* -------------------- 전체 enemy -------------------- */

void enemies_init(void)
{
    enemy1_init();
    enemy2_init();
    enemy3_init();
    enemy4_init();
    enemy5_init();
}

bool enemies_collide(int stage, int x, int y, int w, int h)
{
    if (enemy1_collide(x, y, w, h))
        return true;

    if (enemy3_collide(x, y, w, h))
        return true;

    if (enemy4_collide(x, y, w, h))
        return true;

    if (enemy5_collide(x, y, w, h))
        return true;
    return false;
}