#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if 0

int main(void)
{
	const char* pc = "mango";
	pc = "banana";       // 다른 rodata 로 주소 변경
	//c[0] = 't';         // 변경 안됨 >> const 지정으로 오류 설정 가능
	scanf("%s", pc);     // rodata 영역에 입력 안됨
	return 0;
}

#endif


#if 0

int my_strlen(char* str) {

	char* s;
	if (str == 0)
		return 0;
	for (s = str; *s; s++);
	return s - str;
}

char* my_strcpy(char* to, const char* from) { //const 를 넣어주는 것이 코드 오류 감지에 용이
	char* save = to;
	for (; *to = *from; to++, from++)
		return save;
}

char* my_strcat(char* a, char* b) {
	char* save = a;
	for (; *a; a++);
	for (; *a = *b; b++, a++); // while(*a++ = *b++); 과 동일
	return save;
}

int my_strcmp(char* fir, char* sec) {
	while (*fir == *sec) {
		if (!*fir)
			return 0;
		sec++;
		fir++;
	}

	return *(unsigned char*)fir - *(unsigned char *)sec
}

int main(void)
{
	const char* pc = "mango";
	pc = "banana";       // 다른 rodata 로 주소 변경
	//c[0] = 't';         // 변경 안됨 >> const 지정으로 오류 설정 가능
	//scanf("%s", pc);     // rodata 영역에 입력 안됨

	char str[30] = { 0 };
	printf("%d\n", my_strcmp("applea", "apple"));
	return 0;
}

#endif

#if 0

int main(void)
{
	int a = 10, b = 5, c;
	c = a + b;
	printf("%d\n", c);
	return 0;
}

#endif

#if 0

extern void Increment();
extern int GetNum();

int main(void)
{
	printf("num : %d\n", GetNum());
	Increment();
	printf("num : %d\n", GetNum());
	Increment();
	printf("num : %d\n", GetNum());
	return 0;
}

#endif

#if 0

int main(void)
{
	int score[3][4] = { 0 };
	int* s = (int*)score[0];
	(void)freopen("score1.txt", "r", stdin);
	/*
	for (int i = 0; i < sizeof(score)/sizeof(int); i++) {
		(void)scanf("%d", s + i);   //((int*)score)+i 이 좀 더 효율적
		printf("%d\n", *(s + i));
	}
	*/
	for (int i = 0; i < 3; i++) {
		(void)scanf("%d %d %d %d", score[i], score[i]+1, score[i]+2, score[i]+3);   //((int*)score)+i 이 좀 더 효율적
	}

	for (int i = 0; i < sizeof(score) / sizeof(int); i++) {
		printf("%d\n", *(s + i));
	}

	return 0;
}

#endif