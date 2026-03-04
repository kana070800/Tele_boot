#ifndef __MYLIB_H__
#define __MYLIB_H__

enum {
	eMENU_EXIT = 0,
	eMENU_SCAN,
	eMENU_PRINT,
	eMENU_MAX,
	eMENU_MIN,
	eMENU_SUM,
	eMENU_AVG,
	eMENU_SORT,
	eMENU_MAX_VAL
};
int menu_print(void);
int ary_control(int, int*, int);
int scanf_ary(int* pa, int n);
int print_ary(int* pa, int n);
int findmax_ary(int* pa, int n);
int findmin_ary(int* pa, int n);
int sum_ary(int* pa, int n);
int avg_ary(int* pa, int n); //평균 반올림해서 정수로 반환
//void var_ary(int* pa, int n);
int sort_ary(int* pa, int n);

#endif
