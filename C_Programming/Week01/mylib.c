#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include "mylib.h"

int menu_print()
{
	int num;
	printf("---------------\n");
	printf("MENU\n");
	printf("---------------\n");
	printf("1. read data\n");
	printf("2. print data\n");
	printf("3. find max data\n");
	printf("4. find min data\n");
	printf("5. sum data\n");
	printf("6. calculate average\n");
	printf("7. sort data\n");
	printf("0. exit\n");
	printf(" cmd >> ");
	scanf("%d", &num);
	return num;
}

int ary_control(int c, int* ary, int n) {
	int result = 0;
	switch (c) {
	case eMENU_SCAN:
		scanf_ary(ary, 5);
		break;
	case eMENU_PRINT:
		print_ary(ary, 5);
		break;
	case eMENU_MAX:
		result = findmax_ary(ary, 5);
		break;
	case eMENU_MIN:
		result = findmin_ary(ary, 5);
		break;
	case eMENU_SUM:
		result = sum_ary(ary, 5);
		break;
	case eMENU_AVG:
		result = avg_ary(ary, 5);
		break;
	case eMENU_SORT:
		sort_ary(ary, 5);
		break;
	default:
		printf("없는 번호\n");
	}
	if ((c >= eMENU_MAX) && (c <= eMENU_AVG))
		printf("%d\n", result);

	system("pause");
	system("cls");
}

int scanf_ary(int* pa, int n) {
	for (int i = 0; i < n; i++) {
		printf("input : ");
		scanf("%d", pa + i);
	}
	return n;
}
int print_ary(int* pa, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", *(pa + i));
	printf("\n");
	return n;
}
int findmax_ary(int* pa, int n) {
	int max = 0;
	for (int i = 0; i < n; i++)
		if (max < *(pa + i))
			max = *(pa + i);
	return max;
}
int findmin_ary(int* pa, int n) {
	int min = *pa;
	for (int i = 0; i < n; i++)
		if (min > *(pa + i))
			min = *(pa + i);
	return min;
}
int sum_ary(int* pa, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += *(pa + i);
	return sum;
}
int avg_ary(int* pa, int n) {    //평균 반올림해서 정수로 반환
	int sum = 0;
	double avg;
	for (int i = 0; i < n; i++)
		sum += *(pa + i);
	avg = (double)sum / n;
	;
	//if (avg - (int)avg >= 0.5)
		//avg += 0.5;

	return (int)(avg += 0.5);//right?
}
int sort_ary(int* pa, int n) {
	int tmp = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) { //같을 때 교환 필요 x
			if (*(pa + i) > *(pa + j)) {
				tmp = *(pa + i);
				*(pa + i) = *(pa + j);
				*(pa + j) = tmp;
			}
		}
	}
	return n;
}