#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

#if 0

void exchange1(int** a, int** b)
{
	int temp;
	temp = **a;
	**a = **b;
	**b = temp;
}

void exchange2(int*** a, int*** b)
{
	int temp;
	temp = ***a;
	***a = ***b;
	***b = temp;
}

void exchange3(int** a, int** b)
{
	int* temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void exchange4(int*** a, int*** b)
{
	int* temp;
	temp = **a;
	**a = **b;
	**b = temp;
}

void exchange5(int*** a, int*** b)
{
	int** temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(void)
{
	int a = 10, b = 20;
	int* ap = &a;
	int* bp = &b;
	int** app = &ap;
	int** bpp = &bp;
	printf("%d %d\n", a, b);
	exchange1(&ap, &bp);
	printf("%d %d\n", a, b);
	printf("\n");
	printf("%d %d\n", a, b);
	exchange2(&app, &bpp);
	printf("%d %d\n", a, b);
	printf("\n");
	printf("%d %d\n", ap, bp);
	exchange3(&ap, &bp);
	printf("%d %d\n", ap, bp);
	printf("\n");
	printf("%d %d\n", ap, bp);
	exchange4(&app, &bpp);
	printf("%d %d\n", ap, bp);
	printf("\n");
	printf("%d %d\n", app, bpp);
	exchange5(&app, &bpp);
	printf("%d %d\n", app, bpp);

	return 0;
}

#endif

#if 0

void _print_ary_(char** pary, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", *(pary + i));
	}

}

int main(void)
{
	char* pary[5] = { "dog", "elephant", "horse", "tiger", "lion" };
	_print_ary_(pary, SIZE(pary));
	return 0;
}
#endif

#if 0

void _print_ary_(char (* pary)[10], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", *(pary + i));
	}

}

int main(void)
{
	char pary[5][10] = {"dog", "elephant", "horse", "tiger", "lion"};
	_print_ary_(pary, SIZE(pary));
	return 0;
}
#endif

#if 0

int main(void)
{
	int a[3][4] = { 1,2,3,4,11,12,13,14, 21,22,23,24 };

	int ary1[5] = {4, 1,2,3,4 };
	int ary2[6] = {5, 11, 12,13 ,14,15 };
	int ary3[5] = {4, 21,22,23,24 };

	int* ary[3] = { ary1, ary2, ary3 };
	/*
	for (int i =0; i< 3;i++)
		for(int j = 0; j < 4; j++){
			printf("%5d", a[i][j]);  //디스 어셈블리 결과 메모리 접근이 한번 더 발생
			printf("%5d", ary[i][j]);// 단순 접근 시 좀 더 빠름
		}*/

	
//가변 배열의 첫 인수에 크기 저장시 활용법
	for (int i = 0; i < 3; i++)
		for (int j = 1; j <= ary[i][0]; j++) {
			printf("%5d", ary[i][j]);// 단순 접근 시 좀 더 빠름
		}
	
	return 0;
}
#endif

#if 0

void print_ary2(int* ary, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", ary[i]);
	}
	printf("\n");
}

int comp_inc(int lefty, int righty) {
	return (lefty > righty);
}

int comp_dec(int lefty, int righty) {
	return (lefty < righty);
}

void sort_ary2(int* ary, int size, int (*func)(int, int)) {
	int temp;

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (func(ary[i], ary[j])) {
				temp = ary[i];
				ary[i] = ary[j];
				ary[j] = temp;
			}
		}
	}
}

#define size_ary(x) (sizeof(x) / sizeof((x)[0]))

int main() {

	int ary[] = { 8, 5, 2, 12, 7, 9, 4, 6, 10, 3 };

	print_ary2(ary, size_ary(ary));
	sort_ary2(ary, size_ary(ary), comp_inc);
	print_ary(ary, size_ary(ary));
	sort_ary2(ary, size_ary(ary), comp_dec);
	print_ary(ary, size_ary(ary));
	return 0;
}
#endif


#if 0
int sum(int a, int b) {

	return a + b;
}

int sub(int a, int b) {

	return a - b;
}

int mul(int a, int b) {

	return a * b;
}

void func(int (**op)(int, int), int size) {
	for (int i = 0;i < size; i++)
		printf("%d\n", (*(op + i))(2, 3));
}

void func1(void ** ap, int size) {
	for (int i = 0; i < size; i++)
		printf("%d\n", ((int (*)(int, int))(*(ap + i)))(2, 3));
}


int main(void)
{
	int (*op[3])(int, int) = {sub, sum, mul};


	func(op, 3);


	printf("%d\n", (*(op + 0))(2, 3));
	printf("%d\n", (*(op + 1))(2, 3));
	printf("%d\n", (*(op + 2))(2, 3));


	
	void* ap[3] = {sub, sum, mul};

	func1(ap, 3);

	printf("%d\n", ((int (*)(int, int))(*(ap+0)))(2, 3));
	printf("%d\n", ((int (*)(int, int))ap[1])(2, 3));
	printf("%d\n", ((int (*)(int, int))ap[2])(2, 3));
	//지저분하기에 typedef 를 사용할 수 있다
	return 0;
}
#endif
