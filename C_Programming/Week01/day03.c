#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#if 0
int main(void)
{
	if () {
		printf("True\n");
	}
	else {
		printf("False\n"); //false >> 0, 0.0, NULL, '\0'
	}
	return 0;
}
#endif //false

#if 0
int main(void)
{
	int a = 100;
	if (a > 0) {
		printf("True\n");
//#include <stdbool.h>
		//int sum(int a, int b) { return a + b; } //함수 선언은 가능, 정의는 불가능
	}
	else {
		printf("False\n");
	}
	return 0;
}
#endif //wrong condition

#if 0
int main(void)
{
	int num = 100;
	char* msg = NULL;

	// msg = (num % 2) ? "홀" : "짝";

	//[num % 2 == 1] or [num % 2 != 0] >> 비용차이 존재하는가(디스어셈블리 결과 거의 차이가 없다)
	if (num % 2)
	{
		msg = "홀수";
	}
	else
	{
		msg = "짝수";
	}

	printf("%s\n", msg);

	return 0;
}
#endif //if else, odd even

#if 0
int main(void)
{
	int score = 100;
	char* msg = NULL;

	if (score >= 70) {
		msg = "합격";
	}
	else if(score > 59) {
		msg = "재시험";
	}
	else {
		msg = "불합격";
	}
	/*
	if (score >= 70) {
		msg = "합격";
	}
	else {
		if (score > 59) {
			msg = "재시험";
		}
		else { msg = "불합격"; }
	}
	*/ // 어셈블리로 보면 차이 없음, but 가독성 떨어짐

	printf("%s\n", msg);

	return 0;
}
#endif //if else, score grade

#if 0
int main(void)
{
	int a = 10;
	char* msg = NULL;

	// 조건을 정수로 표현해야한다
	switch (a) {
	default:  //대부분의 경우 default 인 경우 앞이 좋다
		msg = 'F';
		break;
	case 1:
		msg = 'A';
		break;
	case 2:
		msg = 'B';
		break;
	}

	printf("%c\n", msg);

	return 0;
}
#endif //switch case > 배열로 대체 가능성 모색, break 줄여서 흐름 조정을 제외하고는 강점 x

//****************************************************** different method of score
#if 0
int main(void)
{
	int score = 0;
	char* msg = NULL;
	printf("input score : ");
	scanf_s("%d", &score, 4);
	switch (score / 10) {
	default:
		msg = "F";
		break;
	case 6:
		msg = "D";
		break;
	case 7:
		msg = "C";
		break;
	case 8:
		msg = "B";
		break;
	case 9:
	case 10:
		msg = "A";
		break;
	}
	printf("grade : %s\n", msg);
	return 0;
}

#endif

#if 0
int main(void)
{
	int score = 0;
	char* msg = NULL;
	printf("input score : ");
	scanf_s("%d", &score, 4);
	
	score /= 10;

	if (score < 6){
		msg = "F";
	}
	else if (6 == score) {
		msg = "D";
	}
	else if (7 == score) {
		msg = "C";
	}
	else if (8 == score) {
		msg = "B";
	}
	else {
		msg = "A";
	}
	


	printf("grade : %s\n", msg);
	return 0;
}

#endif

#if 0
int main(void)
{
	int score = 0;
	char* msg = NULL;
	printf("input score : ");
	scanf_s("%d", &score, 4);

	score /= 10;
	
	msg = (score < 6) ? "F" : (6 == score) ? "D" : (7 == score) ? "C" :	(8 == score) ? "B" : "A";

	printf("grade : %s\n", msg);
	return 0;
}
#endif

