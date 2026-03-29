#include "game.h"

extern unsigned char key[ALLEGRO_KEY_MAX];
extern long frame;
extern Player p;
float sw, sh;
extern bool win;

DORO_s doro;

#define ALIEN_SHOT_W 12
#define ALIEN_SHOT_H 12
typedef struct SHOT
{
    int x, y, dx, dy;
    bool active;
} SHOT;

#define SHOTS_N 3
SHOT shots[SHOTS_N];

typedef enum {
    DORO_IDLE,      // 대기 (포인트 지정 전)
    DORO_MOVE_WAIT, // 이동 전 1초 대기
    DORO_MOVING,    // 3초 동안 이동 중
    DORO_ATTACK_PREP, // 공격 전 1초 대기 (공격1 or 2 결정)
    DORO_ATTACKING,  // 공격 수행
    DORO_HIT
} DORO_STATE;

struct SPRITES_D 
{
    ALLEGRO_BITMAP* _sheet;
    ALLEGRO_BITMAP* shot;

    ALLEGRO_BITMAP* hit;
    // state
    ALLEGRO_BITMAP* move[2];

    // attack
    ALLEGRO_BITMAP* attack[2];



    
} DORO_img;





void shots_init()
{
    for (int i = 0; i < SHOTS_N; i++)
        shots[i].active = false;
}

bool shots_add(int x, int y)
{

    for (int i = 0; i < SHOTS_N; i++)
    {
        if (shots[i].active)
            continue;


        shots[i].x = p.x;
        shots[i].y = p.y;

        shots[i].active = true;

        return true;
    }
    return false;
}

void shots_update()
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (!shots[i].active)
            continue;


        shots[i].y -= 5;

        if (shots[i].y < 200)
        {
            shots[i].active = false;
            continue;
        }
    }
}

void shots_draw()
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (!shots[i].active)
            continue;

        al_draw_bitmap(DORO_img.shot, shots[i].x, shots[i].y, 0);

    }
}


void doro_init() {

    doro.x = 500;
    doro.y = 300;
    doro.hp = 200;
    doro.timer = 60; //1초 후 동작

    DORO_img._sheet = al_load_bitmap("doro_m.png");

    if (!DORO_img._sheet) return;

    // 원본 이미지의 크기를 가져옵니다.
    sw = al_get_bitmap_width(DORO_img._sheet);
    sh = al_get_bitmap_height(DORO_img._sheet);

    DORO_img.move[0] = al_create_sub_bitmap(DORO_img._sheet, 14, 17, 150, 140);
    must_init(DORO_img.move[0], "doro");

    DORO_img.move[1] = al_create_sub_bitmap(DORO_img._sheet, 180, 17, 170, 140);
    must_init(DORO_img.move[1], "doro1");

    DORO_img.attack[0] = al_create_sub_bitmap(DORO_img._sheet, 30, 170, 133, 180);
    must_init(DORO_img.attack[0], "doro2");

    DORO_img.attack[1] = al_create_sub_bitmap(DORO_img._sheet, 195, 184, 170, 140);
    must_init(DORO_img.attack[1], "doro3");

    DORO_img.hit = al_create_sub_bitmap(DORO_img._sheet, 370, 20, 170, 140);
    must_init(DORO_img.hit, "doro3");

    DORO_img.shot = al_create_sub_bitmap(DORO_img._sheet, 0, 0, 12, 12);
    must_init(DORO_img.shot, "shot");
}

void doro_draw() {
    //al_draw_bitmap(DORO_img._sheet, doro.x, doro.y, 0);

    sw = al_get_bitmap_width(DORO_img._sheet);
    sh = al_get_bitmap_height(DORO_img._sheet);

    if ((doro.state == DORO_ATTACKING) || (doro.state == DORO_ATTACK_PREP))
        if (doro.attack == 0)
            al_draw_scaled_bitmap(DORO_img.attack[0],0, 0, 133, 180,doro.x, doro.y, 133, 180,0);
        else
            al_draw_scaled_bitmap(DORO_img.attack[1], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);
    else if (doro.state == DORO_MOVING)
        if ((frame % 7) > 3)
            al_draw_scaled_bitmap(DORO_img.move[1], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);
        else
            al_draw_scaled_bitmap(DORO_img.move[0], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);
    else if (doro.state == DORO_HIT)
        al_draw_scaled_bitmap(DORO_img.hit, 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);// 피격시
    else
        al_draw_scaled_bitmap(DORO_img.move[0], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);

}

