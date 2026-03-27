#include "tree.h"
#if 0
Tnode* Tree_CreateNode(TElement data)
{
	Tnode* res = (Tnode*)calloc(1, sizeof(Tnode));
	if (!res)
		return NULL;
	
	res->data = data;

	res->left = NULL;
	res->right = NULL;
	return res;
}


void Tree_Porder_Print(Tnode* node){

	printf("%c", node->data);
	if (node->left)
		Tree_Porder_Print(node->left);
	if (node->right)
		Tree_Porder_Print(node->right);

	return;
}


void Tree_Morder_Print(Tnode* node) {

	if (node->left)
		Tree_Morder_Print(node->left);
	printf("%c", node->data);
	if (node->right)
		Tree_Morder_Print(node->right);

	return;
}

void Tree_Border_Print(Tnode* node) {

	if (node->left)
		Tree_Border_Print(node->left);
	if (node->right)
		Tree_Border_Print(node->right);
	printf("%c", node->data);
	return;
}

void Tree_Destroy(Tnode* node) {

	if (node->left)
		Tree_Destroy(node->left);
	if (node->right)
		Tree_Destroy(node->right);
	free(node);
	return;
}



Heap* Heap_Create(int capacity) {

	Heap* tmp = (Heap*)calloc(1, sizeof(Heap));
	if (tmp == NULL)
		return NULL;
	tmp->nodes = (Hnode*)calloc(capacity, sizeof(Hnode));
	if ((tmp->nodes) == NULL) {
		free(tmp);
		return NULL;
	}
	tmp->capacity = capacity+1;
	tmp->usedsize = 0;

	return tmp;

}


void Heap_Insert(Heap *heap, HElement data) {
	int index = ++(heap->usedsize);
	Hnode tmp;
	Hnode* arr = heap->nodes;

	arr[index].data = data;

	while (index != 1) {

		int pindex = index / 2;

		if (arr[pindex].data < data)
			break;

		tmp = arr[pindex];
		arr[pindex] = arr[index];
		arr[index] = tmp;

		index = pindex;
	}
}

void Heap_print(Heap* heap) {
	for (int i = 1; i <= heap->usedsize; i++)
		printf("%d ", (*(heap->nodes + i)).data);
}
///
int min_child(Heap* heap, int index) {
	int tmp = 2 * index;

	if (tmp > heap->usedsize)
		return 0;
	if (tmp + 1 < heap->usedsize) 
		if (heap->nodes[tmp + 1].data < heap->nodes[tmp].data)
		tmp = 2 * index + 1;
	return tmp;
}
/*
HElement Heap_Delete(Heap* heap) {
	HElement res = heap->nodes[1].data;
	int data = heap->nodes[heap->usedsize--].data;
	int index = 1;
	int m_child;

	while (1) {
		m_child = min_child(heap, index); //min index 반환
		int hubo = heap->nodes[m_child].data;
		
		if ((m_child == 1) || (hubo > data)) {
			heap->nodes[index].data = data;
			break;
		}
		
		heap->nodes[index].data = hubo;
		index = m_child;
	}
	return res;
}*///

Hnode Heap_Delete(Heap* heap) {
	Hnode res = heap->nodes[1];
	Hnode data = heap->nodes[heap->usedsize--];
	int index = 1;
	int m_child;

	while (1) {
		m_child = min_child(heap, index); //min index 반환
		Hnode hubo = heap->nodes[m_child];

		if ((m_child == 0) || (hubo.data > data.data)) {
			heap->nodes[index] = data;
			break;
		}

		heap->nodes[index] = hubo;
		index = m_child;
	}
	return res;
}
#endif