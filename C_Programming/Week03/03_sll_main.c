#include "03_sll.h"

#if 0



int main(void)
{
	SLL_node a, b, c;
	a = (SLL_node){ 10, &b };
	b = (SLL_node){ 20, &c };
	c = (SLL_node){ 30, NULL };

	SLL_node *Head = &a;

	printf("%d %d %d\n", Head->data, Head->next->data, Head->next->next->data);

	SLL_node* curr = Head;

	print_SLLnode(Head);

	/* SLL_node * curr 정의 == head 참조후 curr = curr->next */

	return 0;
}

#endif

#if 0

int main(void)
{
	SLL_node* Head = NULL;
	ElementType data = 10;
	/*
	Head = SLL_CreateNode(&data);

	data = 20;
	Head->next = SLL_CreateNode(&data);

	data = 30;
	Head->next->next = SLL_CreateNode(&data);
	*/
	SLL_AppendNode(&Head, SLL_CreateNode(&data));
	data = 20;
	SLL_AppendNode(&Head, SLL_CreateNode(&data));
	data = 30;
	SLL_AppendNode(&Head, SLL_CreateNode(&data));
	data = 40;
	SLL_AppendNode(&Head, SLL_CreateNode(&data));
	data = 50;
	SLL_AppendNode(&Head, SLL_CreateNode(&data));
	data = 60;
	SLL_AppendNode(&Head, SLL_CreateNode(&data));

	print_SLLnode(Head);

	return 0;
}
#endif //head 만 존재할 때 appendnode 구현

#if 0

int main(void)
{
	SLL_node* Head = NULL;
	SLL_node* Tail = NULL;
	ElementType data = 10;
	SLL_AppendNode1(&Head, &Tail, SLL_CreateNode(&data));
	data = 20;
	SLL_AppendNode1(&Head, &Tail, SLL_CreateNode(&data));
	data = 30;
	SLL_AppendNode1(&Head, &Tail, SLL_CreateNode(&data));
	data = 40;
	SLL_AppendNode1(&Head, &Tail, SLL_CreateNode(&data));
	data = 50;
	SLL_AppendNode1(&Head, &Tail, SLL_CreateNode(&data));
	data = 60;
	SLL_AppendNode1(&Head, &Tail, SLL_CreateNode(&data));

	print_SLLnode(Head);

	return 0;
}
#endif //head, tail 존재할 때 appendnode 구현

