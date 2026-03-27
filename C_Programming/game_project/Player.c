#include "game.h"
#if 0

extern const int ITEM_W[];
extern const int ITEM_H[];
extern const int PLAYER_W[];
extern const int PLAYER_H[];
extern const int ENEMY_W[];
extern const int ENEMY_H[];
extern long frame;
extern int stage;
extern int chest_cnt;
extern Item it[MAX_ITEMS];
extern Player p;
extern GAME_STATE state;
extern Enemy en[MAX_ENEMIES];
extern ALLEGRO_SAMPLE* snd_hit;
extern ALLEGRO_SAMPLE* snd_die;
extern GAME_MODE mode;
extern bool key[ALLEGRO_KEY_MAX];
extern SPRITES sprites;

void pi_init()
{
	p.x = BUFFER_W / 2;
	p.y = BUFFER_H - 50;
	p.hp = 3; p.inv_timer = 0;
	p.barrier = false;
	p.barrier_timer = 0;
	frame = 1;
	chest_cnt = 0;

	for (int i = 0; i < MAX_ITEMS; i++)
		it[i].active = false;
}

void player_update()
{
	// 시작 상태 체크
	if (state != STATE_PLAYING)
		return;

	// 타이머 처리
	if (p.inv_timer > 0)
		p.inv_timer--;
	if (p.barrier && --p.barrier_timer <= 0)
		p.barrier = false;

	// 여성 남성 캐릭터 히트박스 같고, 기본, 피격, 배리어마다 크기가 달라짐.
	int current_w, current_h;

	if (p.barrier) {
		current_w = PLAYER3_W; // 배리어 크기
		current_h = PLAYER3_H;
	}
	else if (p.inv_timer > 0) {
		current_w = PLAYER2_W; // 피격 무적 크기
		current_h = PLAYER2_H;
	}
	else {
		current_w = PLAYER1_W; // 기본 크기
		current_h = PLAYER1_H;
	}

	// 적군 충돌 루프 (독립적)
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!en[i].active)
			continue;

		// p.inv_timer == 0일 때만 충돌 판정
		if (p.inv_timer == 0 &&
			collide((int)p.x, (int)p.y, (int)p.x + current_w, (int)p.y + current_h,
				(int)en[i].x, (int)en[i].y, (int)en[i].x + ENEMY_W[en[i].type], (int)en[i].y + ENEMY_H[en[i].type]))
		{
			if (p.barrier)
			{
				p.barrier = false;
				p.barrier_timer = 0;
			}
			else
			{
				p.hp--;
				p.inv_timer = 120;
			}

			en[i].active = false;

			if (p.hp <= 0)
			{
				if (snd_die)
					al_play_sample(snd_die, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				state = (mode == MODE_CHALLENGE) ? STATE_INPUT_NAME : STATE_GAMEOVER;
			}
			else if (snd_hit)
				al_play_sample(snd_hit, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}

	// 아이템 충돌 루프 (독립적)
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (!it[i].active)
			continue;

		// 아이템 타이머 감소 및 소멸
		if (--it[i].timer <= 0)
		{
			it[i].active = false;
			continue;
		}

		// 아이템 충돌 판정
		if (collide((int)p.x, (int)p.y, (int)p.x + current_w, (int)p.y + current_h,
			(int)it[i].x, (int)it[i].y, (int)it[i].x + ITEM_W[it[i].type], (int)it[i].y + ITEM_H[it[i].type]))
		{
			it[i].active = false;
			if (it[i].type == ITEM_HEART && p.hp < 5)
				p.hp++;
			else if (it[i].type == ITEM_BARRIER)
			{
				p.barrier = true;
				p.barrier_timer = 300;
			}
			else if (it[i].type == ITEM_TREASURE_CHEST_TIME)
			{
				chest_cnt++;
			}
		}
	}

	// 플레이어 키보드 입력 및 이동 (루프 밖에서 단 한 번만)
	if (key[ALLEGRO_KEY_UP] && p.y > 0)
		p.y -= 2.5;
	if (key[ALLEGRO_KEY_DOWN] && p.y < BUFFER_H - current_h)
		p.y += 2.5;
	if (key[ALLEGRO_KEY_LEFT] && p.x > 0)
	{
		p.x -= 2.5;
		p.last_dir = DIR_LEFT;
	}
	if (key[ALLEGRO_KEY_RIGHT] && p.x < BUFFER_W - current_w)
	{
		p.x += 2.5;
		p.last_dir = DIR_RIGHT;
	}

	// 경계값 보정
	if (p.x < 0) p.x = 0;
	if (p.y < 0) p.y = 0;
	if (p.x > BUFFER_W - current_w) p.x = (float)BUFFER_W - current_w;
	if (p.y > BUFFER_H - current_h) p.y = (float)BUFFER_H - current_h;
}

void item_update()
{
	// 게임 플레이 중 아니면 종료
	if (state != STATE_PLAYING)
		return;

	// 5초마다 하나씩 아이템 생성
	if (frame % 300 == 0)
	{
		for (int i = 0; i < MAX_ITEMS; i++) if (!it[i].active)
		{
			it[i].x = (float)(50 + rand() % (BUFFER_W - 100));
			it[i].y = (float)(50 + rand() % (BUFFER_H - 100));
			it[i].type = (ITEM_TYPE)(rand() % 3);
			it[i].timer = 300;
			it[i].active = true;

			break;
		}
	}
}

void player_draw()
{
	// 사망했거나 무적 시간 깜빡임 처리
	if (p.hp < 1 || ((p.inv_timer / 2) % 3) == 1)
		return;

	// 성별: 1, 2로 저장되어 있으므로 배열 인덱스(0, 1)로 변환
	int g_idx = p.gender - 1;

	// 상태: 배리어 여부에 따라 0 또는 1
	PLAYER_STATE state = (p.barrier) ? STATE_BARRIER : STATE_NORMAL;

	// 방향: 구조체에 저장된 마지막 방향 사용
	PLAYER_DIR dir = p.last_dir;

	// 그리기 (배열 구조가 sprites.player[2][3][2])
	al_draw_bitmap(sprites.player[g_idx][state][dir], p.x, p.y, 0);
}

void item_draw()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		// 활성화 안 된 아이템 패스
		if (!it[i].active) continue;

		// 현재 아이템의 '타입'을 가져옴 (0, 1, 2 중 하나)
		int type = it[i].type;

		// 타입(인덱스)에 맞는 이미지 선택

		ALLEGRO_BITMAP* s = sprites.item[type];


		if (s)
		{
			// 아이템 사라지기전 깜빡깜빡
			if (it[i].timer > 60 || (it[i].timer / 5) % 2)
				al_draw_bitmap(s, it[i].x, it[i].y, 0);
		}
	}
}
#endif