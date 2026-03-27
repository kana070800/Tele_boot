#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*
 시작접 지정(enqueue), 방문
 for (queue != empty)
 {
	dequeue
	인접점 enqueue, 방문
	종료조건 존재시 점검
 }*/

#if 0

#define MAX_N (100+2)
int map[MAX_N][MAX_N];
int R, C;
int sR, sC; //start
int cnt = 0;

typedef struct _node {
	int r, c;
}node;
int front, rear;
node Queue[MAX_N * MAX_N];
void Enqueue(node data) {
	Queue[rear++] = data;
}

node Dequeue(void) {
	return Queue[front++];
}

void inputData(void) {
	char tmp[MAX_N] = { 0 };
	
	scanf("%d %d", &C, &R);

	for (int i = 1; i <= R; ++i) {
		scanf("%s", tmp + 1);
		for (int j = 1; j <= C; ++j) {
			map[i][j] = tmp[j] - '0';
			cnt += map[i][j];
		}
	}

	scanf("%d %d", &sC, &sR);
}
int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

int BFS(int sR, int sC) {
	int nR, nC;
	int time = 3;
	node curr;

	front = rear = 0;			//bfs 여러번 수행시 초기화 필요
	Enqueue((node) { sR, sC });
	map[sR][sC] = time;			//방문표시
	while (front != rear) {				//q에 존재시 반복
		curr = Dequeue();
		time = map[curr.r][curr.c] + 1;
		for (int i = 0; i < 4; i++) {     //인접점 탐색 후 존재시 enqueue 및 방문표시
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];

			if (map[nR][nC] == 1) {
				Enqueue((node) { nR, nC });
				map[nR][nC] = time;
			}
		}
	}
	return time - 1;  // 마지막 큐에서 time이 1 증가했기에 빼기 수행 필요
}

int main(void) {
	int N, M;
	//(void)freopen("j1078.txt", "r", stdin);
	inputData();

	int time = BFS(sR, sC);

	//printf("%d\n%d", BFS(sR, sC), cnt - rear);  
	//rear는 BFS의 동작이후 결정되는 종속적인 변수
	// printf() 내부 평가 순서는 컴파일러에 따라 다름
	//순서를 결정짓는 습관이 중요
	printf("%d\n%d", time, cnt - rear);

	return 0;
}


#endif //저글링

#if 0

#define MAX_N (100+2)
int map[MAX_N][MAX_N];
int R, C;
int sR, sC; //start
int eR, eC; //end
int cnt = 0;

typedef struct _node {
	int r, c, t;
}node;
int front, rear;
node Queue[MAX_N * MAX_N];
void Enqueue(node data) {
	Queue[rear++] = data;
}

node Dequeue(void) {
	return Queue[front++];
}

void inputData(void) {
	char tmp[MAX_N] = { 0 };

	scanf("%d %d", &C, &R);
	scanf("%d %d %d %d", &sC, &sR, &eC, &eR);
	for (int i = 1; i <= R; ++i) {
		scanf("%s", tmp + 1);
		for (int j = 1; j <= C; ++j) {
			map[i][j] = tmp[j] - '0';
			cnt += map[i][j];
		}
	}
}
int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

int BFS(int sR, int sC) {
	int nR, nC;
	int time = 0;
	node curr;

	front = rear = 0;			//bfs 여러번 수행시 초기화 필요
	Enqueue((node) { sR, sC, time });

	
	while (front != rear) {				//q에 존재시 반복
		curr = Dequeue();
		if ((curr.r == eR) && (curr.c == eC))
			return curr.t;
		for (int i = 0; i < 4; i++) {     //인접점 탐색 후 존재시 enqueue 및 방문표시
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];

			if ((map[nR][nC] == 0)&&(nR > 0)&&(nC > 0)&&(nR <= R)&&(nC <= C)) {
				time = curr.t + 1;
				Enqueue((node) { nR, nC, time });
				map[nR][nC] = 1;
			}
		}
	}
	return 0;
}

int main(void) {
	int N, M;
	(void)freopen("j1661.txt", "r", stdin);
	inputData();

	int time = BFS(sR, sC);

	//printf("%d\n%d", BFS(sR, sC), cnt - rear);  
	//rear는 BFS의 동작이후 결정되는 종속적인 변수
	// printf() 내부 평가 순서는 컴파일러에 따라 다름
	//순서를 결정짓는 습관이 중요
	printf("%d\n", time);

	return 0;
}


