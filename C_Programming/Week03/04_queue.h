#ifndef _Q_H_
#define _Q_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

#define MAX_N (5)

typedef struct QElement {
	int r;
	int c;
}QElement;  //q의 각 노드

typedef int (*enQ_fn)(QElement, struct _arrQueue*);  //구조체 정의는 전체 스코프
typedef int (*deQ_fn)(struct _arrQueue*);  //구조체 정의는 전체 스코프

typedef struct _arrQueue {
	int capacity;  //q element의 최대 개수
	int front;
	int rear;
	QElement* nodes;   //q 관리 구조체

	enQ_fn enq;
	deQ_fn deq;
}ArrQueue;


/*
typedef struct _Qnode {
	QElement data;
	struct _Qnode* next;
	struct _Qnode* prev;
}Qnode;
*/


ArrQueue* Create_ArrQueue(int n);
ArrQueue* Create_ArrQueue1(int n, enQ_fn func, deQ_fn f1);
int EnQueue(QElement data, ArrQueue* q);
QElement* DeQueue(ArrQueue* q);

int Circular_EnQueue(QElement data, ArrQueue* q);
QElement* Circular_DeQueue(ArrQueue* q);

#endif