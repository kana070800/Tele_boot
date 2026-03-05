#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#if 0
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
int main(void)
{
	freopen("score2.txt", "r", stdin); // freopen

	int score[3][4] = {0};
	int* score1 = (int*)(score);									//&score 여부 상관 x >> 주소값은 동일하기에

	for (int i = 0; i < sizeof(score) / sizeof(score[0][0]); i++)   //for (int i = 0; i < SIZE(score) * SIZE(score[0]); i++)
	{
		scanf("%d", score1 + i);									// (void)scanf 형식으로 리턴값 제거 가능
		printf("%d ", *(score1 + i));
	}
	/*
	for (int i = 0; i < SIZE(score); i++)
	{
		for (int j = 0; j < SIZE(score[i]); j++)
		{
			scanf("%d", &score[i][j]);
			printf("%d ", score[i][j]);
		}
		printf("\n");
	}
	*/

	printf("%d", sizeof(score));
	return 0;
}
#endif // multi-dimensional array, pointer arithmetic

#if 0

char* mystrcpy(char* to, const char* from)
{
	char* save = to;
	for (; (*to = *from); ++from, ++to);
	return save;
}

int main(void)
{
	char str1[80] = "tiger";
	char str2[80];
	printf("%s\n", strcpy(str2, str1));
	gets(str1);

	printf("%s\n", str1);
	return 0;
}
#endif // string copy function

#if 0
int sum(int a, int b){
	return a + b;
}

int main(void)
{
	int (*p)(int, int) = sum;
	//int apt = sum; // 정보 손실은 없다, but 함수 포인터로 선언하는 것이 좋다

	printf("%d\n",p(20, 10));


	return 0;
}
#endif // function pointer

#if 0
#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 보안 경고를 무시하고 컴파일을 진행할 때 사용하는 매크로
#include <stdio.h>
int main(void)
{
	unsigned char* temp = (unsigned char*)printf;
	for (int i = 0; i < 10; i++)
		printf("%x\n", *(temp + i));
	printf("%p\n", printf);
	return 0;
}
#endif

#if 0

#define SIZE(a) (sizeof(a)/sizeof((a)[0]))

int func1(int * ap, int n) {
	int total = 0;
	for (int i = 0; i < n; i++)
	{
		total += ap[i];
	}
	return total;
}

int func2(int(*bp)[4], int nr, int nc) {
	int total = 0;
	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++)
			total += bp[i][j];
	}
	return total;
}

