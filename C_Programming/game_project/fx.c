#include "game.h"

#define FX_N 156

FX fx[FX_N];
SPRITES sprites;

void fx_init()
{
    for (int i = 0; i < FX_N; i++)
        fx[i].used = false;
}

void fx_add(int enemy, int x, int y)
{
    for (int i = 0; i < FX_N; i++)
    {
        if (fx[i].used)
            continue;

        fx[i].x = x;
        fx[i].y = y;
        fx[i].frame = 0;
        fx[i].enemy = enemy;
        fx[i].used = true;
        return;
    }
}

void fx_update() {
    for (int i = 0; i < FX_N; i++) {
        if (!fx[i].used) continue;

        fx[i].frame++;

        if ((fx[i].enemy == 0 && (fx[i].frame >= (ENEMY2_FX_FRAMES * 8)))
            || (fx[i].enemy == 1 && (fx[i].frame >= (ENEMY4_FX_FRAMES * 8)))
            || (fx[i].enemy == 2 && (fx[i].frame >= 50)) // 경고 50프레임
            || (fx[i].enemy == 3 && (fx[i].frame >= 24)) // 발사 준비 24프레임
            || (fx[i].enemy == 4 && (fx[i].frame >= 24)) // 잔상 24프레임
            // 보물상자 fx: 이미지 수 * 12틱(재생 속도)
            || (fx[i].enemy == 5 && (fx[i].frame >= (CHEST_CHALLENGE_FRAMES * 12)))
            || (fx[i].enemy == 6 && (fx[i].frame >= (CHEST_BOSS_FRAMES * 12)))
            )
        {
            fx[i].used = false;
        }
    }
}

void fx_draw() {
    for (int i = 0; i < FX_N; i++) {
        if (!fx[i].used) continue;

        // fx 2 (경고) 일 때, 5프레임 주기로 깜빡이게 만듦
        if (fx[i].enemy == 2 && ((fx[i].frame / 5) % 2 == 0))
            continue;

        // 1. 기본적으로 frame_display를 구합니다.
        int frame_display;

        // 보물상자(5, 6)는 12틱마다 1프레임, 나머지는 8틱마다 1프레임
        if (fx[i].enemy == 5 || fx[i].enemy == 6) {
            frame_display = fx[i].frame / 12;
        }
        else {
            frame_display = fx[i].frame / 8;
        }

        // 2. 인덱스 초과 방지 (안전장치)
        if (fx[i].enemy == 3 && frame_display > 2) frame_display = 2; // 레이저 준비 애니메이션은 3장(0,1,2)
        if (fx[i].enemy == 5 && frame_display >= CHEST_CHALLENGE_FRAMES) frame_display = CHEST_CHALLENGE_FRAMES - 1;
        if (fx[i].enemy == 6 && frame_display >= CHEST_BOSS_FRAMES) frame_display = CHEST_BOSS_FRAMES - 1;

        // 3. 이미지 매핑
        ALLEGRO_BITMAP* bmp =
            (fx[i].enemy == 0) ? sprites.enemy2_bomb[frame_display] :
            (fx[i].enemy == 1) ? sprites.enemy4_bomb[frame_display] :
            (fx[i].enemy == 2) ? sprites.razer_before_fx :
            (fx[i].enemy == 3) ? sprites.razer_fx[frame_display] :
            (fx[i].enemy == 4) ? sprites.razer_after_fx :
            (fx[i].enemy == 5) ? sprites.chest_challenge[frame_display] :
            (fx[i].enemy == 6) ? sprites.chest_boss[frame_display] :
            NULL;

        if (bmp) {
            int x;
            int bmp_w = al_get_bitmap_width(bmp);
            int bmp_h = al_get_bitmap_height(bmp);

            // 레이저(2, 3, 4)는 고정 x 좌표에서 발사
            if (fx[i].enemy >= 2 && fx[i].enemy <= 4) {
                x = 200;
            }
            else {
                x = fx[i].x - (bmp_w / 2);
            }
            int y = fx[i].y - (bmp_h / 2);

            // 레이저만 스케일 조정해서 그리기
            if (fx[i].enemy >= 2 && fx[i].enemy <= 4) {
                al_draw_scaled_bitmap(bmp, 0, 0, bmp_w, bmp_h, x, y, 800, ENEMY5_W, 0);
            }
            else {
                al_draw_bitmap(bmp, x, y, 0);
            }
        }
    }
}