#endif //미로탈출시간


#if 0

#define MAX_N (100+2)
int map[MAX_N][MAX_N];
int R, C;
int sR, sC; //start
int eR, eC; //end
int cnt = 0;

typedef struct _node {
	int r, c, t;
}node;
int front, rear;
node Queue[MAX_N * MAX_N];

void Enqueue(node data) {
	Queue[rear++] = data;
}

node Dequeue(void) {
	return Queue[front++];
}

void inputData(void) {
	char tmp[MAX_N] = { 0 };

	memset(map, 1, sizeof(map));

	scanf("%d %d", &C, &R);
	scanf("%d %d %d %d", &sC, &sR, &eC, &eR);
	for (int i = 1; i <= R; ++i) {
		scanf("%s", tmp + 1);
		for (int j = 1; j <= C; ++j) {
			map[i][j] = tmp[j] - '0';
			cnt += map[i][j];
		}
	}
}
int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

int BFS(int sR, int sC) {
	int nR, nC;
	node curr;

	front = rear = 0;			//bfs 여러번 수행시 초기화 필요
	Enqueue((node) { sR, sC, 0 });


	while (front != rear) {				//q에 존재시 반복
		curr = Dequeue();
		if ((curr.r == eR) && (curr.c == eC))
			return curr.t;
		for (int i = 0; i < 4; i++) {     //인접점 탐색 후 존재시 enqueue 및 방문표시
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];

			if ((map[nR][nC] == 0)) {
				Enqueue((node) { nR, nC, curr.t + 1});
				map[nR][nC] = 1;
			}
		}
	}
	return 0;
}

int main(void) {
	int N, M;
	(void)freopen("j1661.txt", "r", stdin);
	inputData();

	int time = BFS(sR, sC);

	//printf("%d\n%d", BFS(sR, sC), cnt - rear);  
	//rear는 BFS의 동작이후 결정되는 종속적인 변수
	// printf() 내부 평가 순서는 컴파일러에 따라 다름
	//순서를 결정짓는 습관이 중요
	printf("%d\n", time);

	return 0;
}


#endif //미로탈출시간 수정

#if 0

#define MAX_N (1000+2)
int map[MAX_N][MAX_N];
int R, C;
int sR, sC; //start
int eR, eC; //end
int cnt = 0;

typedef struct _node {
	int r, c, t;
}node;
int front, rear;
node Queue[MAX_N * MAX_N];
void Enqueue(node data) {
	Queue[rear++] = data;
}

node Dequeue(void) {
	return Queue[front++];
}

void inputData(void) {
	front = rear = 0;
	char tmp[MAX_N] = { 0 };

	scanf("%d %d", &C, &R);
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			scanf("%d", &(map[i][j]));
			if (map[i][j] == 0)
				cnt++;
			if (map[i][j] == 1)
				Enqueue((node) { i, j, 0 });
		}
	}
}
int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

int BFS(int sR, int sC) {
	int nR, nC;
	int time = 0;
	node curr;

	while (front != rear) {				//q에 존재시 반복
		curr = Dequeue();

		for (int i = 0; i < 4; i++) {     //인접점 탐색 후 존재시 enqueue 및 방문표시
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];

			if ((map[nR][nC] == 0) && (nR > 0) && (nC > 0) && (nR <= R) && (nC <= C)) {
				time = curr.t + 1;
				Enqueue((node) { nR, nC, time });
				map[nR][nC] = 1;
				cnt--;
			}
		}
	}
	if (cnt > 0)
		return -1;
	return curr.t;
}

int main(void) {
	int N, M;
	(void)freopen("j2613.txt", "r", stdin);
	inputData();
	int time = BFS(sR, sC);
	printf("%d\n", time);

	return 0;
}


#endif //토마토


#if 0

#define MAX_N (100+2)
int map[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
int N;
int R, C;

typedef struct _node {
	int r, c;
}node;
int front, rear;
node Queue[MAX_N * MAX_N*10];
void Enqueue(node data) {
	Queue[rear++] = data;
}

node Dequeue(void) {
	return Queue[front++];
}

void inputData(void) {
	front = rear = 0;

	scanf("%d %d %d", &N, &R, &C);

	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < MAX_N; j++)
			visited[i][j] = 0x7fffffff;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &(map[i][j]));
			if ((i == 1) || (i == N) || (j == 1) || (j == N)) {
				Enqueue((node) { i, j});

				visited[i][j] = map[i][j] * map[i][j];
			}
		}
	}
}
int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };



