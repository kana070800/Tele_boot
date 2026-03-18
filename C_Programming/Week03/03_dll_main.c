#include "03_dll.h"

#if 0

int main(void)
{
	DLL_node* Head;
	DLL_node* Tail;
	Head = DLL_CreateNode("Head");
	Tail = DLL_CreateNode("Tail");

	Head->next = Tail;
	Tail->prev = Head;
	printf("--------------Append---------------\n");
	Append_DLLNode("dog",Tail);
	Append_DLLNode("cat", Tail);
	Append_DLLNode("rabbit", Tail);
	Append_DLLNode("human", Tail);

	print_DLLMode(Head);
	printf("\n");
	printf("--------------Search---------------\n");
	DLL_node* s;
	s = Search_DLLNode("cat", Head);
	if (s)
		printf("%s", s->data);
	printf("\n");

	printf("--------------delete---------------\n");
	if (Delete_DLLNode("rabbit", Head))
		printf("!!!!error\n");
	else
		printf("ok\n");
	if (Delete_DLLNode("dont", Head))
		printf("!!!!error\n");
	printf("\n");

	print_DLLMode(Head);


	printf("--------------insertFront---------------\n");
	if (InsertFront_DLLNode("Monkey", Head))
		printf("!!!!error\n");
	printf("\n");
	print_DLLMode(Head);

	printf("--------------insertAfter---------------\n");
	s = Search_DLLNode("cat", Head);
	if (InsertAfter_DLLNode("AAAAA", s))
		printf("!!!!error\n");
	printf("\n");
	print_DLLMode(Head);

	printf("--------------insertBefore---------------\n");
	s = Search_DLLNode("cat", Head);
	if (InsertBefore_DLLNode("BBBBB", s))
		printf("!!!!error\n");
	printf("\n");
	print_DLLMode(Head);


	printf("--------------just insert---------------\n");
	s = Search_DLLNode("cat", Head);
	if (Insert_DLLNode("monster",s->prev, s))
		printf("!!!!error\n");
	printf("\n");
	print_DLLMode(Head);

	free(Head); free(Tail);
	Head = Tail = NULL;
	return 0;
}

#endif

#if 0

typedef char Element;

typedef struct _node {
    Element data;
    struct _node* next;
    struct _node* prev;
}NODE;

enum {
    L = 1,
    D,
    B,
    P
};


NODE* _CreateNode(Element data) {
    NODE* new_node;
    new_node = (NODE*)calloc(1, sizeof(NODE));

    if (new_node == NULL)
        return NULL;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}
void Append_Node(Element in_data, NODE* Tail) {
    NODE* new_node = _CreateNode(in_data);

    new_node->prev = Tail->prev;
    new_node->next = Tail;
    Tail->prev = new_node;
    new_node->prev->next = new_node;
}

void print_Node(NODE* Head, NODE* Tail) {
    NODE* curr;
    for (curr = Head; curr != Tail; curr = curr->next) {
        printf("%c", curr->data);
    }
}

int Delete_B_Node(NODE* cur) {
    NODE* del = cur->prev;

    del->next->prev = del->prev;
    del->prev->next = del->next;

    free(del);
}

int Insert_B_Node(Element data, NODE* cur) {
    NODE* new_node = _CreateNode(data);
    if (new_node == NULL)
        return -1;

    new_node->next = cur;
    new_node->prev = cur->prev;
    cur->prev = new_node;
    new_node->prev->next = new_node;

    return 0;
}



int main(void)
{

    NODE* Head = _CreateNode(' ');
    NODE* Tail = _CreateNode(' ');
    NODE* cur = Tail;
    Head->next = Tail;
    Tail->prev = Head;

    int N = 0;
    char tmp,x;
    char in_chars[100000] ;
    scanf("%s", in_chars);
    
    for (int i = 0; in_chars[i] != '\0'; ++i) {
        Append_Node(in_chars[i], cur);
    }

    //Head = Head->next;

    scanf("%d", &N);
    getchar();

    for (int i = 0; i < N; ++i) {
        scanf(" %c", &tmp);
        //getchar();
        //printf("%c", tmp);
        int cases = 0;
        if (tmp == 'L') {
            cases = L;
            getchar();
        }
        if (tmp == 'D') {
            cases = D;
            getchar();
        }
        if (tmp == 'B'){
            cases = B;
            getchar();
        }
        if (tmp == 'P')
            cases = P;

        switch (cases) {
        case L:
            if (cur->prev != Head)
                cur = cur->prev;
            continue;
        case D:
            if (cur != Tail)
                cur = cur->next;
            continue;
        case B:
            if (cur->prev != Head) {
                Delete_B_Node(cur);
            }
            continue;
        case P:
            scanf(" %c", &x);
            getchar();
            Insert_B_Node(x, cur);
            continue;
        default:
            printf("undefined cmd\n");
        }
    }

    print_Node(Head->next, Tail);
    
    return 0;
}
#endif