#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

#if 0
int main(void)
{
	int a[5] = { 1,2,3,4,5 };
	int* p = a;
	for (int i = 0; i < SIZE(a); i++) {
		printf("%d ", a[i]);
		printf("%d ", p[i]);
		printf("%d ", *(a+i));
		printf("%d\n", *(p + i));
	}
	return 0;
}
#endif // 배열 등가 포인터

#if 0
int main(void)
{
	int a[2][3][4] = {0}; //3차원 배열
	int (*b[3])[4] = {0}; // 배열[4]포인터의 배열[3]
	int* (*c[2])(int*) = {0}; //함수포인터의 배열[2]
	int* d[3][4] = {0};    //포인터의 2차원배열
	int (*(*e[5])(void))[4] = {0};  //배열[4]포인터를 반환하는 함수    의 포인터의 배열

	int (*pa)[3][4] = a;  //이차원 배열의 포인터
	int (**pb)[4] = b;   //배열[4]의 이중포인터
	int* (**pc)(int*) = c; //함수의 이중포인터
	int* (*pd)[4] = d;      //포인터배열[4]의 포인터
	int (*(**pe)(void))[4] = e;  //배열[4]포인터를 반환하는 함수   의 이중포인터

	/*
	int a[5] = {1,2,3,4,5};
	for (int i = 0; i < SIZE(a); i++) {
		printf("%d ", a[i]);
		printf("%d ", p[i]);
		printf("%d ", *(a + i));
		printf("%d\n", *(p + i));
	}*/
	return 0;
}
#endif // 배열 등가 포인터 ex심화

#if 0
int main(void)
{
	int a[3][4] = { 0 };
	//printf("%d %d\n", sizeof(*a), sizeof(*a[0])); //첫번째 요소값의 크기
	//printf("%d %d %d", sizeof(a), sizeof(a[0]), sizeof(a[0][0])); //배열의 크기를 표현
	//printf("%d %d", sizeof(&a), sizeof(&a[0])); // &은 포인터이므로 4
	
	//printf("%p ", &a);
	//printf("%p ", &a+1);
	//printf("%p ", a);
	//printf("%p ", a+1);
	//printf("%p ", a[0]);
	//printf("%p ", a[0]+1); //바로 위 코드와 비용은 동일(상수연산)
	//printf("%p ", a[1]);
	//printf("%p ", a[1]+1);
	//00BAFC44 00BAFC74 00BAFC44 00BAFC54 00BAFC44 00BAFC48 00BAFC54 00BAFC58


	char as[] = "tiger";
	printf("%s", as);
	return 0;
}
#endif


#if 0
int main(void)
{
	int a[3][4] = { 0 };
	/*
	1. a                      1000, int (*)[4]
	2. *a                     1000, int *
	3. a[0] == *a             1000, int *
	4. *a[0] == **a           1, int
	5. (*a)[0] >> **a         1, int
	6. *(*(a+1)+0) >>         5, int      
	7.(*(a+1))[0] >>          5, int
	8. *(*(a+0)+2) >>         3, int
	9. (*a+2)[0]   >> *(*a+2)         3, int
	10. (*(*a)+1)  >> **a+1           2, int

	11. &(a+1)[2] >>   a+3         1048, int (*)[4]  XXXXX

	12. *a+1       >>             1004, int *
	13. (a+1)[2]   >> *(a+3)           1048, int *  XXXXX
	14 &(*a)[0]    >> &*(*a)          1000, int *
	15. a[1] + 2   >> *(a+1)+2           1024, int *
	16. &*(*(a+2)) >> *(a+2)           1032, int *

	*a[1] 과 (*a)[1]의 차이
	 >> *(*(a+1)) == 5, *((*a)+1) == 2

	 포인터 형식으로 통일
	 배열이름은 첫번째 요소를 가리킴
	 배열이름 + 상수 연산을 통해 배열 요소를 접근, *에 따라 차원 감소, &으로 차원 증가

	*/
	printf("%s", as);
	return 0;
}
#endif