int BFS(void) {
	int nR, nC;
	node curr;

	while (front != rear) {				//q에 존재시 반복
		curr = Dequeue();

		if ((curr.r == R) && (curr.c == C))
			continue;
		for (int i = 0; i < 4; i++)
		{     //인접점 탐색 후 존재시 enqueue 및 방문표시
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];

			if ((nR > 0) && (nC > 0) && (nR <= N) && (nC <= N))
			{ //경계 만족
				int next = map[nR][nC];
				int current = map[curr.r][curr.c];
				int dcost;


				if (current == next)
				{ // 같다면 
					if (visited[nR][nC] > visited[curr.r][curr.c])
					{
						visited[nR][nC] = visited[curr.r][curr.c];
						Enqueue((node) { nR, nC });
					}
				}
				if (current < next)
				{  //크다면 바로 등산(enq)
					dcost = (next - current) * (next - current);
					if (visited[nR][nC] > visited[curr.r][curr.c] + dcost)
					{
						visited[nR][nC] = visited[curr.r][curr.c] + dcost;
						Enqueue((node) { nR, nC });
					}
				}
				if (current > next)
				{  //작다면 바로 등산(enq)
					dcost = (current - next);
					if (visited[nR][nC] > visited[curr.r][curr.c] + dcost)
					{
						visited[nR][nC] = visited[curr.r][curr.c] + dcost;
						Enqueue((node) { nR, nC });
					}
				}
			}
		}
	}
	return visited[R][C];
}

int main(void) 
{
	(void)freopen("j1111.txt", "r", stdin);
	inputData();
	int min = BFS();
	printf("%d\n", min);


	return 0;
}


#endif //등산로





#if 0
// ����
#define MAX_N (100 + 2)
#define INF (10000)
int map[MAX_N][MAX_N];
int cost[MAX_N][MAX_N]; //�ش� ��ǥ������ ��� ����
int N;
int dR, dC; // �� ���� ��ǥ
typedef struct _node {
	int r;
	int c;
}node;
node Queue[MAX_N * MAX_N * 10];
int front, rear;

void inputData(void) {
	(void)scanf("%d", &N);
	(void)scanf("%d %d", &dR, &dC);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cost[i][j] = INF;
		}
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			(void)scanf("%d", &map[i][j]);
			if ((i == 1) || (i == N) || (j == 1) || (j == N)) {
				Queue[rear++] = (node){ i, j };
				cost[i][j] = map[i][j] * map[i][j];
			}
		}
	}
}

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int BFS(void) {
	int nR, nC, i;
	node curr;
	int nCost; // curr -> (nR, nC)�� ���� �߰����

	while (front != rear) {
		curr = Queue[front++];
		if (curr.r == dR && curr.c == dC) continue; // ���� ���������� Ž�� �� X

		for (i = 0; i < 4; i++) {
			nR = curr.r + dx[i];
			nC = curr.c + dy[i];

			if (nR < 1 || nR > N || nC < 1 || nC > N) continue; // ��� �˻�

			nCost = map[curr.r][curr.c] - map[nR][nC];
			if (nCost < 0) nCost *= nCost;

			if (cost[nR][nC] > cost[curr.r][curr.c] + nCost) {
				cost[nR][nC] = cost[curr.r][curr.c] + nCost;
				Queue[rear++] = (node){ nR, nC };
			}
		}
	}
	return cost[dR][dC];
}
int main(void) {
	(void)freopen("J1111.txt", "r", stdin);
	inputData();
	printf("%d\n", BFS());
	printf("front = %d\n", front);
	return 0;
}

#endif // 등산로1


#if 0

#define MAX_N (100+2)
int N;
int e_X, e_Y;
int map[MAX_N][MAX_N] = { 0 };
int map_cost[MAX_N][MAX_N] = { 0 };

int dX[4] = { -1, 1, 0, 0 };
int dY[4] = { 0, 0, -1, 1 };

typedef struct _node {
	int x;
	int y;
	int cost;
}node;

node Queue[MAX_N * MAX_N * 10];
int front = 0, rear = 0;


