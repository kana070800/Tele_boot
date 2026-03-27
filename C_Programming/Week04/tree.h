#ifndef _TREE_H_
#define _TREE_H_



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))





typedef char TElement;
typedef struct _treenode {


	TElement data;
	struct _treenode* left;
	struct _treenode* right;

}Tnode;




typedef int HElement;
typedef struct _heapnode {
	HElement data;
}Hnode;

typedef struct _heap {
	Hnode* nodes;
	int capacity;
	int usedsize;
}Heap;

Heap* Heap_Create(int capacity);
Hnode Heap_Delete(Heap * heap);
void Heap_Insert(Heap* heap, HElement data);

#endif