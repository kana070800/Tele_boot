#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int HeapElement;
typedef struct _heapnode {
    int r;
    int c;
    HeapElement cost;
}HeapNode;

typedef struct _heap {
    HeapNode* nodes;
    int capacity;
    int usedsize;
}Heap;

HeapNode Heap_Delete(Heap* heap);
void Heap_Insert(Heap* heap, HeapNode data);
void Heap_Print(Heap* heap);
Heap* Heap_Create(int capacity);

#if 01
// 등산로
#define MAX_N (100 + 2)
#define INF (10000)
int map[MAX_N][MAX_N];

int N;
int dR, dC; // 산 정상 좌표
typedef struct _node {
    int r;
    int c;
}node;
node Queue[MAX_N * MAX_N * 10];
int front, rear;

void inputData(Heap* heap) {
    (void)scanf("%d", &N);
    (void)scanf("%d %d", &dR, &dC);


    front = rear = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            (void)scanf("%d", &map[i][j]);
            if ((i == 1) || (i == N) || (j == 1) || (j == N)) {
                Heap_Insert(heap,(HeapNode){i, j, map[i][j] * map[i][j]});
            }
        }
    }
}

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int BFS(heap) {
    int nR, nC, i;
    HeapNode curr;
    int nCost; // curr -> (nR, nC)로 가는 추가비용

    while (1) {
        HeapNode curr = Heap_Delete(heap);
        if (curr.r == dR && curr.c == dC)
            return curr.cost;
        

        for (i = 0; i < 4; i++) {
            nR = curr.r + dx[i];
            nC = curr.c + dy[i];

            if (nR < 1 || nR > N || nC < 1 || nC > N) continue; // 경계 검사

            nCost = map[curr.r][curr.c] - map[nR][nC];
            if (nCost < 0) nCost *= nCost;

            Heap_Insert(heap, (HeapNode) { nR, nC, curr.cost + nCost });
            
        }
    }
}

int main(void) {
    (void)freopen("J1111.txt", "r", stdin);
    Heap* heap = Heap_Create(1000);
    inputData(heap);
    printf("%d\n", BFS(heap));
    printf("front = %d\n", front);
    return 0;
}
//

Heap* Heap_Create(int capacity) {
    Heap* temp = (Heap*)calloc(1, sizeof(Heap));
    if (temp == NULL) {
        return NULL;
    }
    temp->nodes = (HeapNode*)calloc(capacity + 1, sizeof(HeapNode));
    if (temp->nodes == NULL) {
        free(temp);
        return NULL;
    }
    temp->capacity = capacity + 1;
    temp->usedsize = 0;
    return temp;
}

int min_child(Heap* heap, int index) {
    int tmp = 2 * index;

    if (tmp > heap->usedsize)
        return 0;
    if (tmp + 1 < heap->usedsize)
        if (heap->nodes[tmp + 1].cost < heap->nodes[tmp].cost)
            tmp = 2 * index + 1;
    return tmp;
}

HeapNode Heap_Delete(Heap* heap) {
    HeapNode res = heap->nodes[1];
    HeapNode data = heap->nodes[heap->usedsize--];
    int index = 1;
    int m_child;

    while (1) {
        m_child = min_child(heap, index); //min index 반환
        HeapNode hubo = heap->nodes[m_child];

        if ((m_child == 0) || (hubo.cost > data.cost)) {
            heap->nodes[index] = data;
            break;
        }

        heap->nodes[index] = hubo;
        index = m_child;
    }
    return res;
}

// 성공 시 1, 실패 시 0 반환
static int Heap_Resize(Heap* heap, int additional) {
    int new_capacity = heap->capacity + additional;
    HeapNode* new_nodes = realloc(heap->nodes, (new_capacity) * sizeof(HeapNode));
    if (new_nodes == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }
    heap->nodes = new_nodes;
    heap->capacity = new_capacity;
    return 1;
}

// 효율적인 동작을 함 (부모에 있는 값을 자식으로 내리는 동작만 하고, 마지막에 한 번만 data를 저장함)
void Heap_Insert(Heap* heap, HeapNode data)
{
    
    int index = ++heap->usedsize;

    if (heap->usedsize == (heap->capacity)) {
        heap->nodes[heap->capacity] = data;
    }

    HeapNode* nodes = heap->nodes;
    while (index > 1 && nodes[index / 2].cost > data.cost)
    {
        nodes[index] = nodes[index / 2];
        index >>= 1;  //  index /= 2;  //  컴파일러가 최적화해줌
    }

    nodes[index] = data;
}

void Heap_Print(Heap* heap) {
    for (int i = 1; i <= heap->usedsize; ++i) {
        printf("%d ", heap->nodes[i].cost);
    }
    printf("\n");
}


#endif