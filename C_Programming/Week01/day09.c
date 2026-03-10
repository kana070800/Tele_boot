#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))


#if 0

typedef struct _student {
	char* name;
	int age;
}student;



int compInt(const void* a, const void* b) {
	int* ap = (int*)a;
	int* bp = (int*)b;
	/*
	if (*ap == *bp)
		return 0;
	return (*ap > *bp) ? 1 : -1;
	*/
	//3항 연산자는 if, else와 동일하다, if 2번이 좋은 방법
	
	// return (*ap > *bp) ? 1 : (*ap == *bp) ? 0:-1; //if else 2번과 동일
	// return *ap - *bp // 연산시 overflow 위험 존재

	return (*ap < *bp) - (*ap > *bp);
}

int compChar(const void* a, const void* b) {
	return strcmp(*(char**)a, *(char**)b);
	//return strcmp((char*)(*a), (char*)(*b));  // void **를 입력 받을 때 유효한 답안, 일반 변수를 포인터로 인식하는 기법은 유효하지 않음
}

int compChar2(const void* a, const void* b) {
	 return strcmp(*(char(*)[10])a, *(char(*)[10])b);
	//return strcmp((char *)a, (char*)b);  //주소는 동일하기에 똑같은 동작
	// return strcmp(a, b);  //자동적으로 char* 형변환이 된다
	// return strcmp(*(char **)a, *(char**)b); // 안되는 이유가 뭘까?
}

int comp_stu_n(const void * a, const void * b) {
	return strcmp((*(student*)a).name, ((student*)b)->name); // (*(student*)b).name   형변환이 -> 보다 우선순위가 떨어진다
}

int comp_stu_a(const void* a, const void* b) {
	int ai = (*(student*)a).age;
	int bi = ((student*)b)->age;
	return (ai > bi) - (ai < bi);
}

int main(void)
{
	int a[10] = { 78,94,59,48,73,66,42,23,15,24 };
	qsort(a, 10, 4, compInt);

	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	char* str[5] = { "rabbit", "elephant", "cat", "tiger", "dog" };
	qsort(str,5,4,compChar);
	for (int i = 0; i < 5; i++)
		printf("%s ", str[i]);
	printf("\n");

	char str2[5][10] = {"rabbit", "elephant", "cat", "tiger", "dog"};

	
	qsort(str2, 5, 10, compChar2);
	for (int i = 0; i < 5; i++)
		printf("%s ", str2[i]);
	printf("\n"); printf("\n");
	
	printf("%p %p %p\n", (*(char **)str2+0), (*(char**)str2 + 1), (*(char(*)[10])str2 + 1));
	// char** 로 변환하여 적용하면 안되는 것의 이유가 될 것 같다

	student stu[] = {{"tom", 30}, {"Candy", 50},
		{"Terry", 20},{"Jaen", 10},{"Henry", 40} };
	student A;
	A = (student){ "tom", 30 };
	qsort(stu, 5, sizeof(student), comp_stu_a); //이름 오름차순 정렬
	for (int i = 0; i < 5; i++)
		printf("%s %d\n", (stu+i)->name, stu[i].age);
	printf("%s %d\n", A.name, A.age);
	return 0;
}

#endif

#if 0
int main(void)
{
	int* pi;
	int i, sum, N;

	printf("명수 입력 : ");
	scanf("%d", &N);
	pi = (int*)malloc(N * sizeof(int));
	if (pi == NULL) {
		printf("메모리 부족\n");
		exit(1);
	}

	printf("%d 명 나이 입력\n", N);
	for (int i = 0; i < N; i++)
		scanf("%d", pi + i);
	sum = 0;
	for (int i = 0; i < N; i++)
		sum += *(pi + i);

	printf("나이 평균 : %.1f", (double)sum / N);

	free(pi);
	pi = NULL;
	return;
}
#endif

