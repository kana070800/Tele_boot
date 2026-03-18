#include "03_sll.h"

extern SLL_node* Head;

void print_SLLnode(SLL_node * Head) {
	SLL_node* curr;
	for (curr = Head; curr != NULL; curr = curr->next) {
		printf("%d ", curr->data);
	}

}

SLL_node* SLL_CreateNode(ElementType *in_data) {
	SLL_node* new_node;
	new_node = (SLL_node*)calloc(1, sizeof(SLL_node));

	if (new_node == NULL)
		return NULL;

	new_node->data = *in_data;
	new_node->next = NULL;

	return new_node;
}

void SLL_AppendNode(SLL_node** Head, SLL_node* new_node) {
	if (Head == NULL) return;

	SLL_node* curr = *Head;
	
	if (curr == NULL) {
		*Head = new_node;
	}
	else {
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = new_node;

	}
	return;
}

void SLL_AppendNode1(SLL_node** Head, SLL_node** Tail, SLL_node* new_node) {
	if (Head == NULL) return;


	if (*Head == NULL) {
		*Head = new_node;
		*Tail = new_node;
	}
	else {
		(*Tail)->next = new_node;
		*Tail = new_node;
	}
	return;
}