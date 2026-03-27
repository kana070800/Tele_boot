

//1번
#if 01
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

int map[20][20] = { 0 };
int win = 0;
int x, y;

void inputData(void) {

    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j < 20; ++j) {
            (void)scanf("%d", &map[i][j]);
        }
    }
}

void one(int i, int j, int team) {
   
    if (map[i][j + 1] == team)
        if (map[i][j + 2] == team)
            if (map[i][j + 3] == team)
                if (map[i][j + 4] == team) {
                    if (map[i][j + 5] == team)
                        return;
                    win = team;
                    x = i;
                    y = j;
                }
    if (map[i + 1][j + 1] == team)
        if (map[i + 2][j + 2] == team)
            if (map[i + 3][j + 3] == team)
                if (map[i + 4][j + 4] == team) {
                    if (map[i+5][j + 5] == team)
                        return;
                    win = team;
                    x = i;
                    y = j;
                }
    if (map[i + 1][j] == team)
        if (map[i + 2][j] == team)
            if (map[i + 3][j] == team)
                if (map[i + 4][j] == team) {
                    if (map[i + 5][j] == team)
                        return;
                    win = team;
                    x = i;
                    y = j;
                }
    if (map[i + 1][j - 1] == team)
        if (map[i + 2][j - 2] == team)
            if (map[i + 3][j - 3] == team)
                if (map[i + 4][j - 4] == team) {
                    if (map[i + 5][j - 5] == team)
                        return;
                    win = team;
                    x = i;
                    y = j;
                }
    if (map[i - 1][j + 1] == team)
        if (map[i - 2][j + 2] == team)
            if (map[i - 3][j + 3] == team)
                if (map[i - 4][j + 4] == team) {
                    if (map[i - 5][j + 5] == team)
                        return;
                    win = team;
                    x = i;
                    y = j;
                }
    return;
}

void N_Q() {
   
    for (int i = 1; i < 20; ++i)
    {
        for (int j = 1; j < 20; ++j) {
            if (map[i][j] != 0) {
                one(i, j, map[i][j]);
            }
        }
    }
}

int main(void) {

    inputData();
    N_Q();
    printf("%d\n", win);

    if (win)
        printf("%d %d", x, y);
    return 0;
}


#endif 


//2번
#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

int N;
int* x = NULL;
int map[100][100];
int cnt = 0;

void inputData(void) {

    for (int i = 0; i < N; ++i) {
        (void)scanf("%d %d", &x[2*i], &x[2*i+1]);
    }
}
//
int main(void) {
    scanf("%d", &N);
    x = (int*)calloc(2 * N, sizeof(int));
    inputData();

    for (int i = 0; i <N; ++i) {
        
        for (int j = x[2 * i]; j < x[2 * i] + 10; j++) {
            for (int k = x[2 * i+1]; k < x[2 * i+1] + 10; k++) {
                if ((map[j][k] != 1) && (j < 100) && (k < 100)) {

                    map[j][k] = 1;
                    cnt++;
                }
            }

        }
    }

    printf("%d", cnt);
	return 0;
}

#endif 



//3번
#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))


int R, C;
char tmp[50];
int map[50][50] = {0};
int timemap[50][50] = { 0 };


typedef struct _node {
    int r, c;
}node;
int front, rear;
node q[50 * 50];
void Enqueue(node data) {
    q[rear++] = data;
}

node Dequeue(void) {
    return q[front++];
}


void inputData(void) {

    for (int i = 0; i < R; ++i) {
        (void)scanf("%s", tmp);
        for (int j = 0; j < C; j++) {
            if (tmp[j] == 'L')
                map[i][j] = 1;
        }
    }
}

int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

int BFS() {
    int nR, nC;
    int time = 0;
    node curr;

    while (front != rear) {				//q에 존재시 반복
        curr = Dequeue();

        for (int i = 0; i < 4; i++) {     //인접점 탐색 후 존재시 enqueue 및 방문표시
            nR = curr.r + dR[i];
            nC = curr.c + dC[i];

            if ((map[nR][nC] == 1) && (nR >= 0) && (nC >= 0) && (nR < R) && (nC < C)) {
                if (((timemap[curr.r][curr.c] + 1) < timemap[nR][nC])||(timemap[nR][nC] == 0)) {
                    timemap[nR][nC] = timemap[curr.r][curr.c] + 1;
                    Enqueue((node) { nR, nC });
                    map[nR][nC] = 1;
                    if (time < timemap[nR][nC])
                        time = timemap[nR][nC];
                }
            }
        }
    }
    memset(timemap, 0, sizeof(timemap));
    return time;
}






int main(void) {
    int tmp = 0;
    int min = 0;
    scanf("%d %d", &R,&C);
    getchar();
    inputData();


    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (map[i][j] == 1) {
                Enqueue((node) { i, j });
                tmp = BFS();
                if (tmp > min)
                    min = tmp;
            }
        }
    }
    printf("%d\n", min);
	return 0;
}

#endif 


//4번
#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))


int R, C, N;
int* tmp;

typedef struct _node {
    int one, two, cnt, L;
}node;
int front, rear;
node q[50 * 50];
void Enqueue(node data) {
    q[rear++] = data;
}

node Dequeue(void) {
    return q[front++];
}


void inputData(void) {
    (void)scanf("%d", &N);
    (void)scanf("%d %d", &R, &C);

    tmp = (int*)calloc(N-2, sizeof(int));

    for (int i = 0; i < N-2; ++i) {
        (void)scanf("%s", tmp+i);
    }
}


int BFS() {
    int min = 0xfffffff;
    node curr;

    while (front != rear) {
        curr = Dequeue();

        if (curr.L > N - 2) {
            if (curr.cnt < min)
                min = curr.cnt;
            continue;
        }
        int temp = R - tmp[curr.L];
        if (temp < 0) {
            temp = -temp;
        }
        Enqueue((node) { tmp[curr.L], curr.two, curr.cnt + temp, curr.L + 1 });

        temp = C - tmp[curr.L];
        if (temp < 0) {
            temp = -temp;
        }
        Enqueue((node) { curr.one, tmp[curr.L], curr.cnt + temp, curr.L + 1 });

    }
    return min;
}



int main(void) {
   
    inputData();

    Enqueue((node){ R, C, 0 ,0});

    int min = BFS();

    printf("%d\n", min);
    return 0;
}

#endif 