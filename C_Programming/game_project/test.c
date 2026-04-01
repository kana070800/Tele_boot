
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

ALLEGRO_FONT* font;
long score_display;
unsigned char key[ALLEGRO_KEY_MAX];
long frames;
long score;

typedef struct SHIP
{
    int x, y;
    int shot_timer;
    int lives;
    int respawn_timer;
    int invincible_timer;
} SHIP;
extern SHIP ship;
#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;





void init_draw()
{
    al_draw_text(
        font,
        al_map_rgb_f(1, 1, 1),
        150, 150,
        ALLEGRO_ALIGN_CENTER,
        "start A to start, esc to end"
    );
}

void end_draw()
{
    al_draw_text(
        font,
        al_map_rgb_f(1, 1, 1),
        150, 150,
        ALLEGRO_ALIGN_CENTER,
        "end A to start, esc to end"
    );

    al_draw_text(
        font,
        al_map_rgb_f(1, 0.5, 1),
        150, 200,
        ALLEGRO_ALIGN_CENTER,
        "print score, rank"
    );
}

int __title(queue) {

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
            if (key[ALLEGRO_KEY_A])
                done = true;

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
            init_draw();  //타이틀 화면 출력

            disp_post_draw();
        }
    }
    return 0;
}

int __end(queue) {
    {

        cal_score();

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
                if (key[ALLEGRO_KEY_A])
                    done = true;

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
                end_draw();  //엔딩 화면 출력 + 이름 입력을 받고 랭킹 등록, 출력 

                disp_post_draw();
            }
        }
        return 0;
    }

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

    hud_init();
   
    must_init(al_init_primitives_addon(), "primitives");

    //must_init(al_install_audio(), "audio");
    //must_init(al_init_acodec_addon(), "audio codecs");
    //must_init(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    keyboard_init();
    

    al_start_timer(timer);
    while (1) {


        if (__title(queue))
            return 0;
        
        frames = 0;
        score = 0;

        bool done = false;
        bool redraw = true;
        ALLEGRO_EVENT event;
        

        fx_init();
        shots_init();
        self_init();

        //__game_loop();
        while (1)
        {
            al_wait_for_event(queue, &event);

            switch (event.type)
            {
            case ALLEGRO_EVENT_TIMER:
                fx_update();      //피격, 아이템 획득 시 특수효과
                shots_update();   //적 탄환 정보 업데이트
                self_update();    //자신 캐릭터
                hud_update();     //타이머(프레임기반), 먹은 상자, 스테이지 업데이트

                if (key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                redraw = true;
                frames++;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            }

            if (done)
                break;

            keyboard_update(&event);

            if (redraw && al_is_event_queue_empty(queue))
            {
                disp_pre_draw();
                al_clear_to_color(al_map_rgb(0, 0, 0));
                background(); //배경화면 출력
                shots_draw();   
                fx_draw();      
                self_draw();
                hud_draw(); //시간, 보물상자수, 스테이지 현황 출력
                // 변경사항 반영, 출력
                disp_post_draw();
                redraw = false;
            }

            if (self.lives < 0)
                break;
        }

        if (__end(queue)) // if return 1 >> end game
            break;

    }
    
    sprites_deinit();
    hud_deinit();
    audio_deinit();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}