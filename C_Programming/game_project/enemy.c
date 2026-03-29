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
extern SPRITES sprites;
extern Enemy enemy[MAX_ENEMIES];

/* -------------------- sprite -------------------- */


/* -------------------- object -------------------- */

void obj_init_position(Enemy* obj, int count)
{
    for (int i = 0; i < count; i++)
    {
        Enemy* e = &obj[i];
        ENEMY_TYPE type = (ENEMY_TYPE)(i % ENEMY_TYPE_N);

        e->type = type;
        e->x = (float)(rand() % (BUFFER_W - ENEMY_W[type]));
        e->y = (float)(rand() % (BUFFER_H - ENEMY_H[type]));

        e->dx = (rand() % 2 == 0) ? 2.0f : -2.0f;
        e->dy = (rand() % 2 == 0) ? 2.0f : -2.0f;

        e->timer = 0;
        e->active = true;
    }
}

#define ENEMY_N 10

void enemy1_init()
{
    for (int i = 0; i < ENEMY_N; i++)
        enemy[i].active = false;
}

bool enemy1_add()
{
    for (int i = 0; i < ENEMY_N; i++)
    {
        if (enemy[i].active)
            continue;

        // 위:0, 아래:1, 왼: 2, 오: 3
        int side = rand() % 4;

        switch (side) {
        case 0: // 위
            enemy[i].x = between_f(200.0f, 1000.0f);
            enemy[i].y = 200.0f;
            break;

        case 1: // 아래
            enemy[i].x = between_f(1000.0f, 200.0f);
            enemy[i].y = 800.0f;
            break;

        case 2: // 왼쪽
            enemy[i].x = 200.0f;
            enemy[i].y = between_f(200.0f, 1000.0f);
            break;

        case 3: // 오른쪽
            enemy[i].x = 1000.0f;
            enemy[i].y = between_f(200.0f, 1000.0f);
            break;
        }

        // 중앙 플레이 구역 안쪽 임의의 목표점
        float target_x = between_f(200.0f, 1000.0f);
        float target_y = between_f(200.0f, 750.0f);

        float vx = target_x - enemy[i].x;
        float vy = target_y - enemy[i].y;
        float len = sqrtf(vx * vx + vy * vy);

        if (len == 0.0f)
            len = 1.0f;

        float speed = 4.0f;
        enemy[i].dx = vx / len * speed;
        enemy[i].dy = vy / len * speed;

        enemy[i].frame = 0;
        enemy[i].active = true;

        return true;
    }

    return false;
}

void enemy1_update()
{
    enemy1_add();
    for (int i = 0; i < ENEMY_N; i++)
    {
        if (!enemy[i].active)
            continue;

        enemy[i].x += enemy[i].dx;
        enemy[i].y += enemy[i].dy;

        // 맵 밖으로 나갈 시 사라짐
        if (enemy[i].x < 200.0f || enemy[i].x > 1000.0f ||
            enemy[i].y < 200.0f || enemy[i].y > 800.0f)
        {
            enemy[i].active = false;
            continue;
        }

        enemy[i].frame++;
    }
}


bool enemy1_collide(int x, int y, int w, int h)
{
    for (int i = 0; i < ENEMY_N; i++)
    {
        if (!enemy[i].active)
            continue;

        int sw, sh;

        sw = ENEMY_SPEAR_W;
        sh = ENEMY_SPEAR_H;

        // player와 충돌 시 사라짐
        if (collide(x, y, x + w, y + h, enemy[i].x, enemy[i].y, enemy[i].x + sw, enemy[i].y + sh))
        {
            enemy[i].active = false;
            return true;
        }
    }

    return false;
}

void enemy1_draw()
{
    for (int i = 0; i < ENEMY_N; i++)
    {
        if (!enemy[i].active)
            continue;

        al_draw_bitmap(sprites.enemy[ENEMY_SPEAR], enemy[i].x - ENEMY_SPEAR_W / 2, enemy[i].y - ENEMY_SPEAR_H / 2, 0);
    }
}