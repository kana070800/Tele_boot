#ifndef _DLL_H_
#define _DLL_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

typedef char * DLLElent;

typedef struct _dllnode {
	DLLElent data;
	struct _dllnode* next;
	struct _dllnode* prev;
}DLL_node;


DLL_node * DLL_CreateNode(DLLElent data);
void Append_DLLNode(DLLElent in_data, DLL_node* prev);
void print_DLLMode(DLL_node* Head);
DLL_node* Search_DLLNode(DLLElent in_data, DLL_node* Head);
int Delete_DLLNode(DLLElent in_data, DLL_node* Head);

int InsertFront_DLLNode(DLLElent data, DLL_node* Head);
int InsertAfter_DLLNode(DLLElent data, DLL_node* target);
int InsertBefore_DLLNode(DLLElent data, DLL_node* target);
int Insert_DLLNode(DLLElent data, DLL_node* t_prev, DLL_node* t);


void Enqueue(DLLElent data, DLL_node* Head, DLL_node* Tail);
DLL_node* Dequeue(DLL_node* Head, DLL_node* Tail);
DLL_node* Search_P_Node(DLLElent data, DLL_node* Head, DLL_node* Tail);
#endif