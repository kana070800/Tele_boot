


#if 0
#include <stdio.h>
int main(void)
{
	int a = 'A';
	int b, c;
	b = a + 32;
	c = a + ('a' - 'A');
	printf("%c %c\n", b, c);
	return 0;
}
#endif //ascii code

#if 0
#include <stdio.h>
typedef int INTARR5[5]; //int 배열 == INTARR5
typedef int (*PP)[5];    //int 배열포인터 == PP
typedef int *IP
int main(void)
{
	INTARR5 A;
	int a[5] = { 1 }, b[5] = {2}, c[5] = { 3 };
	INTARR5 x, y, z;
	IP x1, y1, z1;
	printf("%d, %d, %d", a[0], b[0], c[0]);
	return 0;
}
#endif // typedef ex

#if 0
#include <stdio.h>
int main(void)
{
	int a = 0x12345678;
	char n = 0x12345678;
	printf("a = %x, n = %x\n", a, n);
	return 0;
}
#endif // little endian

#if 0
#include <stdio.h>
int main(void)
{
	char ch1 = 'A';
	char ch2 = 65;
	printf("char %c, ASCII : %d\n", ch1, ch1);
	printf("ASCII : %d, char : %c\n", ch2, ch2);

	unsigned char uch1 = -1; //ff
	unsigned char uch2 = 128; //80
	signed char ch11 = -1; //ff
	signed char ch22 = 128; //80
	//메모리 저장방식은 동일, but 변수 해석 방식이 다르기 때문에 다르게 출력된다
	printf("unsigned char(%%u) : %u %u\n", uch1, uch2);
	printf("signed char(%%u)   : %d %d\n", ch11, ch22);
	return 0;
}
#endif // stored value of memory


//------------------------------------ x86의 경우 32 bit, x64의 경우 64 bit

#if 0
#include <stdio.h>
int main(void)
{
	int income = 0;
	double tax;
	const double tax_rate = 0.12;
	double* dp = &tax_rate;

	income = 456;

	//tax_rate = 0.15; //불가
	*dp = 0.15; //가능

	tax = income * tax_rate;
	printf("tax = %.1lf\n", tax);

	printf("%d",strlen("apple"));
	return 0;
}
#endif // const value change

#if 0
#include <stdio.h>
int main(void)
{	
	int a;
	scanf("%d", &a);
	printf("input : %d\n", a); //안전하지 않은 함수, scanf_s 권장
	return 0;
}
#endif // scanf

#if 0

#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 보안 경고를 무시하고 컴파일을 진행할 때 사용하는 매크로
#include <stdio.h>
int a = 10;
int b = a + 20;
int main(void)
{
	char str[5];
	printf("input : ");
	// scanf("%s", &str);  //길이 제한 없음(크기 초과시 runtime error 발생)
	scanf_s("%s", &str, 5); //초과시 출력이 안됨(정상적 종료), 공백 인식 x
	printf("input : %s\n", str); 
	return 0;
}
#endif // scanf_s

#if 0
#include <stdio.h>
/*
unsigned int setBit(unsigned int num, int bitposition)
{
	return num | (0x1 << bitposition);
}

unsigned int clearBit(unsigned int num, int bitposition)
{
	return num & ~(0x1 << bitposition);
}

unsigned int toggleBit(unsigned int num, int bitposition)
{
	return num ^ (0x1 << bitposition) ;
}
*/
unsigned int setBit(unsigned int num, int start, int count)
{
	return num | (((1 << count) - 1) << start); // or (2^n - 1 shift)
}

unsigned int clearBit(unsigned int num, int start, int count)
{
	return num & ~(((1 << count) - 1) << start); // and (2^n - 1 shift)
}

unsigned int toggleBit(unsigned int num, int start, int count)
{
	return num ^ (((1 << count) - 1) << start); // xor (2^n - 1 shift)
}

#define isBitSet(num, bitposition) (num >> bitposition) & 0x1
/*
static unsigned int isBitSet(unsigned int num, int bitposition)
{
	return (num >> bitposition) & 0x1;
}
*/
int main(void)
{
	int num = 0xf0;
	printf("%X\n", setBit(num,2,2));
	printf("%X\n", clearBit(num, 6, 2));
	printf("%X\n", toggleBit(num, 2, 4)); 
	printf("%d\n", isBitSet(num, 3));
	return 0;
}
#endif // bit set, clear, toggle functions

#if 0
#include <stdio.h>
int main(void)
{
	char x = -128;
	char y = x - 1;
	printf("%d, %d, %d\n", x - 1,(char)(x - 1), y);
}
#endif // char calculation

#if 0
#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 보안 경고를 무시하고 컴파일을 진행할 때 사용하는 매크로
#include <stdio.h>
#include <string.h>

int Check_Z(int left, int right, char* buffer, int * count)
{
	if (buffer[left] == ' ')
		left++;
	if ('0' == buffer[left])
		return 0;

	
	int i = (int)(buffer[right - 1] - '0');
	count[i]++;
	
	return 1;

}

int Set_right(int left, char* buffer)
{
	left++;
	while ((buffer[left]) && (buffer[left] != ' ')) //null 이나 ' ' 이면 루프 종료
		left++;
	return left;
}

int main(void)
{
	int right = 0, left = 0, flag = 1;
	char buffer[200];
	int count[10] = { 0 };

	printf("input nums : ");
	fgets(buffer, sizeof(buffer), stdin);
	
	while (flag) {
		left = right;
		right = Set_right(left, buffer);
		flag = Check_Z(left, right, buffer, count);
	}
	
	for (int i = 0; i < 10; i++)
		printf("%d\n", count[i]);
		
	printf("%s", buffer);

	/*
	for (int i = 1; i < a; i = i * 10)
	{
		temp *= 10;
		temp += a / i % 10;
	}
	
	printf("output num : %d\n", temp);*/
	return 0;
}
#endif // fitst number count

#if 01
#include <stdbool.h>

int if_Find_solution(int * index)
{
	int count = 0;
	while (*index++)
		printf("%d", *index);
	return count;
}

int main(void)
{
	int N, tmp=0,value=0;
	int index[100] = { 0 };
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &tmp);
		getchar();
		index[tmp] = 1;
	}
	
	printf("%d", if_Find_solution(index));
	return 0;
}
#endif
