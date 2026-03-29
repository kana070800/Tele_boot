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
extern ALLEGRO_BITMAP* MAP[6];
extern int flag_mode;
extern DORO_s doro;

void map_init() {
    for (int i = 0; i < 6; ++i) {
        char filename[256];
        snprintf(filename, sizeof(filename), "%d.png", i);
        MAP[i] = al_load_bitmap(filename);

        if (!MAP[i]) {
            printf("couldn't load images : %s\n", filename);
            return;
        }
    }
}

void background(int n)
{
    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(MAP[n]);
    float img_height = al_get_bitmap_height(MAP[n]);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(MAP[n], 0, 0, img_width, img_height, 0, 0, screen_width, screen_height, 0);
    al_flip_display();
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
	strcpy(ranks[count].name, "test111");
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
    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 110 + ITEM_TREASURE_CHEST_W + 5, 100, 0, "%ld", chest_cnt);
    //stage

    float bar_width = 300.0f;  // 전체 너비
    float bar_height = 15.0f;  // 높이
    float x = (BUFFER_W - bar_width) / 2.0f; // 화면 중앙 정렬
    float y = 20.0f;           // 상단 여백

    if (flag_mode == 2) {
        al_draw_textf(font_l, al_map_rgb_f(1, 0, 0), 530, 100, 0, "DORO");
        al_draw_filled_rectangle(200, 170, 200 + 200 * 4, 180, al_map_rgb(0, 0, 0));
        al_draw_filled_rectangle(200, 170, 200 + doro.hp*4, 180, al_map_rgb(200, 0, 0));
    }
    else
        al_draw_textf(font_l, al_map_rgb_f(1, 0, 0), 530, 100, 0, "Stage %d", stage);
    int spacing = ITEM_HEART_W + 5;
    for (int i = 0; i < p.hp; i++)
        al_draw_bitmap(sprites.item[0], 100 + (i * spacing), 30, 0);

    al_draw_bitmap(sprites.item[2], 60 + ITEM_TREASURE_CHEST_W + 5, 100, 0);
    
    //프로필 파일 추가 필요
    //al_draw_bitmap(??????, 60 + 5, 5, 0);


}


//--------------------------------

/*
void background(int n)
{
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return;
    }
    char filename[256];
    snprintf(filename, sizeof(filename), "%d.png", n);
    ALLEGRO_BITMAP* image = al_load_bitmap(filename);

    if (!image) {
        printf("couldn't load images : %s\n", filename);
        return;
    }
    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(image);
    float img_height = al_get_bitmap_height(image);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_init_primitives_addon();

    al_draw_scaled_bitmap(image, 0, 0, img_width, img_height, 0, 0, screen_width, screen_height, 0);

    if ((n == 1) || (n == 2) || (n == 3)) {
        al_draw_filled_rectangle(200, 200, 900, 600, al_map_rgb(0, 0, 0));
    }
    ALLEGRO_BITMAP* ingame_male = al_load_bitmap("ingame_male.png");
    if (!ingame_male) {
        printf("couldn't load character image\n");
        al_destroy_bitmap(image);
        return;
    }

    al_draw_scaled_bitmap(ingame_male, 0, 0, al_get_bitmap_width(ingame_male), al_get_bitmap_height(ingame_male), 0, 0, 150, 150, 0);
    al_flip_display();
    //al_destroy_bitmap(image);
}
*/






/*
int main() {
    if (!al_init()) return 1;
    if (!al_init_image_addon()) return 1;
    ALLEGRO_DISPLAY* disp = al_create_display(1200, 900);
    if (!disp) return 1;
    background(1);
    al_rest(20.0);
    al_destroy_display(disp);
    return 0;
}*/