int main(void)
{
	int arr[5] = {1,2,3,4,5};
	int brr[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
	printf("%d\n", func1(arr, SIZE(arr)));
	printf("%d\n", func2(brr, SIZE(brr), SIZE(brr[0])));
	return 0;
}
#endif

#if 0
#define SIZE(a) (sizeof(a)/sizeof((a)[0]))
int main(void)
{
	//char* p[3] = { "a", "banana", "cherry" };
	//printf("%c %c %c\n", p[0][2], p[1][1], p[2][2]); //위험
	int arr[3] = {2, 1,2 };
	int brr[6] = {5, 1,2,3,4,5 };
	int crr[4] = {3, 1,2,3};           //배열 요소 크기를 나타내는 값을 첫 요소에 넣는 식으로 길이 정보를 저장
	int* p[3] = { arr, brr, crr };     //
	printf("%d %d %d\n", p[0][2], p[1][1], p[2][2]); //위험
}
#endif

#if 0
int func(int* p, int n)
{
	++p; // 배열등가 포인터 > 주소연산
	printf("%d\n", *p);
	return 0;
}
int main(void)
{
	int arr[5] = { 1,2,3,4,5 };
	func(arr, 5);
}
#endif
//------------------------------------------------
#if 0
#include "mylib.h"
#define SIZE(a) (sizeof(a)/sizeof(a[0]))

int main(void)
{
	int c = 1;
	int ary[5] = { 0 };

	while (c = menu_print()) {
		ary_control(c, ary, SIZE(ary));
	}
	return 0;
}
#endif //switch case 

#if 0
#include "mylib.h"

int main(void)
{
	int num = 1;
	void *cmds[8] = {NULL, scanf_ary , print_ary , findmax_ary, findmin_ary, sum_ary, avg_ary, sort_ary};
	//int (*cmds[8])(int*, int) = { NULL, scanf_ary , print_ary , findmax_ary, findmin_ary, sum_ary, avg_ary, sort_ary };
	int ary[5] = { 0 };
	
	while(num = menu_print()) {
		if ((num > eMENU_EXIT) || (num <= eMENU_MAX_VAL))
			printf("return : %d\n", ((int (*)(int*, int))cmds[num])(ary, 5));
		else
			printf("wrong input");
	}

	return 0;
}

#endif  //function pointer menu   다른 입력일 때 예외처리필요, enum을 통한 인덱스표현

#if 0

#include "mylib.h"
#define SIZE(a) (sizeof(a)/sizeof(a[0]))

typedef enum {
	eEXEC_ARR_LOAD_DATA = 0,
	eEXEC_ARR_PRINT_DATA,
	eEXEC_ARR_GET_MIN,
	eEXEC_ARR_GET_MAX,
	eEXEC_ARR_GET_SUM,
	eEXEC_ARR_GET_AVG,
	eEXEC_ARR_GET_SORT,
	eEXEC_ARR_MAX
} eEXEC_ARR;


typedef struct {
	char* exec_name;
	int (*exec_handle)(int*, int);
} stEXEC_TABLE;

stEXEC_TABLE exec_table[eEXEC_ARR_MAX] = {
	[eEXEC_ARR_LOAD_DATA] = { "Load Data",    scanf_ary },
	[eEXEC_ARR_PRINT_DATA] = { "Print Data",    print_ary },
	[eEXEC_ARR_GET_MIN] = { "Get Min",        findmin_ary },
	[eEXEC_ARR_GET_MAX] = { "Get Max",        findmax_ary },
	[eEXEC_ARR_GET_SUM] = { "Get Sum",        sum_ary },
	[eEXEC_ARR_GET_AVG] = { "Get Avg",        avg_ary },
	[eEXEC_ARR_GET_SORT] = { "Sort Data",    sort_ary }
};

int main(void) {
	int ary[5] = { 0 };
	int exec_input = 0;

	while (1) {
		printf("-------------------------------------\n");
		printf("# Select EXEC Type\n");
		printf("-------------------------------------\n");

		for (size_t iAry = 0; iAry < eEXEC_ARR_MAX; iAry++) {
			printf("\t%zu: - %s\n", iAry + 1, exec_table[iAry].exec_name);
		}
		printf("\t%d: - %s\n", 0, "EXIT");
		printf("-------------------------------------\n");
		printf("Select Menu> ");

		scanf("%d", &exec_input);
		printf("-------------------------------------\n");

		if (exec_input == 0) {
			printf("Exit\n");
			return 0;
		}
		if (exec_input > eEXEC_ARR_MAX || exec_input < 0) {
			fprintf(stderr, "Wrong EXEC NUM");
			return 1;
		}

		printf("# EXEC RESULT:\n\t%d\n", exec_table[exec_input - 1].exec_handle(ary, SIZE(ary)));
		printf("-------------------------------------\n");
	}

	return 0;
}

#endif

#if 0
#include "mylib.h"

typedef enum {
	eMENU_EXIT = 0,
	eMENU_READ,
	eMENU_PRINT,       // 2
	eMENU_FIND_MAX,    // 3
	eMENU_FIND_MIN,    // 4
	eMENU_SUM,         // 5
	eMENU_AVG,         // 6
	eMENU_SORT,         // 7
	eMENU_MAX
} eMENU;                                   //배열 선언시 확장성 보장, 변수 및 타입 검색 용이

int menu() {
	int c;
	printf("MENU\n"
		"1. 데이터 읽기\n"
		"2. 데이터 출력\n"
		"3. 최댓값\n"
		"4. 최솟값\n"
		"5. 합계\n"
		"6. 평균\n"
		"7. 오름차순 정렬\n"
		"0. 종료\n");

	scanf("%d", &c);

	return c;
}

int main(void) {
	int ary[5] = { 0 };
	int c;

	while (c = menu()) {

		switch (c) {
		case eMENU_READ: scanf_ary(ary, 5); break;
		case eMENU_PRINT: print_ary(ary, 5); break;
		case eMENU_FIND_MAX: printf("최댓값: %d \n", findmax_ary(ary, 5)); break;
		case eMENU_FIND_MIN: printf("최솟값: %d \n", findmin_ary(ary, 5)); break;
		case eMENU_SUM: printf("합계: %d \n", sum_ary(ary, 5)); break;
		case eMENU_AVG: printf("평균: %d\n", avg_ary(ary, 5)); break;
		case eMENU_SORT: sort_ary(ary, 5); break;
		default: printf("없는 번호 입니다.\n");
		}

	}

	printf("종료 \n");
}
#endif

#if 0
#include "mylib.h"
#define SIZE(a) (sizeof(a)/sizeof((a)[0]))

int main(void)
{
	int ary[5] = { 0 };
	int c;

	while (c = menu_print2())
		ary_control3(c, ary, SIZE(ary));
	
	return 0;
}
#endif //구조체
//---------------------------------------

#if 0
int main(void)
{
	char ch1, ch2;
	//scanf("%c%c", &ch1, &ch2);  //공백, enter를 입력으로 인식
	//scanf("%c %c", &ch1, &ch2);  // 공백, enter를 입력으로 인식 안함
	ch1 = getchar();
	ch2 = getchar();
	putchar(ch1);
	putchar(ch2);
	printf("[%c%c]", ch1, ch2);
	return 0;
}
#endif

#if 0
#define SIZE(a) (sizeof(a)/sizeof((a)[0]))
void my_gets(char* s, int n) {
	for (int i = 0; i < n - 1; i++) {
		*(s + i) = getchar();
		if (*(s + i) == '\n') {
			*(s + i) = '\0';
			break;
		}
	}
	*(s + n - 1) = '\0';
}
int main(void)
{
	char str[6];
	my_gets(str, SIZE(str));
	printf("%s\n", str);
}
#endif


#if 0
#define SIZE(a) (sizeof(a)/sizeof((a)[0]))

char * to_upper(char* s) {
	int i = 0;
	while(*(s + i)) {
		if ((*(s + i) >= 'a') && (*(s + i) <= 'z'))
			*(s + i) -= ('a'-'A');
		i++;
	}
	return s;
}

char* to_upper1(char* s) {
	char* save = s;
	while (*s) {
		if ((*(s) >= 'a') && (*(s) <= 'z'))
			*(s) -= ('a' - 'A');
		s++;
	}
	return save;
}

int main(void)
{
	char str[40] = "Tom & Jerry";
	printf("%s\n", to_upper1(str));
	printf("%s\n", to_upper(str));
}
#endif