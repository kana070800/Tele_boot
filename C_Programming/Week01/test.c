#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

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
		
	//printf("%s", buffer);

	return 0;
}
#endif // fitst number count

#if 01
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

int _first(int a, bool *index) 
{
	while (!*(index + a))
		a++;  // 0 0 1 0 1 1 1 0 0      5 24567     0 0 > 1에서 멈춤 2리턴 0 > 2 2 > 3에서 멈춤 4리턴 2 > 4 4 > 5
	return a+1;
}



int _cal(int first, int second, bool *index)
{
	int count = 0;
	int d = second + (second - first); // 1 3 4 7 10 >> 6 ~ 8 >> 8 ~ 11
	int max = second + 2*(second - first); // 01011001001
	for (int i = d - 1; i < max; i++)
		if (index[i])
			count++;

	return count;
}


int main(void)
{
	int N, tmp = 0, init = 0,init1=0, first = 0, second = 0;
	bool index[1000] = { 0 };
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &tmp);
		getchar();
		index[tmp] = 1;
	}
	tmp = 0;

	for (int i = 0; i < N-2; i++)
	{
		init = first;
		first = _first(init, index); //init에서 first 선정
		//printf("%d\n", first);
		
		second = first;
		
		for (int j = 0; j < N - 2 - i; j++) {
			init1 = second;
			
			second = _first(init1, index); //first에서 second 선정 >> 내부에서 _first를 N - 1 - i 번 수행
			//printf("%d %d\n", first, second);
			//printf("%d\n", _cal(first, second, index));
			tmp += _cal(first, second, index);
		}
	}
	printf("%d\n", tmp);
	return 0;
}
#endif //확장이 , 예외처리 추가
/*

예외처리는 나중에 추가 (N 범위)

1. 크기가 정해진 배열에 입력된 인덱스 요소에 표시

2. 인덱스 간 관계를 통해 경우의 수를 연산 >  _first 를 N-2번 반복
		1) find next int value 1 >> _first (index[0]에서 부터 for 돌면서 1 찾기, 찾으면 정지, 인덱스 반환)
		2) choose next 1 index >> _second (받은 인덱스에서 부터 for 돌면서 1 찾기, 찾으면 정지, 인덱스 반환)
		3) is there any 1 in 범위 >> 범위를 연산하고 연산된 범위 사이에 1 이 있는지 탐색
	

1. 입력 수 만큼 연꽃 구조체(위치 포함) 생성
2. 구조체에 저장된 위치를 통해 경우의 수를 연산
	위치값들 정렬 필요
	연산 자체는 용이
	*/


#if 0


int main(void)
{
	int N, d, k, c, value = 0, tmp, flag_x, flag_c;
	scanf("%d %d %d %d", &N, &d, &k, &c);


	int* arr = (int*)malloc(sizeof(int) * (N+k-1)); // 접시수 만큼 배열생성
	//int* cham = (int*)malloc(sizeof(int) * (k));    // 참조값들 저장 배열
	//d = 초밥 가지수 >> 입력 시 범위를 지정한다
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
		getchar();
	}
	for (int i = 0; i < (k - 1); i++) //연속참조 횟수-1만큼 배열 추가
		arr[N + i] = arr[i];
	//k = 연속 섭취수 >> 참조횟수
	//c = 쿠폰 번호 >> 참조중 발견시 k+1 반환
	//1. 순차적으로 연산하여 발견하면 k+1, or k 반환
	//2. 판별만 하면 되잖아 >> 문제 발생 (가짓수가 적을때 판별 곤란)

	//배열을 N번 순차적으로 k번 참조
	//참조 중 각기 다른 것을 먹는 횟수를 반환
	//		1) c를 포함시
	//			1) k 보다 작다
	//			2) k 만큼 
	//				>> 다른 것을 먹는 횟수를 반환
	//		2) c를 포함 안할 시
	//			1) k 보다 작다
	//			2) k 만큼
	//				>> 다른 것을 먹는 횟수를 반환 + 1
	// 반복된 반환값 중 최댓값이 결론

	/*
	printf("%d %d %d %d\n", N, d, k, c);
	for (int i = 0; i < N - 1 + k; i++)
		printf("%d ", arr[i]);
		*/
	
	for (int i = 0; i < N; i++)
	{
		tmp = 0;
		flag_c = 1; //c 발견시 0
		for (int j = 0; j < k; j++) //잘라진 N+k-1배열에서 일일이 참조하고 
		{//1 2 3 3 4  일때 4 반환, c 인지 판별 
			flag_x = 1; // 중복 발견시 0
			for (int x = 0; x < k - j; x++) {
				if (arr[i + j + x + 1] == arr[i + j]) //배열 [i] ~ [i+k-1] 까지 발견 안되면 +1
					flag_x = 0;
				if (arr[i + j + x + 1] == c)
					flag_c = 0;
			}
			tmp += flag_x;
		}
		tmp += flag_c;
		value = (value > tmp) ? value : tmp;

		if (value == (k + 1))
			break;
	}
	
	printf("%d", value);

