#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

#if 0

/*
1 1 1
1 1 2
1 1 3

1 2 1
1 2 2
1 2 3

1 3 1
1 3 2
1 3 3
*/

int cnt = 0;


void Count(int N, int D, int * P) {

	if (D == 0) {
		for (int i = N; i > 0; i--)
			printf("%d ", P[i]);
		printf("\n");
		return;
	}
	for (int i = 1; i <= N; ++i) {
		P[D] = i;
		Count(N, D-1, P);
	}
}

int main(void)
{
	int N = 5;
	int* P = (int*)calloc(N+1, sizeof(int));

	Count(N, N, P);

	return 0;
}

#endif

#if 0

/*    3P2
123
132
213
231
312
321

1234
1243

1324
1342

1423
1432

2134
2143

2413
2431

	3124
~~
	3421

	4123
~~
	4321
*/

int cnt = 0;
int N = 8;

void Count(int L, int* arr, int* visit) {

	if (L > N) {
		for (int i = 1; i <= N; i++)
			printf("%d ", arr[i]);
		printf("\n");
		return;
	}
	for (int i = 1; i <= N; ++i) {
		if (visit[i] == 0) {
			visit[i] = 1;
			arr[L] = i;
			Count(L + 1, arr, visit);
			visit[i] = 0;
		}
	}
}

int main(void)
{
	int* arr = (int*)calloc(N+1, sizeof(int));
	int* visit = (int*)calloc(N+1, sizeof(int));

	Count(1, arr, visit);

	return 0;
}

#endif

#if 0
/* 
각 노드 연결 여부, 감염 여부 판정 필요
	인접 행렬로 구현 >> 7x7 로 구현, 양방향인 경우 [2][4], [4][2]에 표시하여 경로 확인
	visited 행렬로 방문여부 확인
	 >> 효율이 떨어짐

	 각 행 > 연결 개수, 연결노드 나열 방식으로 구현
	 visited 행렬로 방문여부 확인
	 >> 검색에는 유리
	 >> 연결 개수만큼만 반복하여 검색

*/

#define MAX_N (100+1)
int adjM[MAX_N][MAX_N];
int adjL[MAX_N][MAX_N];
int visited[MAX_N];
int V, E;
int N = 0;
int M = 0;
int cnt;

void inputDataM(void) {
	int x, y;

	scanf("%d", &N);
	scanf("%d", &M);

	for (int i = 0; i < M; ++i) {
		scanf("%d %d", &x, &y);
		adjM[x][y] = 1;
		adjM[y][x] = 1;
	}
}

void inputDataL(void) {
	int x, y;

	scanf("%d", &N);
	scanf("%d", &M);

	for (int i = 0; i < M; ++i) {
		scanf("%d %d", &x, &y);
		adjL[x][0]++;
		adjL[y][0]++;
		adjL[x][adjL[x][0]] = y;
		adjL[y][adjL[y][0]] = x;
	}
}

void print_adjM(void) {
	for (int i = 1; i < N + 1; ++i) {
		for (int j = 1; j < N + 1; ++j)
			printf("%d ", adjM[i][j]);
		printf("\n");
	}
}

void print_adjL(void) {
	for (int i = 1; i < N + 1; ++i) {
		printf("%d : ", i);
		for (int j = 0; j <= adjL[i][0]; ++j) //adjL[i][0]
			printf("%d ", adjL[i][j]);
		printf("\n");
	}
}

void xL(int from) 
{
	int path = adjL[from][0];		//길의 개수
	visited[from] = 1;				//감염

	for (int i = 1; i <= path; i++) { // 존재하는 길 접근
		int next = adjL[from][i];
		if (visited[next] == 0) {	//감염 안되었다면 재귀
			cnt++;
			xL(next);
		}
	}
}

void xM(int from)
{
	visited[from] = 1;					//감염
	for (int to = 1; to <= N+1; to++) {  //감염된 노드의 인접 i에 길이 존재하는가
		int path = adjM[from][to];
		if ((path == 1) && (visited[to] == 0)) {//길이 존재하고, 감염이 안되었다면 재귀
			cnt++;
			xM(to);
		}
	}
}


int main(void) {
	(void)freopen("B2606.txt", "r", stdin);
	//memset(adjM, 0, sizeof(adjM));
	//memset(visited, 0, sizeof(visited));

	cnt = 0;


	inputDataL();
	xL(1);
	print_adjL();
	printf("\n%d\n", cnt);
	
	/*
	inputDataM();
	xM(1);
	print_adjM();
	printf("\n%d\n", cnt);
	*/
	return 0;
}

#endif

#if 0

int cnt = 0;

int* UP;
int* DOWN;
int* CAL;
int N = 0;

void N_Q(int L) {
	if (L >= N) {
		cnt++;
		return;
	}

	for (int i = 0; i < N; ++i)
	{
		if ((UP[i + L] == 0) && (DOWN[i - L + N - 1] == 0) && (CAL[i] == 0)) {
			UP[i + L] = 1;
			DOWN[i - L + N - 1] = 1;
			CAL[i] = 1;
			N_Q(L + 1);
			UP[i + L] = 0;
			DOWN[i - L + N - 1] = 0;
			CAL[i] = 0;
		}
	}
}

int main(void)
{
	(void)scanf("%d", &N);
	
	UP = (int*)calloc(2 * N - 1,sizeof(int));
	DOWN = (int*)calloc(2 * N - 1, sizeof(int));
	CAL = (int*)calloc(N, sizeof(int));

	N_Q(0);

	printf("%d", cnt);

	return 0;
}

#endif //N-Queen

#if 0


int N = 0;
int* path = NULL;
int* visited = NULL;
int min = 100;
int tmp = 0;
int flag = 0;

void hea(int L, int curr) {
	if (L > N) {
		if (flag == 1)
		{
			min = ((tmp < min) ? tmp : min);
		}
		flag = 0;
		return;
	}

	for (int i = 0; i < N; ++i) {
		if ((path[curr * N + i] != 0) && visited[i] == 0) {
			int index = curr * N + i;
			if ((L == N) && (visited[0] == 0))
				flag = 1;
			if ((L != N) && (i == 0))
				continue;
			tmp += path[index];
			visited[i] = 1;
			hea(L + 1, i);
			visited[i] = 0;
			tmp -= path[index];
		}
	}
}



int main(void) {

	scanf("%d", &N);

	path = (int*)calloc(N * N, sizeof(int));
	visited = (int*)calloc(N, sizeof(int));
	for (int i = 0; i < N * N; ++i)
		scanf("%d", path + i);
	min = 100 * N;
	hea(1, 0);

	printf("%d\n", min);
	return 0;
}
#endif //해밀턴