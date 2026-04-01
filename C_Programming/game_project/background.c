#include "game.h"


extern Rank ranks[11];
extern int chest_cnt;
extern int frame;
extern int score;
extern int stage;
extern Player p;
extern SPRITES sprites;
extern ALLEGRO_FONT* font;
extern ALLEGRO_FONT* font_l;
extern ALLEGRO_BITMAP* MAP[10];
extern int flag_mode;
extern DORO_s doro;

extern char input_name[16];
void score_draw_at(float x, float start_y, float spacing);
void score_draw_pre_update(float x, float start_y, float spacing);


void map_init() {
    for (int i = 0; i < 10; ++i) {
        char filename[256];
        snprintf(filename, sizeof(filename), "%d.png", i);
        MAP[i] = al_load_bitmap(filename);

        if (!MAP[i]) {
            printf("couldn't load images : %s\n", filename);
            return;
        }
    }
}

void addprofile() {

    if (p.gender == 1) {
        al_draw_scaled_bitmap(MAP[6], 0, 0, al_get_bitmap_width(MAP[6]), al_get_bitmap_height(MAP[6]), 0, 0, 180, 180, 0);
    }

    if (p.gender == 2) {
        al_draw_scaled_bitmap(MAP[7], 0, 0, al_get_bitmap_width(MAP[7]), al_get_bitmap_height(MAP[7]), 0, 0, 180, 180, 0);
    }
}
/*
void background(int n)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(MAP[n]);
    float img_height = al_get_bitmap_height(MAP[n]);

    al_draw_scaled_bitmap(MAP[n], 0, 0, img_width, img_height, 0, 0, screen_width, screen_height, 0);

    // 4번 화면: 이름 입력 및 실시간 랭킹 (파일 기반)
    if (n == 4) {
        score_draw_pre_update(660, 260, 48.8);
        al_draw_text(font_l, al_map_rgb(255, 255, 255), 600, 170, ALLEGRO_ALIGN_CENTER, "ENTER YOUR NAME");
        al_draw_textf(font_l, al_map_rgb(255, 255, 0), 600, 760, ALLEGRO_ALIGN_CENTER, "%s_", input_name);
    }

    // 5번 화면: 최종 결과창 (메모리 기반)
    if (n == 5) {
        al_draw_text(font_l, al_map_rgb(255, 255, 255), 600, 40, ALLEGRO_ALIGN_CENTER, "- HALL OF FAME -");
        score_draw_at(300, 185, 50); // 여기서 한 번만 출력
    }
}
*/


void background(int n)
{
    static int last_bgm_n = -1; //이전 BGM 번호를 저장하는 정적 변수
    static ALLEGRO_SAMPLE_INSTANCE* current_inst = NULL; //초기화된 샘플 인스턴스 포인터
    static ALLEGRO_SAMPLE* current_sample = NULL; // 현재 로드된 샘플 포인터

    if (n != last_bgm_n) {
        // 기존 곡이 있다면 정지 및 메모리 해제
        if (current_inst) {
            al_stop_sample_instance(current_inst);
            al_destroy_sample_instance(current_inst);
        }
        if (current_sample) {
            al_destroy_sample(current_sample);
        }

        // 새로운 곡 로드
        char bgm_name[32];
        sprintf(bgm_name, "bgm_%d.ogg", n);

        current_sample = al_load_sample(bgm_name);

        if (current_sample) {
            current_inst = al_create_sample_instance(current_sample);
            al_set_sample_instance_playmode(current_inst, ALLEGRO_PLAYMODE_LOOP);
            al_attach_sample_instance_to_mixer(current_inst, al_get_default_mixer());
            al_play_sample_instance(current_inst);
            printf("BGM %d 재생 시작\n", n); // 디버깅용 로그
        }
        else {
            printf("BGM %s 로드 실패! 경로를 확인하세요.\n", bgm_name);
        }

        last_bgm_n = n;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));

    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(MAP[n]);
    float img_height = al_get_bitmap_height(MAP[n]);

    al_draw_scaled_bitmap(MAP[n], 0, 0, img_width, img_height, 0, 0, screen_width, screen_height, 0);

    // 4번 화면: 이름 입력 및 실시간 랭킹 (파일 기반)
    if (n == 4) {
        score_draw_pre_update(660, 260, 48.8);
        al_draw_text(font_l, al_map_rgb(255, 255, 255), 600, 170, ALLEGRO_ALIGN_CENTER, "ENTER YOUR NAME");
        al_draw_textf(font_l, al_map_rgb(255, 255, 0), 600, 760, ALLEGRO_ALIGN_CENTER, "%s_", input_name);
    }

    // 5번 화면: 최종 결과창 (메모리 기반)
    if (n == 5) {
        al_draw_text(font_l, al_map_rgb(255, 255, 255), 600, 40, ALLEGRO_ALIGN_CENTER, "- HALL OF FAME -");
        al_draw_text(font, al_map_rgb(255, 255, 255), 225, 148, ALLEGRO_ALIGN_LEFT, "- RANK -");
        score_draw_at(300, 195, 50); // 여기서 한 번만 출력
    }
}

// 파일 데이터 출력 (이름-점수 분리 정렬)
void score_draw_pre_update(float x, float start_y, float spacing)
{
    FILE* fp = fopen("score.txt", "r");
    if (!fp) return;

    Rank temp_ranks[10] = { 0 };
    int count = 0;
    while (count < 10 && fscanf(fp, "%s %f", temp_ranks[count].name, &temp_ranks[count].time) != EOF) {
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count; i++) {
        float y = start_y + (i * spacing);
        al_draw_text(font, al_map_rgb(255, 255, 255), x - 145, y, ALLEGRO_ALIGN_LEFT, temp_ranks[i].name);
        al_draw_textf(font, al_map_rgb(255, 255, 255), x + 122, y, ALLEGRO_ALIGN_RIGHT, "%.1f", temp_ranks[i].time);
    }
}

