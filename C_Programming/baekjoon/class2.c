#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

//제로
#if 0
int main(void) {
	int N = 0;
	int tmp;
	int sp = 0;
	scanf("%d", &N);

	long* stack = (long *)calloc(N, sizeof(long));

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &tmp);

		if (tmp != 0)
			stack[sp++] = tmp;
		if (tmp == 0)
			sp--;
	}
	long sum = 0;
	for (int i = 0; i < sp; i++)
		sum += stack[i];

	printf("%d", sum);
}

#endif //굳이 삭제할 필요도 없더라


//요세푸스 문제 0
#if 0
int main(void)
{
	int N = 0;
	int K = 0;
	int sp = -1;
	scanf("%d", &N);
	scanf("%d", &K);
	int* stack = (int*)calloc(N, sizeof(int));
	printf("<");
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < K; ++j) {
			sp++;
			if (sp == N)
				sp = 0;

			if (stack[sp] == 1)
				j--;
			else if (j == K - 1) {
				printf("%d", sp + 1);
				if (i != N - 1)
					printf(", ");
				stack[sp] = 1;
				break;
			}
			else
				continue;
		}

	}
	printf(">");
	return;
}

#endif  //return 0 안쓰면 런타임 에러
//반복문내부 제어변수의 참조를 통해 조건부 동적 반복가능


//소수 찾기
#if 0
int main(void) {
	int N = 0;
	int tmp = 0;
	int cnt = 0;
	int f = 0;
	scanf("%d", &N);

	int* s = (int*)calloc(N, sizeof(int));
	for (int i = 0; i < N; ++i)
		scanf("%d", &s[i]);

	for (int i = 0; i < N; ++i) {
		tmp = s[i];
		if ((tmp == 2) || (tmp == 3) || (tmp == 5) || (tmp == 7)) {
			cnt++;
			continue;
		}
		if ((tmp == 1) || !(tmp % 2) || !(tmp % 3) || !(tmp % 5) || !(tmp % 7))
			continue;

		f = 1;
		for (int j = 2; j < tmp/2; ++j) {
			if (!(j % 2) || !(j % 3) || !(j % 5) || !(j % 7))
				continue;
			if (!(tmp % j))
				f = 0;
		}
		cnt += f;
	}

	printf("%d", cnt);
	return 0;
}
#endif// 반복문 제어문자의 선정 주의, 1일 때 조건 간과... 어떻게 해결할까...


//이항 계수1
#if 0
int main(void) {
	int N = 0;
	int K = 0;
	int cc = 1;
	scanf("%d %d", &N, &K);

	for (int i = N; i > N - K; i--) {
		cc = cc * i;
	}

	for (int i = K; i > 1; i--) {
		cc = cc / i;
	}
	printf("%d", cc);
	return 0;
}
#endif


// 좌표 정렬하기 오답**********************************************
#if 0

typedef struct xy {
	int x, y;
}ST;

int fx(ST* a, ST* b)
{
	return a->x - b->x;
}

int fy(ST* a, ST* b)
{
	return a->y - b->y;
}

int main(void) {
	int N = 0;
	int curr, next;
	scanf("%d", &N);

	ST* arr = (ST*)calloc(N, sizeof(ST));
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &((arr+i)->x), &((arr + i)->y));
	}
	qsort(arr, N, sizeof(ST),fx);


	for (int i = 0; i < N-1; i++) {
		curr = 0, next = 0;
		if (arr[i].x != arr[i + 1].x) {
			continue;
		}
		else {
			curr = i;
			next = curr;
			while (arr[curr].x == arr[next++].x) {
				if (next == N) {
					next--;
					break;
				}
			}
		}
		qsort(arr + curr, next - curr, sizeof(ST), fy);
	}


	for (int i = 0; i < N; i++)
		printf("%d %d\n", (arr + i)->x, (arr + i)->y);
}
#endif////왜 안되는지 모르겠네... 반례 통과 했자나...

// 좌표 정렬하기 정답**********************************************
#if 0

typedef struct xy {
	int x, y;
}ST;

int fx(const void* a, const void* b) {
	ST* p1 = (ST*)a;
	ST* p2 = (ST*)b;

	if (p1->x != p2->x) 
		return p1->x - p2->x;
	
	return p1->y - p2->y;
}

int main(void) {
	int N = 0;
	int curr, next;
	scanf("%d", &N);

	ST* arr = (ST*)calloc(N, sizeof(ST));
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &((arr + i)->x), &((arr + i)->y));
	}
	qsort(arr, N, sizeof(ST), fx);


	for (int i = 0; i < N; i++)
		printf("%d %d\n", (arr + i)->x, (arr + i)->y);
}
#endif//// qsort의 구조체 정렬

// 수 정렬 2
#if 0

int fx(int *a, int* b) {
	return *a - *b;
}

int main(void) {
	int N = 0;

	scanf("%d", &N);

	int* arr = (int*)calloc(N, sizeof(int));

	for (int i = 0; i < N; i++)
		scanf("%d", (arr + i));

	qsort(arr, N, sizeof(int), fx);


	for (int i = 0; i < N; i++)
		printf("%d\n", *(arr+i));
}
//
#endif

