#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))


#if 0

enum { KEY_BASE = 72 };

int main(void)
{
	char* msg[]={"up",NULL, NULL,"left",NULL, "right",NULL,NULL,"down"};
	int c;  //72, 80, 75, 77    0, 8, 3, 5
	char* print_msg = NULL;

	(void)scanf("%d", &c);
	if ((print_msg = msg[c - KEY_BASE]) == NULL)
		return 1;

	printf("%s\n", print_msg);

	return 0;
}
#endif


#if 0
int main() {
    char* msg[4] = { "Down", "Left", "Up", "Right" };
    int c;
    if (_getch() == 224) {
        c = _getch();
        printf("%s\n", msg[(c % 10) % 4]);
    }
    return 0;
}

#endif //연산이 2번, 메모리 적음

#if 0
int main() {
    char* msg[9] = { "UP", 0, 0, "LEFT", 0, "RIGHT", 0, 0, "DOWN" };
    int c;

    if (_getch() == 224) {
        c = _getch();
        printf("%s\n", msg[c - 72]);
    }
    return 0;
}
#endif

#if 0

int main() {

    char* msg[256] = { 0 };

    msg[72] = "Up";
    msg[75] = "Left";
    msg[77] = "Right";
    msg[80] = "Down";

    int c;

    if (_getch() == 224) {
        c = _getch();
        printf("%s\n", msg[c]);
    }

    return 0;
}
#endif //(char *) 의 낭비, 특정 위치에만 값을 저장 및 참조

#if 0
int main(void) {
    char* msg[4] = { "Down","Left","Up","Right" };
    unsigned char map[256] = {
        [80] = 0,
        [75] = 1,
        [72] = 2,
        [77] = 3
    };
    int c;
    if (_getch() == 224) {
        c = _getch();
        printf("%s\n", msg[map[c]]);
    }
    return 0;
}
#endif// 배열 참조연산 추가, 특정 위치에만 값을 저장 및 참조, unsigned char의 낭비 (낭비되는 byte 수가 1/4로 감소)

#if 0
#include <stdio.h>
#include <conio.h>

enum Direction {
    DIR_DOWN,
    DIR_LEFT,
    DIR_UP,
    DIR_RIGHT
};

int main() {

    const char* msg[] = {
        "Down",
        "Left",
        "Up",
        "Right"
    };

    unsigned char map[256] = {
        [80] = DIR_DOWN,
        [75] = DIR_LEFT,
        [72] = DIR_UP,
        [77] = DIR_RIGHT
    };

    int c;

    if (_getch() == 224) {
        c = _getch();
        enum Direction dir = map[c];
        printf("%s\n", msg[dir]);
    }

    return 0;
}
#endif // 기존 방법에 enum 활용

#if 0
typedef char CARR10[10];
typedef CARR10* CARR10_P;
typedef int (*I_FP_PI)(CARR10_P, int);

int printAry(CARR10_P ary, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%s ", ary[i]);
    }
    printf("\n");
}

int main(void) {
    CARR10 fruit[] = {"apple", "melon", "cherry"};
    I_FP_PI fn;

    fn = printAry;
    fn(fruit, sizeof(fruit) / sizeof(fruit[0]));

    return 0;
}
#endif

#if 0

#define SOUND_DEVICE_TYPE 1

int main(void) {

#if !SOUND_DEVICE_TYPE
    printf("사운드 장치를 사용하지 않음\n");
#else
#error CODE 10 : Unknown Device!
#endif

    printf("사운드 모드 = %d\n", SOUND_DEVICE_TYPE);

    return 0;
}
#endif

#if 0

#define Assert(x) { \
    if ((x) >= 4) printf("Range error : %s, %d\n", __FILE__, __LINE__); \
}

int main(void) {
    int a[4] = { 10, 20, 30, 40 };
    int i;

    for (i = 0; i <= 4; ++i) {
#line 100
        Assert(i);
        printf("a[%d] = %d\n", i, a[i]);
    }

    return 0;
}

#endif

#if 0
#define NDEBUG //assert.h 활성화 여부 결정 == 오류 검출 할지 말지 여부를 결정
#include <assert.h>

int main(void) {
    int x;

    printf("\nEnter an integer value: ");
    (void)scanf("%d", &x);

    assert(x >= 0);

    printf("You entered %d.", x);

    return 0;
}
#endif