#if 0
int main(void)
{
	int score = 0;
	char* msg = NULL;
	printf("input score : ");
	scanf_s("%d", &score, 4);

	score /= 10;
	char grade[11] = {'F','F','F','F','F','F', 'D', 'C', 'B', 'A','A'};

	msg = grade[score];

	printf("grade : %c\n", msg);
	return 0;
}
#endif
//******************************************************
#if 0
int main(void)
{
	int score = 0;
	int pass = 1234;
	char* msg = NULL;

	
	
	printf("input num : ");
	scanf("%d", &score);

	while (scanf("%d", &score)) {
		printf("input num : ");
		scanf("%d", &score);
	}
	
	/*	
	do {
		printf("input num : ");
		scanf_s("%d", &score);
	} while (score != pass);
	*/

	printf("ok!\n");
	return 0;
}
#endif //while vs do while 

#if 0
int main(void)
{
	int score = 0;
	int input = 0;
	printf("input : ");
	if (score = scanf("%d", &input)) {
		printf("scanf return value : %d\n", score);

		(input % 2) ? printf("홀\n") : printf("짝\n");  //함수호출은 식
	}
	return 0;
}
#endif //function

#if 0
int main(void)
{
	int score = 0;
	int pass = 1234;
	
	int flag = 0;
	
	//flag = scanf("%d", &score);  //%d 옵션일 때 a는 문자 입력 시 0 반환, 그런데! 숫자에 이어서 문자를 입력하면 1이 반환되어 문제 발생
	
	while ( printf("input num : ") && (scanf("%d", &score) != 1) || (score != pass)) {
		printf("응 아니야 다시해~\n");
		while (getchar() != '\n') {}
	}
	//버퍼 비우기, scanf가 실패하면 버퍼에 남아있는 입력값이 계속해서 scanf의 입력으로 들어가기 때문에 버퍼를 비워주는 과정이 필요하다
	
	printf("%d", flag);

	return 0;
}
#endif

#if 0
int main(void)
{
	char *input = (char*) malloc(10*sizeof(char));
	char *pass = "1234";

	int flag,i = 0;

	printf("input num : ");

	while(1) {
		scanf("%s", input);
		i++;
		if (*(pass + i) != *(input + i))
		{
			printf("wrong");
			continue;
		}
	}
	
	free(input);
	return 0;
}
#endif

#if 0
int main(void)
{
	int total = 0;
	for (int i = 1; i < 101; i+=2)
	{
		total += i;
	}
	printf("total = %d", total);
}
#endif

#if 0

void func(int a, int b) {
	return; //가능
}
int main(void) {
	func(1, 2);
	return 0;
}

#endif


#if 0
int main(void)
{
	int arr[5] = { 1,2,3,4,5 };
	printf("%p %p %p\n", arr, arr + 1, arr - 1);

	printf("%p %d\n", &arr + 1, sizeof(arr)); //&arr은 배열 포인터 >> 배열 전체를 가리키는 포인터 >> 20 바이트 이동
	printf("%d %d\n", *arr, *(arr + 3)); //요소 참조

	for (int i = 0; i < 5; i++)
	{
		scanf("%d", (arr + i)); // scanf("%d", &arr[i]); 동일한 결과, 어셈블리코드
		//while (getchar() != '\n') {}
	}
	for (int i = 0; i < 5; i++)
	{
		printf("%d", *(arr + i)); // printf("%d", arr[i]); 동일한 결과, 어셈블리코드
	}
	printf("\n");
	return 0;
}
#endif

#if 0
#define SIZE(a) (sizeof(a)/sizeof(a[0]))

int main(void) {

	int score[5];
	int total = 0;

	freopen("score1.txt", "r", stdin);
	for (int i = 0; i < SIZE(score); i++)
	{
		scanf("%d", &score[i]); // scanf("%d", score + i); 동일한 결과, 어셈블리코드
		total += score[i];
	}
	printf("total = %d\n", total);
	return 0;
}
#endif






#if 0
int main(void)
{
	int a;
	int temp = 0;
	printf("input num : ");
	scanf("%d", &a);
	for (int i = 1; i < a; i = i * 10)
	{
		temp++;
	}
	printf("output num : %d\n", temp);
	return 0;
}
#endif