void doro_update() {

    doro.timer--;

    switch (doro.state) {
    case DORO_IDLE:
        if (doro.timer <= 0) {
            // 1. 무작위 장소지정 (게임 영역 내)
            float target_x = between(200, 1000 - 150);
            float target_y = between(200, 800 - 150);

            // 2. 1초 동안 이동할 속도(dx, dy)
            doro.dx = (target_x - doro.x) / 50.0f;
            doro.dy = (target_y - doro.y) / 50.0f;

            doro.timer = 50;        // 대기
            doro.state = DORO_MOVING;
        }
        break;

    case DORO_MOVING:
        // 이동 수행
        doro.x += doro.dx;
        doro.y += doro.dy;

        if (doro.timer <= 0) {
            doro.timer = 60;        // 정지 후 1초 대기
            doro.state = DORO_ATTACK_PREP;
        }
        break;

    case DORO_ATTACK_PREP:
        if (doro.timer <= 0) {
            // 공격 1 또는 2 결정
            doro.attack = rand() % 2;
            doro.timer = 60;        // 1초 후 공격 수행
            doro.state = DORO_ATTACKING;
        }
        break;
    case DORO_HIT:
        if (doro.timer <= 0) {
            doro.timer = 5;
            doro.state = DORO_IDLE;
        }
        break;
    case DORO_ATTACKING:
        if (doro.attack == 0) {
            //doro_attack_1();
        }
        else {
            //doro_attack_2();
        }

        doro.timer = 30;
        doro.state = DORO_IDLE;
        break;
    }
    //충돌(player)
    if (p.inv_timer == 0 && collide(p.x, p.y, p.x + PLAYER1_W, p.y + PLAYER1_H,
        doro.x, doro.y, doro.x + 150, doro.y + 140))
    {
        if (p.barrier) {
            p.barrier = false;
        }
        else {
            p.hp--;
            p.inv_timer = 120; // 2초 무적
        }
    }
    //충돌(player_shot)
    for (int i = 0; i < SHOTS_N; ++i) {
        if (shots[i].active) {
            if (collide(shots[i].x, shots[i].y, shots[i].x + 12, shots[i].y + 12,
                doro.x, doro.y, doro.x + 150, doro.y + 140))
            {
                doro.hp -= 5;
                shots[i].active = false;
                doro.state = DORO_HIT;
                doro.timer = 5;
            }
        }
    }
}


void boss_fight_loop(ALLEGRO_EVENT_QUEUE* queue) {
    shots_init();
    doro_init();
    bool done= false;
    bool redraw = true;
    ALLEGRO_EVENT event;


    softly_next(3, 0, queue);
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            doro_update();
            player_update();    //자신 캐릭터
            if (!(frame % 50))
                shots_add(p.x, p.y);
            shots_update();
            item_update();
            hud_update();     //타이머(프레임기반), 먹은 상자, 스테이지 업데이트

            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            redraw = true;
            frame++;
            
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        keyboard_update(&event);

        //프레임을 통해 시간 계산하여 스테이지 플래그 반영 >> enum


        if (redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            background(3);
            ///
            al_draw_filled_rectangle(200, 200, 1000, 800, al_map_rgb(0, 0, 0));
            ///
            doro_draw();
            player_draw();
            shots_draw();
            
            item_draw();
            hud_draw(); //시간, 보물상자수, 스테이지 현황 출력
            // 변경사항 반영, 출력
            disp_post_draw();
            redraw = false;
        }

        if (doro.hp <= 0)
            win = true;
        if ((doro.hp <= 0) ||(p.hp <= 0)) { // 꺼지기 직전 무언가
            break;
        }
    }

    softly_next(3, 1, queue);



}
