#include "04_queue.h"

#if 0

int main(void) {
	ArrQueue * Queue = Create_ArrQueue(5);
	//printf("%d %d", Queue->capacity, sizeof(*Queue->nodes));
	/*
	(Queue->nodes + 1)->r = 1;
	(Queue->nodes + 1)->c = 2;  //  Queue->nodes[1].c
	printf("\n%d %d\n", (Queue->nodes + 1)->r, (Queue->nodes + 1)->c);
	*/

	for (int i = 0; i < 7; ++i) {
		int r = EnQueue((QElement) { i, i+1 }, Queue);
		if (r == 1)
			printf("%d %d\n", (Queue->nodes + i)->r, (Queue->nodes + i)->c);

	}

	QElement* rq = DeQueue(Queue);
	if (rq)
		printf("%d %d\n", rq->r, rq->c);

	rq = DeQueue(Queue);
	if (rq)
		printf("%d %d\n", rq->r, rq->c);

	return 0;
}

#endif

#if 0
int main(void) {
	ArrQueue* Queue = Create_ArrQueue1(5, EnQueue, DeQueue);

	for (int i = 0; i < 7; ++i) {
		int r = Queue->enq((QElement) { i, i + 1 }, Queue);
		if (r)
			printf("%d %d\n", (Queue->nodes + i)->r, (Queue->nodes + i)->c);
	}
	QElement* rq;
	for (int i = 0; i < 7; ++i) {
		rq = Queue->deq(Queue);
		if (rq)
			printf("%d %d\n", rq->r, rq->c);
	}

	return 0;
}

#endif


#if 01
int main(void) {
	ArrQueue* Queue = Create_ArrQueue1(5, Circular_EnQueue, Circular_DeQueue);

	for (int i = 0; i < 8; ++i) {
		int r = Queue->enq((QElement) { i, i + 1 }, Queue);
		if (r)
			printf("%d %d\n", (Queue->nodes + i)->r, (Queue->nodes + i)->c);
	}

	QElement* rq;
	for (int i = 0; i < 3; ++i) {
		rq = Queue->deq(Queue);
		if (rq)
			printf("%d %d\n", rq->r, rq->c);
	}

	for (int i = 0; i < 7; ++i) {
		int r = Queue->enq((QElement) { i, i + 1 }, Queue);
		if (r)
			printf("%d %d\n", (Queue->nodes + i)->r, (Queue->nodes + i)->c);
	}

	for (int i = 0; i < 10; ++i) {
		rq = Queue->deq(Queue);
		if (rq)
			printf("%d %d\n", rq->r, rq->c);
	}


	return 0;
}

#endif