/*
8 30 4 30
7
9
7
30
2
7
9
25
*/

	free(arr);

	return 0;
}

#endif

#if 0
int main(void)
{
	int N, d, k, c, value = 0, tmp, flag_x, flag_c;
	scanf("%d %d %d %d", &N, &d, &k, &c);

	int* arr = (int*)malloc(sizeof(int) * (N + k - 1)); // 접시수 만큼 배열생성
	//int* cham = (int*)malloc(sizeof(int) * (k));    // 참조값들 저장 배열
	//d = 초밥 가지수 >> 입력 시 범위를 지정한다
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
		getchar();
	}
	for (int i = 0; i < (k - 1); i++) //연속참조 횟수-1만큼 배열 추가
		arr[N + i] = arr[i];
	//k = 연속 섭취수 >> 참조횟수
	//c = 쿠폰 번호 >> 참조중 발견시 k+1 반환
	//1. 순차적으로 연산하여 발견하면 k+1, or k 반환
	//2. 판별만 하면 되잖아 >> 문제 발생 (가짓수가 적을때 판별 곤란)

	//배열을 N번 순차적으로 k번 참조
	//참조 중 각기 다른 것을 먹는 횟수를 반환
	//		1) c를 포함시
	//			1) k 보다 작다
	//			2) k 만큼 
	//				>> 다른 것을 먹는 횟수를 반환
	//		2) c를 포함 안할 시
	//			1) k 보다 작다
	//			2) k 만큼
	//				>> 다른 것을 먹는 횟수를 반환 + 1
	// 반복된 반환값 중 최댓값이 결론


	printf("%d", value);


	free(arr);

	return 0;
}

#endif


//5, 10, 11, 10, 11, 11, 22, 11, 12, 12, 22, 22, 22, 23





#if 0

#include <stdbool.h>
#include <stdint.h>

typedef struct A {
	double trace_7_now;  //7일 trace
	double trace_7_B;    //7일전
	double day_now;   //당일 종가 for 특수 case2
	double day_B;     //전일 종가
	double aver_120;

	int can_use;  //가용 
	int in_zoo ;   //주식
	int in_bank;  //저축

	int scase_2_cnt;  //특수 case 2 횟수, 2번 이상 시 중단
	char flag_case_2 ;
	char flag_case_2 ;
	bool month_change;
	int day;
}Status;


void value_load(Status* my);
void value_update(Status* my);
void day_update(Status* my);
void check_scase_2(Status* my);
void check_scase_1(Status* my);
void check_gcase(Status* my);
void account_adjust(Status* my);
void perform(Status* my);

//중간 매개로 파일에 저장해 둔 값을 불러오기
//단순 입력이 아닌 끌어오는 방법 고민
int main(void)
{
	
	/*
	매일 장 마감 직전 변수 갱신, 불러오기
	if)이번 주 특수 case2가 2번 발생했었는지 점검
	특수 case2 인지 확인

	한주 기준날 확인
		특수 case1 인지 확인
		일반 case에서 어떤 상황인지 확인

	매달 기준날인지 확인 후 조정
	변수 저장
	*/

	Status my_info = { 0 };

	value_load(&my_info);

	day_update(&my_info);

	if (2 > my_info.flag_case_2) {
		check_scase_2(&my_info);

		if (1 == my_info.day) {
			check_scase_1(&my_info);
			check_gcase(&my_info);
		}

	}

	if (my_info.month_change) {
		account_adjust(&my_info);
	}

	perform(&my_info);
	value_update(&my_info);
	printf("%d", 1);
	return 0;
}
void value_load(Status* my) { //파일 불러오기, 웹 사이트에서 불러오기*******how?

}
void day_update(Status* my){ //현재 날짜를 통해 날짜 정보, flag update
	
}
void check_scase_2(Status*my){ //특수 case2 확인
	if (my->day_now > (my->day_B) * 1.05) {
		my->scase_2_cnt++;
		my->flag_2_up = 1;
	}
	if (my->day_now < (my->day_B) * 0.95) {
		my->scase_2_cnt++;
		my->flag_2_dn = 1;
	}
}
void check_scase_1(SStatus* my){ //특수 case1 확인

}
void check_gcase(Status* my){ //일반 case 확인  >>  수수료 고려 필요, 너무 작은 변동일 경우 거래 x

}
void account_adjust(Status* my){ // 매달 계좌 조정 확인

}
void perform(Status* my) { // 거래 진행 및 반영

}
void value_update(Status* my) { //정보 update 및 파일에 저장
	if ((my->day % 7) == 0)
		my->scase_2_cnt = 0;
	my->flag_2_dn = 0;
	my->flag_2_up = 0;
}


#endif