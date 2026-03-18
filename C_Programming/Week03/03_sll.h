#ifndef _SLL_H_
#define _SLL_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

typedef int ElementType;
typedef struct _node {
	ElementType data;
	struct _node* next;

}SLL_node;



void print_SLLnode(SLL_node* curr);
SLL_node* SLL_CreateNode(ElementType * data);
void SLL_AppendNode(SLL_node** Head, SLL_node* new_node);
void SLL_AppendNode1(SLL_node** Head, SLL_node** Tail, SLL_node* new_node);
#endif