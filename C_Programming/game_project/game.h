#ifndef _GAME_H_
#define _GAME_H_
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#define MAX_ENEMIES 200
#define MAX_ITEMS   8
#define MAX_RANK    10

#define BUFFER_W 1200
#define BUFFER_H 900

#define DISP_SCALE 1
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

/* -------------------- game state -------------------- */

typedef enum {
    STATE_MENU,
    STATE_MODE_SELECT,
    STATE_GENDER_SELECT,
    STATE_PLAYING,
    STATE_INPUT_NAME,
    STATE_RANKING,
    STATE_GAMEOVER,
    STATE_VICTORY
} GAME_STATE;

typedef enum {
    MODE_STORY,
    MODE_CHALLENGE,
    MODE_BOSS_ONLY
} GAME_MODE;

/* -------------------- enemy / item types -------------------- */

typedef enum {
    ENEMY_SPEAR,
    ENEMY_BOMB,
    ENEMY_FIREBALL,
    ENEMY_HOMING,
    ENEMY_TYPE_N
} ENEMY_TYPE;

typedef enum {
    ITEM_HEART,
    ITEM_BARRIER,
    ITEM_TREASURE_CHEST,
    ITEM_TYPE_N
} ITEM_TYPE;

/* -------------------- size tables -------------------- */

extern const int PLAYER_W[3];
extern const int PLAYER_H[3];

extern const int ITEM_W[ITEM_TYPE_N];
extern const int ITEM_H[ITEM_TYPE_N];

extern const int ENEMY_W[ENEMY_TYPE_N];
extern const int ENEMY_H[ENEMY_TYPE_N];

#define PLAYER1_W  (PLAYER_W[0])
#define PLAYER1_H  (PLAYER_H[0])
#define PLAYER2_W  (PLAYER_W[1])
#define PLAYER2_H  (PLAYER_H[1])
#define PLAYER3_W  (PLAYER_W[2])
#define PLAYER3_H  (PLAYER_H[2])

#define ITEM_HEART_W           (ITEM_W[ITEM_HEART])
#define ITEM_HEART_H           (ITEM_H[ITEM_HEART])
#define ITEM_BARRIER_W         (ITEM_W[ITEM_BARRIER])
#define ITEM_BARRIER_H         (ITEM_H[ITEM_BARRIER])
#define ITEM_TREASURE_CHEST_W  (ITEM_W[ITEM_TREASURE_CHEST])
#define ITEM_TREASURE_CHEST_H  (ITEM_H[ITEM_TREASURE_CHEST])

#define ENEMY_SPEAR_W      (ENEMY_W[ENEMY_SPEAR])
#define ENEMY_SPEAR_H      (ENEMY_H[ENEMY_SPEAR])
#define ENEMY_BOMB_W       (ENEMY_W[ENEMY_BOMB])
#define ENEMY_BOMB_H       (ENEMY_H[ENEMY_BOMB])
#define ENEMY_FIREBALL_W   (ENEMY_W[ENEMY_FIREBALL])
#define ENEMY_FIREBALL_H   (ENEMY_H[ENEMY_FIREBALL])
#define ENEMY_HOMING_W     (ENEMY_W[ENEMY_HOMING])
#define ENEMY_HOMING_H     (ENEMY_H[ENEMY_HOMING])
/*
// 게임의 현재 흐름을 제어하는 상태 (메뉴, 게임 중, 결과창 등)
typedef enum {
    STATE_MENU, STATE_MODE_SELECT, STATE_GENDER_SELECT,
    STATE_PLAYING, STATE_INPUT_NAME, STATE_RANKING,
    STATE_GAMEOVER, STATE_VICTORY
} GAME_STATE;

// 게임 모드 설정
typedef enum {
    MODE_STORY,      // 스토리 모드
    MODE_CHALLENGE,  // 무한/도전 모드
    MODE_BOSS_ONLY   // 보스전만 진행하는 모드
} GAME_MODE;

// 적의 종류
typedef enum {
    ENEMY_SPEAR,     // 창병 (직선 공격 등)
    ENEMY_BOMB,      // 폭탄병 (범위 공격)
    ENEMY_FIREBALL,  // 화염구
    ENEMY_HOMING,    // 추적탄 (플레이어를 쫓아옴)
    ENEMY_TYPE_N      // 적의 수
    //ENEMY_BOSS_SHOT  // 보스가 발사하는 탄환
} ENEMY_TYPE;

// 아이템의 종류
typedef enum {
    ITEM_HEART,                 // 체력 회복
    ITEM_BARRIER,               // 방어막 생성
    ITEM_TREASURE_CHEST_TIME    // 보물상자 혹은 시간 관련 아이템
} ITEM_TYPE;
*/
// 랭킹 정보 (이름과 클리어 타임)
typedef struct { char name[16]; float time; } Rank;
Rank rank;

// 방향 정의
typedef enum {
    DIR_LEFT = 0,
    DIR_RIGHT = 1
} PLAYER_DIR;

// 상태 정의
typedef enum {
    STATE_NORMAL = 0,
    STATE_BARRIER = 1
} PLAYER_STATE;

// 플레이어 정보
typedef struct {
    float x, y;
    int hp, gender;     // 1: 남, 2: 여
    int inv_timer;
    bool barrier;
    int barrier_timer;

    PLAYER_DIR last_dir; // 마지막 누른 키 저장
} Player;

// 적 정보
typedef struct {
    float x, y;          // 위치 좌표
    float dx, dy;        // 이동 속도 및 방향 (델타 값)
    ENEMY_TYPE type;     // 적 종류
    int timer;           // 패턴용 타이머
    int frame;
    bool active;         // 현재 화면 존재 여부 (활성화 상태)
} Enemy;


// 아이템 정보
typedef struct {
    float x, y;          // 위치 좌표
    ITEM_TYPE type;      // 아이템 종류
    int timer;           // 소멸 전 지속 시간 등
    bool active;         // 활성화 상태
} Item;


typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;

    // player (성별, 상태, 좌우)
    ALLEGRO_BITMAP* player[2][3][2];

    // 아이템
    ALLEGRO_BITMAP* item[3];

    // 적
    ALLEGRO_BITMAP* enemy[4];
} SPRITES;

// 메뉴 함수 선언
//void store_filed();
//void cal_score();
void background(int);

// player & item 함수 선언
void pi_init();
void player_update();
void item_update();
void player_draw();
void item_draw();

// enemy 함수 선언
void enemy1_init();
void enemy1_update();
void enemy1_draw();

// hud 함수 선언
//void hud_init();
//void hud_update();
//void hud_draw();

// 공용체 함수
void must_init(bool test, const char* description);
int between(int lo, int hi);
float between_f(float lo, float hi);
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

void disp_init();
void disp_deinit();
void disp_pre_draw();
void disp_post_draw();

void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h);
void sprites_init();
void sprites_deinit();

void audio_init();
void audio_deinit();

void fx_init();
void fx_add(bool spark, int x, int y);
void fx_update();
void fx_draw();

int __title(ALLEGRO_EVENT_QUEUE * q);
int __end(ALLEGRO_EVENT_QUEUE* q);

#endif