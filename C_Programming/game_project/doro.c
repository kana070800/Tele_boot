#include "game.h"

extern unsigned char key[ALLEGRO_KEY_MAX];
extern long frame;
extern Player p;
float sw, sh;
extern bool win;
extern Enemy enemy2[ENEMY2_N];
extern SPRITES sprites;
extern int chest_cnt;

DORO_s doro;

#define ALIEN_SHOT_W 12
#define ALIEN_SHOT_H 12
typedef struct SHOT
{
    int x, y, dx, dy;
    bool active;
} SHOT;

#define SHOTS_N 50
SHOT shots[SHOTS_N];

typedef enum {
    DORO_IDLE,      // 대기 (포인트 지정 전)
    DORO_MOVE_WAIT, // 이동 전 1초 대기
    DORO_MOVING,    // 3초 동안 이동 중
    DORO_ATTACK_PREP, // 공격 전 1초 대기 (공격1 or 2 결정)
    DORO_ATTACKING,  // 공격 수행
    DORO_HIT
} DORO_STATE;

typedef enum {
    RAZER_WARNING,  // fx 2 (경고)
    RAZER_SHOOTING, // fx 3 (발사 준비)
    RAZER_FULL      // 완전한 레이저 (enemy5)
} RAZER_STATE;
int flag_l = RAZER_WARNING;
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


        float tmp_x = (doro.x + 80 - p.x) * (doro.x + 80 - p.x);
        float tmp_y = (doro.y + 50 - p.y) * (doro.y + 50 - p.y);

        shots[i].dx = sqrt(tmp_x / (tmp_x + tmp_y)) * 5;
        shots[i].dy = sqrt(tmp_y / (tmp_x + tmp_y)) * 5;

        if ((doro.x + 80 - p.x) < 0)
            shots[i].dx = -shots[i].dx;
        if ((doro.y + 50 - p.y) < 0)
            shots[i].dy = -shots[i].dy;

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

        shots[i].x += shots[i].dx;
        shots[i].y += shots[i].dy;

		if ((shots[i].y < 200) || (shots[i].y > 800) || (shots[i].x < 200) || (shots[i].x > 1000))
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

        al_draw_bitmap(sprites.enemy[ENEMY_SPEAR], shots[i].x, shots[i].y, 0);

    }
}
int r_timer = 0;
int razer[3] = { 0, 0, 0 };
void doro_attack_1() {
    r_timer--;
    if (!(r_timer)) {
        switch (flag_l) {
        case RAZER_WARNING:
            flag_l = RAZER_SHOOTING;
            fx_add(2, 200, razer[0] + 30);
            fx_add(2, 200, razer[1] + 30);
            fx_add(2, 200, razer[2] + 30);
            r_timer = 50; // 경고 50프레임 대기
            break;

        case RAZER_SHOOTING:
            flag_l = RAZER_FULL;
            fx_add(3, 200, razer[0] + 55);
            fx_add(3, 200, razer[1] + 55);
            fx_add(3, 200, razer[2] + 55);
            r_timer = 24; // 애니메이션(3장) * 8프레임 = 24프레임 대기
            break;
        case RAZER_FULL:
            // 여기서 flag_l = RAZER_WARNING; 로 돌려도 되지만 다음 턴에 초기화됨
            al_play_sample(enemy_explode[4], 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            enemy5_add(200, razer[0]);
            enemy5_add(200, razer[1]);
            enemy5_add(200, razer[2]);
            r_timer = 50; // 완전 발사 유지 시간
            break;
        }
    }
    return;
}

void doro_attack_2() {
    for (int i = 0; i < 3; i++){
        enemy4_add();
    }
    return;
}

void doro_attack_draw() {
    enemy3_draw();
    enemy4_draw();
    enemy5_draw();
    return;
}



void doro_init() {

    doro.x = 500;
    doro.y = 200;
    doro.hp = 200;
    doro.timer = 60; //1초 후 동작
	doro.state = DORO_IDLE;

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

    if ((doro.state == DORO_ATTACKING) || (doro.state == DORO_ATTACK_PREP)) {
        if (doro.attack == 1)
            al_draw_scaled_bitmap(DORO_img.attack[0], 0, 0, 133, 180, doro.x, doro.y, 133, 180, 0);
        else if (doro.attack == 2)
            al_draw_scaled_bitmap(DORO_img.attack[1], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);
        else 
			al_draw_scaled_bitmap(DORO_img.move[0], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);
    }
    else if (doro.state == DORO_MOVING) {
        if ((frame % 7) > 3)
            al_draw_scaled_bitmap(DORO_img.move[1], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);
        else
            al_draw_scaled_bitmap(DORO_img.move[0], 0, 0, 170, 135, doro.x, doro.y, 170, 135, 0);
    }
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
            doro.timer = 30;        // 정지 후 1초 대기
            doro.state = DORO_ATTACK_PREP;
        }
        break;

    case DORO_ATTACK_PREP:
        if (doro.timer <= 0) {
            // 공격 1 또는 2 결정
            doro.attack = rand() % 2 + 1;
            if (doro.attack == 1)
            {
                for (int i = 0; i < 3; ++i)
                    razer[i] = between_f(MAP_TOP, MAP_BOTTOM - ENEMY5_W);
                // 50(경고) + 24(발사준비, 3프레임*8) + 50(발사유지) = 총 124프레임
                doro.timer = 124;
                r_timer = 1;
                flag_l = RAZER_WARNING; // 시작 상태 초기화
            }
            else {
                doro.timer = 50;
            }
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
        if (doro.attack == 1) {
            doro_attack_1();
        }
        if (doro.attack == 2) {
            doro_attack_2();
        }
        if (doro.timer <= 0) {
            doro.attack = 0;
            doro.timer = 5;
            doro.state = DORO_IDLE;
        }
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
                if (doro.state != DORO_ATTACKING) {
                    doro.state = DORO_HIT;
                    doro.timer = 5;
                }
            }
        }
    }
}


void boss_fight_loop(ALLEGRO_EVENT_QUEUE* queue) {
    shots_init();
    doro_init();
    enemies_init();
    fx_init();
    bool done= false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    int s_duty = 50;

    softly_next(3, 0, queue);
    while (1)
    {
        win = false;
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            doro_update();
            
            if (!(frame % s_duty))
                shots_add(p.x, p.y);
            shots_update();
            if (chest_cnt < 5)
                s_duty = 50 - 10*chest_cnt;
            item_update();
            
            
            if (frame % 50 == 0) {
                al_play_sample(enemy_explode[3], 0.75, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                enemy3_add(doro.x + 85, doro.y + 70);
            }
            enemy3_update();
            enemy4_updatex(p.x, p.y);
            enemy5_update();
            fx_update();
            player_update();    //자신 캐릭터
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
            
            fx_draw();
            player_draw();
            shots_draw();
            addprofile();
            doro_attack_draw();
            doro_draw();
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



