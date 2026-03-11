#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

#if 0

typedef int (ppp)(int, int);


int sum(int a, int b)
{
	return a + b;
}

int main(void)
{
	int func = sum;
	printf("%d",((int (*) (int, int))func)(2, 3));


	//printf("%d", ((ppp)func)(2, 3));
	return 0;
}

#endif

#if 0

struct profile {
	int age;
	double height;
	char* name;
};

void init_struct(struct profile *pf) {

	pf->age = 21; // == (*pf).age == pf[0].age
	pf->height = 160;
	pf->name = "cho hyeon jun";
}
void print_struct(struct profile* pf) {

	printf("%d %.1f %s\n", pf->age, pf->height, pf->name);
}

int main(void)
{
	struct profile pf = {1, 2, "ch"};
	init_struct(&pf);
	print_struct(&pf);
	return 0;
}

#endif

#if 0

struct student {
	int age;
	int scores[3];
	char name[20];
};

void input_data(struct student* stu, int N) {
	for (int i = 0; i < N; i++) {
		(void)scanf("%d %d %d %d %s", &((stu + i)->age), (stu + i)->scores, 
			(stu + i)->scores+1, (stu + i)->scores+2, (stu + i)->name);
	}
}

void input_data2(struct student* stu, int N) {  //디스 어셈블리 결과 메모리 참조가 적어지므로 효율적
	struct student* temp;
	for (int i = 0; i < N; i++) {
		temp = stu + i;
		(void)scanf("%d %d %d %d %s", &(temp->age), temp->scores,
			temp->scores + 1, temp->scores + 2, temp->name);
	}
}
void input_data3(struct student* stu, int N) {  //디스 어셈블리 결과 메모리 참조가 적어지므로 효율적 + 가시성 좋음
	struct student* temp = stu;
	int* sc;
	for (int i = 0; i < N; i++, temp++) {
		sc = temp->scores;
		(void)scanf("%d %d %d %d %s", &(temp->age), sc,
			sc + 1, sc + 2, temp->name);
	}
}
void input_data_T(struct student* stu, int N) {
	struct student temp = { 0 };
	for (int i = 0; i < N; i++) {
		(void)scanf("%d %d %d %d %s", &(temp.age), temp.scores,
			temp.scores + 1, temp.scores + 2, temp.name);
		stu[i] = temp;
	}
}

void print_data(struct student* stu, int N) {
	for (int i = 0; i < N; i++) {
		//printf("%d ", (stu + i)->age);
		//printf("%s\n", (stu + i)->name);
		printf("%d %d %d %d %s\n", (stu + i)->age, (stu + i)->scores[0], 
			((stu + i)->scores)[1], (stu + i)->scores[2], (stu + i)->name);

	}
}

void print_data2(struct student* stu, int N) {
	struct student* tmp;
	int* sc;
	for (int i = 0; i < N; i++) {
		tmp = stu + i;
		sc = tmp->scores;
		printf("%d %d %d %d %s\n", tmp->age, sc[0],
			sc[1], sc[2], tmp->name);

	}
}

int main(void)
{
	struct student *stu = NULL;
	int N = 0;
	(void)freopen("stu.txt", "r", stdin);
	(void)scanf("%d", &N);
	stu = (struct student*)calloc(N, sizeof(struct student));
	input_data3(stu, N);
	print_data2(stu, N);
	return 0;
}

#endif

#if 0

struct IP_Header {
	uint16_t Version : 4;
	uint16_t IHL : 4;
	uint16_t Type_of_service : 8;
	uint16_t Total_Lenght;
	uint16_t Identification;
	uint16_t IP_Flags_x : 1;
	uint16_t IP_Flags_D : 1;
	uint16_t IP_Flags_M : 1;
	uint16_t Fragment_Offset : 13;
	uint8_t Time_to_Live ;
	uint8_t Protocol;
	uint16_t Header_Checksum;
	uint32_t Source_Address;
	uint32_t Destination_Address;
	uint32_t IP_Option;
};

int main(void)
{
	int a = 0x12345678;

	printf("%x\n", a);   //little endian check
	return 0;
}
#endif

#if 0
struct bit {
	unsigned a : 3;
	unsigned b : 3;
	unsigned c : 3;   //c   b   a
	unsigned d : 3;
}x;  //   1010 (1001)   01 001 010 (1000) >> 0100 1010 출력

int main(void)
{
	x.a = 2;
	x.b = 1;
	x.c = 3;
	x.d = 5;
	//printf("%x\n", x.a);
	printf("%x\n", *((unsigned char*) &x + 1)); //printf 로 입력 시 4byte 단위로 보내진다. char는 signed 로 인지하여 부호비트가 확장 in visual studio
	return 0;
}
#endif

#if 0

struct IP {
	unsigned char Flag_a : 1;
	unsigned char Flag_b : 1;
	unsigned char Flag_c : 1;
	unsigned char Flag_d : 1;
	unsigned char Flag_e : 1;
	unsigned char Flag_f : 1;
	unsigned char Flag_g : 1;
	unsigned char Flag_h : 1;
};

int main(void)
{
	struct IP A;  //{1,0,1,0,1,0,1,0} >> little endian을 따르기에 출력시 01010101 == 0x55 출력
	
	*(unsigned char*)&A = (unsigned char)0x55; //same result == 0b01010101

	/* unsigned char*P = (unsigned char)&A ; 이후 *P = 0x55 가능 */
	printf("%x\n", *((unsigned char*)&A));

	return 0;
}
#endif

#if 0

union student {

	int a;
	char b;
	short c;
};

int main(void)
{
	union student stu = { 0x12345678 };
	printf("%X %X %X %X", stu.a, *( & stu.b + 1),stu.b, stu.c);
	return 0;
}
#endif

#if 01
struct IP_Header {
	uint8_t Version : 3;
	uint8_t IHL : 5;
};
union Data {
	unsigned char ALL;
	struct IP_Header Part;
};

int main(void)
{
	union Data B;
	B.ALL = 0x55;
	printf("%x  ", 100);

	printf("%x %x %x\n", B.ALL, B.Part.Version, B.Part.IHL );   //little endian check
	return 0;
}
#endif