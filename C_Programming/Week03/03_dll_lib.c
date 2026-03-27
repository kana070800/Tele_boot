#include "03_dll.h"

void print_DLLMode(DLL_node* Head) {
	DLL_node* curr;
	for (curr = Head; curr != NULL; curr = curr->next) {
		printf("%s\n", curr->data);
	}

}


DLL_node* DLL_CreateNode(DLLElent in_data) {
	DLL_node* new_node;
	new_node = (DLL_node*)calloc(1, sizeof(DLL_node));

	if (new_node == NULL)
		return NULL;

	new_node->data = in_data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void Append_DLLNode(DLLElent in_data, DLL_node* target) {
	DLL_node* new_node = DLL_CreateNode(in_data);

	new_node->prev = target->prev;
	new_node->next = target;
	target->prev = new_node;
	new_node->prev->next = new_node;

	/*
	Prev = target->prev;
	new_node->prev = target->prev;
	new_node->next = target;
	Prev = new_node;
	target->prev = new_node;
	3~4 번째 순서가 바뀌어도 이상 없음
	*/
}

DLL_node* Search_DLLNode(DLLElent in_data, DLL_node* Head) {
	DLL_node* curr = Head;
	while (curr->next) {
		curr = curr->next;
		if (!strcmp(curr->data, in_data))
			return curr;
	}
	return NULL;
}

int Delete_DLLNode(DLLElent in_data, DLL_node* Head) {
	DLL_node* del = Search_DLLNode(in_data, Head);

	if (del == NULL)
		return -1;
	del->next->prev = del->prev;
	del->prev->next = del->next;

	free(del);
	return 0;
}







int InsertFront_DLLNode(DLLElent data, DLL_node* Head) {
	DLL_node* new_node = DLL_CreateNode(data);
	if (new_node == NULL)
		return -1;

	new_node->prev = Head;
	new_node->next = Head->next;
	Head->next = new_node;
	new_node->next->prev = new_node;

	return 0;
}
int InsertAfter_DLLNode(DLLElent data, DLL_node* target) {
	DLL_node* new_node = DLL_CreateNode(data);
	if (new_node == NULL)
		return -1;

	new_node->prev = target;
	new_node->next = target->next;
	target->next = new_node;
	new_node->next->prev = new_node;

	return 0;
}
int InsertBefore_DLLNode(DLLElent data, DLL_node* target) {
	DLL_node* new_node = DLL_CreateNode(data);
	if (new_node == NULL)
		return -1;

	new_node->next = target;
	new_node->prev = target->prev;
	target->prev = new_node;
	new_node->prev->next = new_node;

	return 0;
}

int Insert_DLLNode(DLLElent data, DLL_node* t_prev, DLL_node* t) {
	DLL_node* new_node = DLL_CreateNode(data);
	if (new_node == NULL)
		return -1;

	new_node->next = t;
	new_node->prev = t_prev;
	t->prev = new_node;
	t_prev->next = new_node;

	return 0;
}



DLL_node* Search_P_Node(DLLElent data, DLL_node* Head, DLL_node* Tail) {
	DLL_node* curr = Head;
	while (curr != Tail) {
		curr = curr->next;
		if (1 == strcmp(curr->data, data))
			return curr->prev;
	}
	return Tail->prev;
}


void Enqueue(DLLElent data, DLL_node* Head, DLL_node* Tail) {

	DLL_node* prev = Search_P_Node(data, Head, Tail);
	//if (!prev)
		//return;

	Insert_DLLNode(data, prev, prev->next);
	return;
}
//
DLL_node* Dequeue(DLL_node* Head, DLL_node* Tail) {

	if (Head->next == Tail)
		return NULL;
	DLL_node* tmp = Head->next;

	Head->next->next->prev = Head;
	Head->next = Head->next->next;
	
	return tmp;
}