//직각삼각형
#if 0
int main(void) {
	int a, b, c;

	while (1) {
		scanf("%d %d %d", &a, &b, &c);

		if ((a==0)&&(b==0)&&(c==0))
			break;

		a *= a;
		b *= b;
		c *= c;

		if ((a == b+c)||(b == a + c )||(c == a+b)) {
			printf("right\n");
		}
		else {
			printf("wrong\n");
		}
	}

	return 0;
}
#endif

//스텍 
#if 0
enum x{
	push = 1,
	pop ,
	size,
	empty,
	top
};

int main(void) {

	int N = 0;
	int cn = 0;
	int sp = 0;
	int tmp = 0;
	char cmd[10];

	//int* stack = (int*)calloc(N, sizeof(int));
	int stack[10000] = { 0 };
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		scanf("%s", cmd);
		if (!strcmp(cmd, "push"))
			cn = push;
		if (!strcmp(cmd, "pop"))
			cn = pop;
		if (!strcmp(cmd, "size"))
			cn = size;
		if (!strcmp(cmd, "empty"))
			cn = empty;
		if (!strcmp(cmd, "top"))
			cn = top;

		switch (cn) {
		case push:
			scanf("%d", &tmp);
			stack[sp++] = tmp;
			break;
		case pop:
			if (sp == 0) {
				printf("-1\n");
				break;
			}
			printf("%d\n", stack[sp-- - 1]);
			break;
		case size:
			printf("%d\n", sp);
			break;
		case empty:
			if (sp == 0) {
				printf("1\n");
				break;
			}
			printf("0\n");
			break;
		case top:
			if (sp == 0) {
				printf("-1\n");
				break;
			}
			printf("%d\n", stack[sp-1]);
			break;
		}
	

	}


	return 0;
}

#endif // 절대 alloc 함수들을 쓰지마...

//체스판 칠하기
#if 0

char board[50][50] = { 'W' };
int min = 0x7fffffff;


void find_minW(int sr, int sc) {
	int cnt = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2) {
				if (board[sr + i][sc + j] != 'W')
					cnt++;
			}
			else {
				if (board[sr + i][sc + j] != 'B')
					cnt++;
			}
		}
	}
	if (min > cnt)
		min = cnt;
}

void find_minB(int sr, int sc) {
	int cnt = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2) {
				if (board[sr + i][sc + j] != 'B')
					cnt++;
			}
			else {
				if (board[sr + i][sc + j] != 'W')
					cnt++;
			}
		}
	}
	if (min > cnt)
		min = cnt;
}


int main(void) {
	int R, C;
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; ++i)
		scanf("%s", board + i);
	
	int s = 0;
	for (int i = 0; i <= R - 8; ++i) {
		for (int j = 0; j <= C - 8; ++j) {
			find_minW(i,j);
			find_minB(i, j);
		}
	}
	printf("%d\n", min);
	return 0;
}
#endif //내가 알아볼 수 있게 변수명을 정하죵,,,

//큐
#if 0
enum x {
	push = 1,
	pop,
	size,
	empty,
	front,
	back
};

int main(void) {

	int N = 0;
	int cn = 0;
	int f = 0,b = 0;
	int tmp = 0;
	char cmd[10];

	//int* stack = (int*)calloc(N, sizeof(int));
	int heap[10000] = { 0 };
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		scanf("%s", cmd);
		if (!strcmp(cmd, "push"))
			cn = push;
		if (!strcmp(cmd, "pop"))
			cn = pop;
		if (!strcmp(cmd, "size"))
			cn = size;
		if (!strcmp(cmd, "empty"))
			cn = empty;
		if (!strcmp(cmd, "front"))
			cn = front;
		if (!strcmp(cmd, "back"))
			cn = back;

		switch (cn) {
		case push:
			scanf("%d", &tmp);
			heap[b++] = tmp;
			break;

		case pop:
			if (b == f) {
				printf("-1\n");
				break;
			}
			printf("%d\n", heap[f++]);
			break;
		case size:
			printf("%d\n", b-f);
			break;
		case empty:
			if (b == f) {
				printf("1\n");
				break;
			}
			printf("0\n");
			break;
		case front:
			if (b == f) {
				printf("-1\n");
				break;
			}
			printf("%d\n", heap[f]);
			break;
		case back:
			if (b == f) {
				printf("-1\n");
				break;
			}
			printf("%d\n", heap[b - 1]);
			break;
		}


	}


	return 0;
}

#endif

//괄호
#if 0
int main(void)
{
	char things[10000][51] = { 0 };
	int target = 0;

	int N = 0;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
		scanf("%s", (things + i));

	for (int i = 0; i < N; ++i) {
		target = 0;
		for (int j = 0; j < 50; j++) {
			if (things[i][j] == '(')
				target++;
			if (things[i][j] == ')')
				target--;
			if (target < 0) {
				break;
			}
		}
		if (target == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}
#endif// 몇개 입력인지 최대 값 지정 안한 쓰레기 문제 라고하면 안되겠죠

//팰린드롬수우
#if 0
int main(void)
{
	char things[10000][51] = { 0 };
	int target = 0;

	int i = 0;
	for (; i < 10000; ++i) {
		scanf("%s", (things + i));
		if (!strcmp("0", (things + i)))
			break;
	}






	return 0;
}
#endif

#if 0
#endif