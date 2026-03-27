#include "tree.h"


#if 0

int main(void) {

	Tnode* Root = NULL;

	Root = Tree_CreateNode('/');
	Root->left = Tree_CreateNode('+');
	Root->right = Tree_CreateNode('*');
	
	Root->left->left = Tree_CreateNode('4');
	Root->left->right = Tree_CreateNode('3');

	Root->right->left = Tree_CreateNode('1');
	Root->right->right = Tree_CreateNode('2');
	
	
	Tree_Porder_Print(Root);
	printf("\n");
	Tree_Morder_Print(Root);
	printf("\n");
	//Tree_Border_Print(Root);

	Tree_Destroy(Root);

	return 0;
}


#endif

#if 0
int main(void)
{
	Heap* heap = Heap_Create(20);


	Hnode x[20] = { 2, 8, 52, 13, 37, 67, 161, 17, 43, 88 };
	memcpy(heap->nodes + 1,x,sizeof(x));
	heap->usedsize = 10;
	
	Heap_Insert(heap, 7);
	
	Heap_print(heap);


	printf("\n");
	printf("%d", (Heap_Delete(heap)).data);
	printf("\n");
	Heap_print(heap);
	printf("\n");
	printf("%d", Heap_Delete(heap).data);
	printf("\n");
	Heap_print(heap);
	//printf(" %d", (int)(3 / 2)); // 1
	//

	return 0;
}


#endif