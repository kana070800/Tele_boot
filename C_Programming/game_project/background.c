#include "game.h"


extern Rank ranks[11];
extern int chest_cnt;

void background(int n)
{/*
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return;
    }*/
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
    al_draw_scaled_bitmap(image, 0, 0, img_width, img_height, 0, 0, screen_width, screen_height, 0);
    al_flip_display();
    al_destroy_bitmap(image);

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
	float now_total = (float)(frame / 60) + (chest_cnt * 5.0f);
	strcpy(ranks[count].name, "test");
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
			fprintf(fp, "%s %.1f\n", ranks[i].name, ranks[i].time);
		fclose(fp);
	}
}
/*
void score_draw()
{
	al_draw_text(font, al_map_rgb(1, 1, 1), BUFFER_W / 2, 50, ALLEGRO_ALIGN_CENTER, "--- RANKING ---");

	for (int i = 0; i < 10; i++)
	{
		if (ranks[i].time <= 0) continue;

		float x = BUFFER_W / 2;
		float y = 100 + (i * 40);

		al_draw_textf(
			font,
			al_map_rgb(1, 1, 1),
			x, y,
			ALLEGRO_ALIGN_CENTER,
			"%d.  %-16s  %.1f",
			i + 1, ranks[i].name, ranks[i].time
		);
	}
}*/




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