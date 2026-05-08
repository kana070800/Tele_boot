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


#endif //hanoi

#if 0

// code for baekjoon : 24444

#include <stdio.h>
#include <stdlib.h>
int N = 0;
int M = 0;
int R = 0;
int** space = NULL;
int* visited = NULL;

int cnt = 1;
int MAX_Na = 0;

typedef int QElement;

typedef struct _arrQueue {
    int capacity;
    int front;
    int rear;
    QElement* nodes;
}ArrQueue;

ArrQueue* Queue;


ArrQueue* Create_ArrQueue(int n) {
    ArrQueue* res = (ArrQueue*)calloc(1, sizeof(ArrQueue));
    if (res == NULL)
        return NULL;
    res->nodes = (QElement*)calloc(n, sizeof(QElement));
    if (res->nodes == NULL)
        return NULL;

    res->capacity = n;

    return res;
}

int EnQueue(QElement data, ArrQueue* q)
{
    int next = (q->rear + 1) % q->capacity;
    if (next == q->front)
    {
        return 0;
    }

    *(q->nodes + (q->rear)) = data;
    q->rear = next;
    return 1;
}

QElement* DeQueue(ArrQueue* q)
{
    if (q->rear == q->front)
    {
        return NULL;
    }
    QElement* tmp = (q->nodes + q->front);
    q->front = (q->front + 1) % q->capacity;
    return tmp;
}





int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void bfs(int st) {
    visited[R] = 1;

    EnQueue(R, Queue);

    while (Queue->front != Queue->rear) {
        QElement* node = DeQueue(Queue);
        printf("%d\n", *node);
        for (int i = 1; i <= space[*node][0]; ++i) {
            int next = space[*node][i];
            if (visited[next] == 0) {
                visited[next] = 1;
                EnQueue((QElement)next, Queue);
            }
        }
    }
    for (int i = 1; i <= N; i++)
        if (visited[i] == 0)
            printf("0\n");
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &R);

    space = (int**)calloc((N + 1), sizeof(int*));
    visited = (int*)calloc(N + 1, sizeof(int));



    int* buf = (int*)calloc(2 * M, sizeof(int));


    for (int i = 0; i < M; ++i) {
        int from, to;
        scanf("%d %d", &from, &to);
        buf[i * 2] = from;
        buf[i * 2 + 1] = to;
        visited[buf[i * 2]]++;
    }


    for (int i = 1; i <= N; ++i) {
        *(space + i) = (int*)calloc(1 + visited[i], sizeof(int));
        MAX_Na = (MAX_Na < visited[i]) ? visited[i] : MAX_Na;
        visited[i] = 0;
    }

    Queue = Create_ArrQueue(MAX_Na * 2); //using MAX_N

    for (int j = 0; j < M; ++j) {
        space[buf[j * 2]][0]++;
        space[buf[j * 2]][space[buf[j * 2]][0]] = buf[j * 2 + 1];
    }


    free(buf);

    for (int i = 1; i <= N; ++i) {
        qsort(space[i] + 1, space[i][0], sizeof(int), compare);
    }

    bfs(R);
    return 0;
}

#endif  //bfs



//이진탐색
#if 0

int Binary_search(int* arr, int size, int value) {

    int left = 0;
    int right = size - 1;
    int mid = (right + left) / 2;
    while (left <= right) {
        mid = (right + left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        }
        else if (arr[mid] > value)
        {
            right = mid - 1;
        }
        else
            return mid;
    }
    return -1;
}

int Binary_x(int* arr, int size, int value, int i) {

    int left = i;
    int right = size - 1;
    int mid = (right + left) / 2;
    if (left <= right) {
        if (arr[mid] < value) {
            Binary_x(arr, size, value, mid + 1);
        }
        else if (arr[mid] > value)
        {
            Binary_x(arr,mid - 1,value,i);
        }
        else
            return mid;
    }
    else
        return -1;
}

int main(void)
{
    int arr[] = { 1, 3, 6, 9, 12, 13, 14, 17, 22, 25 };

    printf("%d\n", Binary_search(arr, sizeof(arr), 20)); // 그냥
    printf("%d\n", Binary_x(arr, sizeof(arr), 19, 0)); // 재귀

    


}
#endif

#if 0

int Binary_low(int* arr, int size, int value) {

    int left = 0;
    int right = size - 1;
    //int mid = (right + left) / 2;
    while (left <= right) {
        int mid = (right + left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        }
        else if (arr[mid] > value)
        {
            right = mid - 1;
        }
        else
            return mid;
    }
    if (left == size)
        return -1;
    return left;
}


int Binary_up(int* arr, int size, int value) {

    int left = 0;
    int right = size - 1;
    //int mid = (right + left) / 2;
    while (left <= right) {
        int mid = (right + left) / 2;
        //int mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        }
        else if (arr[mid] > value)
        {
            right = mid - 1;
        }
        else
            return mid;
    }

    return left - 1;
}



