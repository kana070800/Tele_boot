#include "game.h"

GAME_STATE state = STATE_MENU;  // 초기 상태는 메뉴 화면
GAME_MODE mode = MODE_STORY;    // 기본 모드는 스토리 모드
const int ITEM_W[] = { 30, 35, 35 };
const int ITEM_H[] = { 30, 35, 24 };
const int PLAYER_W[] = { 25, 40, 50 };
const int PLAYER_H[] = { 55, 50, 60 };
const int ENEMY_W[] = { 25, 43, 28, 44 };
const int ENEMY_H[] = { 25, 47, 30, 44 };
Player p = { 0 };                       // 플레이어 객체 생성
Enemy enemy[MAX_ENEMIES] = { 0 };          // 적 배열 선언
Item it[MAX_ITEMS] = { 0 };             // 아이템 배열 선언
Rank ranks[11] = { 0 };           // 랭킹 배열 선언
SPRITES sprites = { 0 };
int rank_count = 0;
char input_name[16] = { 0 };
int stage = 0;
long frame = 0;
int score = 0;
int chest_cnt = 0;
unsigned char key[ALLEGRO_KEY_MAX] = { 0 };
bool win = false;

ALLEGRO_FONT* font;
ALLEGRO_FONT* font_l;
ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;


// 효과음 자원
ALLEGRO_SAMPLE* snd_hit = NULL; // 피격 시 효과음
ALLEGRO_SAMPLE* snd_die = NULL; // 사망 시 효과음
int flag_mode = 0;

int title(queue) {

    softly_next(0, 0, queue);

    bool done = false;
    ALLEGRO_EVENT event;
    al_flush_event_queue(queue);
    memset(key, 0, sizeof(key));
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_1]) {
                done = true;
                flag_mode = 1;
            }
            if (key[ALLEGRO_KEY_2]) {
                done = true;
                flag_mode = 2;
            }
            if (key[ALLEGRO_KEY_ESCAPE] || key[ALLEGRO_KEY_3]) {
                return 1;
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return 1;
        }

        if (done)
            break;

        keyboard_update(&event);

        if (al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            background(0);  // 첫 타이틀 화면 출력, "enter를 눌러 시작하시오" 같은 문구

            disp_post_draw();
        }
    }
    
    softly_next(0, 1, queue);


    done = false;
    al_flush_event_queue(queue);
    memset(key, 0, sizeof(key));
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_1]) {
                done = true;
                p.gender = 1;
            }
            if (key[ALLEGRO_KEY_2]) {
                done = true;
                p.gender = 2;
            }
            if (key[ALLEGRO_KEY_ESCAPE]) {
                return 1;
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return 1;
        }

        if (done)
            break;

        keyboard_update(&event);

        if (al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //background(xxx);  // 캐릭터 선택화면 추가??
            al_draw_textf(font_l, al_map_rgb_f(1, 1, 1), 400, 400, 0, "1 : male\n 2 : female");

            disp_post_draw();
        }
    }


    return 0;
}

int end(queue) {
    
    softly_next(4, 0, queue);

    cal_score(); // 점수를 계산, 파일로부터 랭킹을 불러와서 정렬

    bool done = false;
    ALLEGRO_EVENT event;
    al_flush_event_queue(queue);
    memset(key, 0, sizeof(key));
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_ENTER]) {
                done = true;
            }
            
            if (key[ALLEGRO_KEY_ESCAPE]) {
                return 1;
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return 1;
        }

        if (done)
            break;

        keyboard_update(&event);

        if (al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            background(4);  //엔딩 화면 출력 + 점수 표시, 이름 입력받기 추가 예정
            al_draw_textf(font_l, al_map_rgb_f(1, 1, 1), 450, 810, 0, "press Enter");
            score_draw();
            disp_post_draw();
        }
    }
    softly_next(4, 1, queue);

    softly_next(5, 0, queue);

    done = false;
    al_flush_event_queue(queue);
    memset(key, 0, sizeof(key));
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_1])
                done = true;
            
            if (key[ALLEGRO_KEY_ESCAPE] || key[ALLEGRO_KEY_2]) {
                return 1;
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return 1;
        }

        if (done)
            break;

        keyboard_update(&event);

        if (al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            background(5);  // 두번째 엔딩 화면 출력 , 입력받은 이름 반영 및 랭킹 표시, 타이틀 돌아가기 or 게임 종료 선택
            disp_post_draw();
        }

    }
    //store_score(); // 변경된 랭킹을 파일에 저장

    softly_next(5, 1, queue);

    return 0;
    

}

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    disp_init();
    //audio_init();

    must_init(al_init_image_addon(), "image");
    sprites_init();
    map_init();

    must_init(al_init_font_addon(), "font");
    must_init(al_init_ttf_addon(), "ttf");
    hud_init();
    must_init(al_init_primitives_addon(), "primitives");

    //must_init(al_install_audio(), "audio");
    //must_init(al_init_acodec_addon(), "audio codecs");
    //must_init(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    keyboard_init();
    enemy1_init();
    //enemy2_init();
    //enemy3_init();

    al_start_timer(timer);

    while (1) {


        if (title(queue))  // if return 1 >> end game
            return 0;


        frame = 0;
        score = 0;

        bool done = false;
        bool redraw = true;
        ALLEGRO_EVENT event;


        stage = 1;
        state = STATE_PLAYING;
        pi_init();

        
        if (flag_mode == 2)
            boss_fight_loop(queue);

        if (flag_mode == 1) {
            softly_next(1, 0, queue);
            //__game_loop();

            while (1)
            {
                al_wait_for_event(queue, &event);

                switch (event.type)
                {
                case ALLEGRO_EVENT_TIMER:
                    enemy1_update();   //적 탄환 정보 업데이트
                    /*
                    if (stage >= 2)
                        enemy2_update();
                    if (stage >= 3)
                        enemy3_update();*/
                    player_update();    //자신 캐릭터
                    item_update();
                    hud_update();     //타이머(프레임기반), 먹은 상자, 스테이지 업데이트

                    if (key[ALLEGRO_KEY_ESCAPE])
                        done = true;

                    redraw = true;
                    frame++;
                    if (!(frame % (60 * 10)))
                        stage++;
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
                    if (stage > 3)
                        background(3); //배경화면 출력, 각 스테이지마다 다르게 출력
                    else
                        background(stage);
                    ///
                    al_draw_filled_rectangle(200, 200, 1000, 800, al_map_rgb(0, 0, 0));
                    ///
                    player_draw();
                    enemy1_draw();
                    /*
                        if (stage >= 2)
                            enemy2_draw();
                        if (stage >= 3)
                            enemy3_draw();*/
                    item_draw();
                    hud_draw(); //시간, 보물상자수, 스테이지 현황 출력
                    // 변경사항 반영, 출력
                    disp_post_draw();
                    redraw = false;
                }

                if (p.hp == 0) { // 꺼지기 직전 무언가
                    break;
                }
            }
            if (stage > 3)
                softly_next(3, 1, queue);
            else
                softly_next(stage, 1, queue);


        }
        if (end(queue)) // if return 1 >> end game
            break;

    }

    sprites_deinit();
    hud_deinit();
    //audio_deinit();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    for (int i = 0; i < 6; ++i)
        al_destroy_bitmap(MAP[i]);
    return 0;
}