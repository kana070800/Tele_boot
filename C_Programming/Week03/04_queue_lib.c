#include "04_queue.h"



ArrQueue* Create_ArrQueue1(int n, enQ_fn eq, deQ_fn dq) {

	ArrQueue* res = (QElement*)calloc(1, sizeof(ArrQueue));
	if (res == NULL) 
		return NULL;
	res->nodes = (QElement*)calloc(n, sizeof(QElement));
	if (res->nodes == NULL) 
		return NULL;

	res->capacity = n;
	res->enq = eq;
	res->deq = dq;

	return res;
}

ArrQueue* Create_ArrQueue(int n) {

	ArrQueue* res = (QElement*)calloc(1, sizeof(ArrQueue));
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
	if (q->rear >= q->capacity)
	{
		printf("overflow\n");
		return 0;
	}

	*(q->nodes + q->rear++) = data;

	return 1;
}

QElement* DeQueue(ArrQueue* q)
{
	if (q->front >= q->rear)
	{
		printf("underflow\n");
		return NULL;
	}

	return (q->nodes + q->front++);
}

/*
int Circular_EnQueue(QElement data, ArrQueue* q)
{
	if ((q->rear - q->front) >= 5)
	{
		printf("overflow\n");
		return 0;
	}

	*(q->nodes + (q->rear++)%6) = data;
	
	return 1;
}

QElement* Circular_DeQueue(ArrQueue* q)
{
	if ((q->rear - q->front) < 1)
	{
		printf("underflow\n");
		return NULL;
	}

	return (q->nodes + (q->front++)%5);
}
*/

int Circular_EnQueue(QElement data, ArrQueue* q)
{
	int next = (q->rear + 1) % q->capacity;
	if (next == q->front)
	{
		printf("overflow\n");
		return 0;
	}

	*(q->nodes + (q->rear)) = data;
	q->rear = next;
	return 1;
}

QElement* Circular_DeQueue(ArrQueue* q)
{
	if (q->rear == q->front)
	{
		printf("underflow\n");
		return NULL;
	}
	QElement* tmp = (q->nodes + q->front);
	q->front = (q->front + 1) % q->capacity;
	return tmp;
}