int main(void)
{
    int arr[] = { 1, 3, 6, 9, 12, 13, 14, 17, 22, 25 };

    printf("%d\n", Binary_low(arr, 10, 11)); // 4
    printf("%d\n", Binary_up(arr, 10, 16));  //6

    printf("%d\n", Binary_low(arr, 10, 17)); //
    printf("%d\n", Binary_up(arr, 10, 25));  

    printf("%d\n", Binary_low(arr, 10, 23)); //
    printf("%d\n", Binary_up(arr, 10, 34));

    printf("%d\n", Binary_low(arr, 10, 27)); //
    printf("%d\n", Binary_up(arr, 10, 40));

    printf("%d\n", Binary_low(arr, 10, 80));
    printf("%d\n", Binary_up(arr, 10, 80));

    printf("%d\n", Binary_low(arr, 10, -10));
    printf("%d\n", Binary_up(arr, 10, -10));
}//
#endif 


#if 0



int Binary_low(int* arr, int size, int value) {

    int left = 0;
    int right = size - 1;
    //int mid = (right + left) / 2;
    while (left <= right) {
        int mid = (right + left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        }
        else if (arr[mid] > value)
        {
            right = mid - 1;
        }
        else
            return mid;
    }
    if (left == size)
        return -1;
    return left;
}


int Binary_up(int* arr, int size, int value) {

    int left = 0;
    int right = size - 1;
    //int mid = (right + left) / 2;
    while (left <= right) {
        int mid = (right + left) / 2;
        //int mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        }
        else if (arr[mid] > value)
        {
            right = mid - 1;
        }
        else
            return mid;
    }

    return left - 1;
}

int compare(const void* a, const void* b) {
    // 비교 로직 작성
    return (*(int*)a - *(int*)b);
}

int main(void)
{
    int N, cnt = 0, first = 0, second = 0, low = 0, high = 0;
    scanf("%d", &N);

	int* arr = (int*)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    qsort(arr, N, sizeof(int), compare);


    for (int i = 0; i < N - 2; i++)//
    {
        first = arr[i];

        for (int j = i + 1; j < N - 1; j++) {
            second = arr[j];

			int d = second - first;
            low = Binary_low(arr, N, second + d);
            high = Binary_up(arr, N, second + 2*d);
            printf("%d %d | %d %d\n",i,j, low, high);
			if ((high != -1) && (low != -1))
                cnt += (high - low + 1);
        }
    }
    printf("%d\n", cnt);
    return 0;////

    //
}//1 3 4 7 10//
#endif //도약


#if 0

int func(int*a,int*b) {

    return *a - *b;
}

int main(void)
{
    int T = 0;
    int buf[10000] = { 0 };
    scanf("%d", &T);
    int sum = 0;
    int tmp = 0;
    for (int i = 0; i < T; ++i) {
        int K = 0;
        scanf("%d", &K);
        sum = 0;
        for (int j = 0; j < K; ++j) {
            scanf("%d", (buf+j));
        }
        qsort(buf, K, sizeof(int), func);

        for (int j = 0; j < K - 1; ++j) {
            buf[j + 1] += buf[j];
            sum += buf[j + 1];
            tmp = buf[j + 1];
            int k = j + 1;
            while (buf[k] > buf[k + 1]) {
                k++;
            }

            memmove(buf + j + 1, buf + j + 2, sizeof(int) * (k - j - 1));
            buf[k] = tmp;
        }
        
        
        printf("%d\n", sum);
    }

    return 0;
}
#endif


#if 0


int func(int* a, int* b) {

    return *a - *b;
}

int main(void)
{
    int T = 0;
    int buf[10000] = { 0 };
    scanf("%d", &T);
    int sum = 0;
    for (int i = 0; i < T; ++i) {
        int K = 0;
        scanf("%d", &K);
        sum = 0;
        for (int j = 0; j < K; ++j) {
            scanf("%d", (buf + j));
        }
        //qsort(buf, K, sizeof(int), func);

        for (int j = 0; j < K - 1; ++j) {
            qsort(buf + j, K - j, sizeof(int), func);

            buf[j + 1] += buf[j];
            sum += buf[j + 1];
        }


        printf("%d\n", sum);
    }

    return 0;
}
#endif
//



#if 0

int func(int* a, int* b) {

    return *a - *b;
}

typedef struct st {
    int m;
    int v;
}st;


int main(void) {
    int N, K = 0;
    scanf("%d %d", &N, &K);
    st buf[10000] = { 0 };
    st cass  = { 0 };

    int bag[10000] = { 0 };

    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &(buf[i].m), &(buf[i].v));
    }

    for (int i = 0; i < K; ++i) {
        scanf("%d", &bag[i]);
    }

    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < 1; ++j)
        {
            if (buf[j].m > bag[i])
                continue;
        }

    }

    return 0;
}
#endif