void input_data() {

	(void)scanf("%d", &N);
	(void)scanf("%d %d", &e_X, &e_Y);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			(void)scanf("%d", &map[i][j]);
			map_cost[i][j] = 2500;
		}

		Queue[rear++] = (node){ 0, i, 0 };
		Queue[rear++] = (node){ i, 0, 0 };
		Queue[rear++] = (node){ N + 1, i, 0 };
		Queue[rear++] = (node){ i, N + 1, 0 };

	}
}

void print_map() {

	for (int i = 0; i <= N + 1; i++)
	{
		for (int j = 0; j <= N + 1; j++)
		{
			printf("%d ", map_cost[i][j]);
		}
		printf("\n");
	}

}

int cost_calcul(int c_map, int n_map) {

	if (c_map >= n_map) return c_map - n_map;
	else if (c_map < n_map) return (c_map - n_map) * (c_map - n_map);

	return 0;
}

void BFS(void) {

	int m_X, m_Y;
	int cX, cY, cost;

	while (front != rear) {

		node curr;
		curr = Queue[front++];

		cX = curr.x;
		cY = curr.y;
		cost = curr.cost;

		//printf("x = %d y = %d cost = %d\n", curr.x, curr.y, cost);

		if (cost > map_cost[cX][cY]) {
			//printf("skip || x = %d y = %d cost = %d, map_cost = %d\n", curr.x, curr.y, cost, map_cost[cX][cY]);
			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			m_X = cX + dX[i];
			m_Y = cY + dY[i];

			int m_cost = cost + cost_calcul(map[cX][cY], map[m_X][m_Y]);

			if (map[m_X][m_Y] != 0 && map_cost[m_X][m_Y] > m_cost)
			{
				//printf("next || x = %d y = %d cost = %d\n", m_X, m_Y, m_cost);
				Queue[rear++] = (node){ m_X, m_Y, m_cost };
				map_cost[m_X][m_Y] = m_cost;
			}
		}
	}
}

int main() {

	(void)freopen("J1111.txt", "r", stdin);

	input_data();
	//print_map();
	BFS();
	printf("%d\n", map_cost[e_X][e_Y]);
	printf("front = %d\n", front);

	return 0;
}

#endif // 등산로2


#if 0

#define MAX_N (100+2)
int map[MAX_N][MAX_N];
int M, N;
int sR, sC, sD; //start
int eR, eC, eD; //end
int cnt = 0;

typedef struct _ROBOT {
	int r, c;
	int direction; //enum
	int	prev_cmd; // if go, go_count++, no cmd_count++
	int	go_count; // if 3 < go_count, cmd_count++
	int cmd_count;
}ROBOT;

enum {
	east = 1,
	west,
	south,
	north,
};

enum {
	UN_define,
	GO,
	TURN_r,
	TURN_l,
};


int front, rear;

ROBOT Queue[MAX_N * MAX_N];

void Enqueue(ROBOT data) {
	Queue[rear++] = data;
}

ROBOT Dequeue(void) {
	return Queue[front++];
}

void inputData(void) {

	memset(map, 1, sizeof(map));

	scanf("%d %d", &M, &N);

	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	scanf("%d %d %d %d %d %d", &sR, &sC, &sD, &eR, &eC, &eD );
	/*
	for (int i = 0; i <= M+1; ++i) {
		for (int j = 0; j <= N+1; ++j) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}*/

}
int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

int BFS(int sR, int sC) {
	int nR, nC;
	ROBOT curr;

	front = rear = 0;			//bfs 여러번 수행시 초기화 필요
	Enqueue((ROBOT) { sR, sC, sD, UN_define, 0, 0});


	while (front != rear) {				//q에 존재시 반복
		curr = Dequeue();
		if ((curr.r == eR) && (curr.c == eC) && (curr.direction == eD))
			return curr.cmd_count;

		for (int i = 0; i < 4; i++) {     //인접점 탐색
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];     // 동 = 1, 서 = 2, 남 = 3, 북 = 4

			if ((map[nR][nC] == 0)) {
				
			}
		}
	}
	return 0;
}

int main(void) {
	(void)freopen("B1726.txt", "r", stdin);
	inputData();

	int  = BFS(sR, sC);

	
	//printf("%d\n", );

	return 0;
}


#endif //로봇