// 메모리 데이터 출력 (이름-점수 분리 정렬)
void score_draw_at(float x, float start_y, float spacing)
{
    for (int i = 0; i < 10; i++)
    {
        if (ranks[i].time <= 0) continue;
        float y = start_y + (i * spacing);
        al_draw_text(font, al_map_rgb(255, 255, 255), x - 120, y, ALLEGRO_ALIGN_LEFT, ranks[i].name);
        al_draw_textf(font, al_map_rgb(255, 255, 255), x + 120, y, ALLEGRO_ALIGN_RIGHT, "%.1f", ranks[i].time);
    }
}


void softly_next(int next, int flag, ALLEGRO_EVENT_QUEUE* queue) {
    int frames = 0;
    bool done = 0;

    ALLEGRO_EVENT event;
    al_flush_event_queue(queue);
    while (1)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if (frames > 250) {
                    done = true;
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                return;
        }
        if (done)
            break;
        frames += 3;
            if (al_is_event_queue_empty(queue))
            {
                disp_pre_draw();
                al_clear_to_color(al_map_rgb(0, 0, 0));
                background(next);  // flag에 따라 화면의 점진적인 전환
                if (flag == 0)
                    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba(0, 0, 0, 255 - frames));
                if (flag == 1)
                    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba(0, 0, 0, frames - 255));
                disp_post_draw();
            }
        }
}


float total_time = 0;
extern float frame;
extern Rank ranks[11];

void cal_score()
{
	// 기존 데이터 읽기
	FILE* fp = fopen("score.txt", "r");
	int count = 0;
	if (fp != NULL)
	{
		while (count < 10 && fscanf(fp, "%s %f", ranks[count].name, &ranks[count].time) != EOF)
			count++;
		fclose(fp);
	}

	// 현재 점수 계산 및 11번째 칸에 추가
	float now_total = ((float)frame / 60) + (chest_cnt * 5.0f);
	strcpy(ranks[count].name, input_name);
	ranks[count].time = now_total;
	count++;

	// 정렬 (Bubble Sort) - 내림차순
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (ranks[j].time < ranks[j + 1].time)
			{
				Rank temp = ranks[j];
				ranks[j] = ranks[j + 1];
				ranks[j + 1] = temp;
			}
		}
	}

	// 덮어쓰기 (최대 10개만)
	fp = fopen("score.txt", "w");
	if (fp != NULL)
	{
		int save_limit = (count > 10) ? 10 : count;
		for (int i = 0; i < save_limit; i++)
			fprintf(fp, "%s %.2f\n", ranks[i].name, ranks[i].time);
		fclose(fp);
	}
}

void score_draw()
{
	//al_draw_text(font, al_map_rgb(1, 1, 1), BUFFER_W / 2, 50, ALLEGRO_ALIGN_CENTER, "--- RANKING ---");

	for (int i = 0; i < 10; i++)
	{
		if (ranks[i].time <= 0) continue;

		float x = BUFFER_W / 2 + 30;
		float y = 260 + (i * 49);

		al_draw_textf(
			font,
			al_map_rgb(1, 1, 1),
			x, y,
			ALLEGRO_ALIGN_CENTER,
			"%-20s %.1f",
            ranks[i].name, ranks[i].time
		);
	}
}



extern ALLEGRO_FONT* font;
long score_display;

void hud_init()
{
    font = al_load_font("font_1.ttf", 25, 0);
    font_l = al_load_font("font_1.ttf", 40, 0);
    if (!font) {
        // TTF 로드 실패 시 비상용으로 내장 폰트라도 로드
        font = al_create_builtin_font();
        font_l = al_create_builtin_font();
    }
    must_init(font, "font");
    must_init(font_l, "fontl");
    score = 0;
}

void hud_deinit()
{
    al_destroy_font(font);
    al_destroy_font(font_l);
}

void hud_update()
{
    score = frame*5/3;  // 1초
}

void hud_draw()
{   //time display
    al_draw_textf(font,al_map_rgb_f(1, 1, 1),1000, 100,0,"%06ld",score);
    //number of treasure
    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 200 + ITEM_TREASURE_CHEST_W + 5, 100, 0, "%ld", chest_cnt);
    //stage

    float bar_width = 300.0f;  // 전체 너비
    float bar_height = 15.0f;  // 높이
    float x = (BUFFER_W - bar_width) / 2.0f; // 화면 중앙 정렬
    float y = 20.0f;           // 상단 여백

    if (flag_mode == 1) {
        al_draw_textf(font_l, al_map_rgb_f(1, 0, 0), 530, 100, 0, "DORO");
        al_draw_filled_rectangle(200, 170, 200 + 200 * 4, 180, al_map_rgb(0, 0, 0));
        al_draw_filled_rectangle(200, 170, 200 + doro.hp*4, 180, al_map_rgb(200, 0, 0));
    }
    else
        al_draw_textf(font_l, al_map_rgb_f(1, 0, 0), 530, 100, 0, "Stage %d", stage);
    int spacing = ITEM_HEART_W + 5;
    for (int i = 0; i < p.hp; i++)
        al_draw_bitmap(sprites.item[0], 180 + (i * spacing), 30, 0);

    al_draw_bitmap(sprites.item[2], 150 + ITEM_TREASURE_CHEST_W + 5, 100, 0);
    
    //프로필 파일 추가 필요
    //al_draw_bitmap(??????, 60 + 5, 5, 0);


}

