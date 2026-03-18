#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))


#if 0

/*
단순 이동 횟수
	[1] > 1
	[2] > [1] + 1 + [1] > 3
	[3] > [3] + 1 + [3] > 7
	[4] > [3] + 1 + [4] > 15
	...
	[N] > [N-1] + 1 + [N-1]

이동하는 위치의 결정 [N] == 탑의 이동
	[1] > 즉시 원하는 위치
	[2]
		[1]을 자리 2  >  2 넘김 >  [1]을 자리 3
		2 [1] 0
			1 2 > 1 3 > 2 3
	[3]
		[2]을 자리 2  >  3 넘김 >  [2]을 자리 3
		3 [2] 0
			[1 3 > 1 2 > 3 2] > 1 3 > [2 1 > 2 3 > 1 3]
	[4]
		[3]을 자리 2  >  4 넘김 >  [3]을 자리 3
		4 [3] 0
		[2]을 자리 3 >  3 넘김 >  [2]을 자리 2    >>   4   >>  [2]을 자리 1 >  3 넘김 >  [2]을 자리 3

		           [[1 3 > 1 2 > 3 2] > 1 2 > [2 1 > 2 3 > 1 3]] > 1 3 >[[1 3 > 1 2 > 3 2] > 2 3 > [2 1 > 2 3 > 1 3]]
	[5]
		[4]을 자리 2  >  5 넘김 >  [4]을 자리 3
		5 [4] 0
...
	[N]
		[N-1]을 자리 2  >  N 넘기고 [N-1]을 자리 3
		N [N-1] 0 > 0 [N-1] N

기존 [x]의 위치, 이동하고 싶은 위치(원하지 않는 위치 포함됨), x값이 필요

원하는 위치, 이동해야할 위치 판별 문제



본능적으로 문제가 풀리는 과정 중 나는 무엇을 고려하고 있는가
*/
int cnt = 0;

int count(int N)
{
	if (N == 1)
		return 1;
	return 2 * count(N - 1) + 1;
}

void hanoi_tower(int N, int from, int to)
{
	int not_to = 6 - from - to; // not to 결정, 1,2,3 중 from도 to도 아닌 것

	if (N == 1)
	{
		cnt++;
		printf("%d %d\n", from, to);
		return;
	}

	hanoi_tower(N - 1, from, not_to); // [N-1]을 from 에서 not to 로
	cnt++;
	printf("%d %d\n", from, to); // N을 from에서 to 로 
	hanoi_tower(N - 1, not_to, to); // [N-1]을 not to 에서 to 로
	return 0;
}

int main(void)
{
	int N = 5;
	int K = 0;

	//scanf("%d", N);
	printf("%d\n", count(N));

	hanoi_tower(N, 1, 3);

	printf("%d", cnt);
	return 0;
}


#endif

#if 0

// code for baekjoon : 24444


#include <stdio.h>
#include <stdlib.h>
int N = 0;
int M = 0;
int R = 0;
int* space = NULL;
int* visited = NULL;

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

void bfs(int st) {
    //printf("%d\n",st);

    int first = st * (M + 1);
    int j = 0;
    int* logg = (int*)calloc(M, sizeof(int));
    //가기 전에 visit 검사 후 행렬에 저장하고 visit=1 수행 , 저장된 행렬을 통해 bfs call
    for (int i = space[first]; 1 <= i; i--) {
        int to_go = space[first + i];
        if (visited[to_go] == 0) {
            visited[to_go] = 1;
            logg[j++] = to_go;
        }
    }
    for (int i = 0; logg[i] != 0; i++)
        printf("%d\n", logg[i]);
    printf("\n");
    for (int i = 0; logg[i] != 0; i++)
        bfs(logg[i]);
}

int main(void)
{
    int cnt = 0;
    scanf("%d %d %d", &N, &M, &R);

    space = (int*)calloc((N + 1) * (M + 1), sizeof(int));
    visited = (int*)calloc(N + 1, sizeof(int));
    for (int i = 1; i <= M; ++i) {
        int from, to;
        scanf("%d %d", &from, &to);
        space[from * (M + 1)]++;
        space[from * (M + 1) + i] = to;

        //space[to*(M+1)]++;
        //space[to*(M+1) + i] = from;
    }

    for (int i = 1; i <= N; ++i) {
        qsort(space + i * (M + 1) + 1, M, sizeof(int), compare);
    }
    printf("%d\n", R);
    bfs(R);
    /*
    for (int i = 0; i < (N+1)*(M+1);++i){
            printf("%d ", space[i]);
            cnt++;
            if (cnt == M+1){
                    printf("\n");
                    cnt = 0;
            }
    }
    printf("\n\n%d %d\n", N, M);
*/
    return 0;
}

#endif  //bfs