#if 0
int main(void)
{
	int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
// 2차원 배열의 행의 개수 모를 때
	int(*b)[4] = NULL;

	b = (int(*)[4])calloc(3, sizeof(int[4]));
	if (b == NULL)
		exit(0);
	
// 2차원 배열의 행과 열의 개수 모를 때 [1]
	int** c = NULL;

	c = (int**)calloc(3, sizeof(int*));
	if (c == NULL)
		exit(0);
	for (int i = 0; i < 3; i++) {
		c[i] = (int*)calloc(4, sizeof(int));
		if (c[i] == NULL)
			exit(0);
	}
// 2차원 배열의 행과 열의 개수 모를 때 [2]
	int** d = NULL;

	d = (int**)calloc(3, sizeof(int*));
	if (d == NULL)
		exit(0);

	d[0] = (int*)calloc(12, sizeof(int));
	if (d[0] == NULL)
		exit(0);
	for (int i = 1; i < 3; i++) {
		d[i] = d[0] + sizeof(int*) * i;
	}

	int cnt = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++)
			b[i][j] = c[i][j] = d[i][j] = ++cnt;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d\n", a[i][j]);
			printf("%d\n", b[i][j]);
			printf("%d\n", c[i][j]);
			printf("%d\n", d[i][j]);
		}
	}

	free(b);

	for (int i = 0; i < 3; i++)
		free(c[i]);
	free(c);

	free(d[0]);
	free(d);

	return 0;
}
#endif


#if 0

int main(void) {
	int* a  = NULL; //배열 이름
	int* temp = NULL; //임시변수
	int N = 0;		//배열의 크기
	int num;		//입력변수
	int count;		//입력받은 데이터 개수

	for (count = 0; scanf("%d", &num) && num > 0; ++count)
	{
		if (count == N) {
			N += 3;
			temp = (int*)realloc(a, N * sizeof(int));
			if (temp == NULL) {
				free(a);
				exit(1);
			}
			a = temp;
		}
		a[count] = num;
	}



	for (int i = 0; i < count; i++) {

		printf("%d ", a[i]);
	}

	free(a);
	a = NULL;

	


	return 0;

}
#endif

#if 0

int main(void) {
	
	char temp[80];
	char** str = NULL;
	int N;

	(void)freopen("data.txt", "r", stdin);
	(void)scanf("%d", &N);
	str = (char**)calloc(N, sizeof(char*));
	if (str == NULL) exit(0);

	for (int i = 0; i < N; i++) {
		(void)scanf("%s", temp);

		str[i] = (char*)malloc((strlen(temp) + 1));
		if (str[i] == NULL) exit(0);

		strcpy(str[i], temp);
	}

	for (int i = 0; i < N; i++)
		printf("%s ", str[i]);
	
	for (int i = 0; i < N; i++)
		free(str[i]);
	free(str);
	str = NULL;
	

	return 0;

}
#endif

#if 0

char **inputData(int *N) {
	char temp[80];
	int cnt;
	char** str = NULL;
	(void)scanf("%d", N);
	cnt = *N;
	str = (char**)calloc(cnt, sizeof(char*));
	if (str == NULL) exit(0);

	for (int i = 0; i < cnt; i++) {
		(void)scanf("%s", temp);

		str[i] = (char*)malloc((strlen(temp) + 1));
		if (str[i] == NULL) exit(0);

		strcpy(str[i], temp);
	}
	return str;
}

printData(int N, char**str) {
	for (int i = 0; i < N; i++)
		printf("%s ", str[i]);
	printf("\n");
}

freeData(int N, char ** str) {
	for (int i = 0; i < N; i++)
		free(str[i]);
	free(str);
}

int main(void) {

	char temp[80];
	char** str = NULL;
	int N;

	(void)freopen("data.txt", "r", stdin);

	str = inputData(&N);

	printData(N, str);

	freeData(N, str);

	str = NULL;


	return 0;

}
#endif //권장되는 방식
