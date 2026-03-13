#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE(a) (sizeof(a)/ sizeof((a)[0]))

#if 0

int N = 100;

/*겹치는 부분 함수화 가능
반복문 조건 연산시 i-- 고려 >> 초기값 연산시에만 계산 됨*/

void test5(int L) {
	for (int i = 0; i < (N-L); i++)
		printf(" ");
	for (int i = 0; i < 2*L - 1; i++)
		printf("*");
	printf("\n");
	if (L >= N)
		return;
	test5(L + 1);
	for (int i = 0; i < (N - L); i ++)
		printf(" ");
	for (int i = 0; i < 2 * L - 1; i++)
		printf("*");
	printf("\n");
}

void test4(int L) {
	for (int i = 0; i < L;i++)
		printf("*");
	printf("\n");
	if (L >= N)
		return;
	test4(L + 1);
}

void test3(int L) {
	printf("%d ", L);
	if (L >= N)
		return;
	test3(L + 1);
	printf("%d ", L);
}

void test2(int L) {
	if (L > N)
		return;
	printf("%d ", L);
	test2(L + 1);
	printf("%d ", L);
}

void test1(int L) {
	if (L >= N)
		return;
	test1(L + 1);
	printf("%d ", L);
}

void test(int L) {
	printf("%d ",L);
	if (L >= N)
		return;
	test(L+1);
}


int main(void)
{
	test5(1);
	return 0;
}

#endif

#if 0

int N = 4;
int arr[10] = { 0 };
int data[10] = { 8,4,2,1 };
int Target = 5;

void test(void)
{
	int A[3] = { 4,2,1 };
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 2; ++k) {
				int tot = 0;
				if (i == 1) tot += A[0];
				if (j == 1) tot += A[1];
				if (k == 1) tot += A[2];
				if (tot == 5) printf("%d %d %d\n", i, j, k);
			}
		}
	}

}

void print_arr() {
	for (int i = 1; i <= N; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void test1(int L, int cnt)
{
	if (L > N) {
		printf("%d    ", cnt);
		print_arr();
		return;
	}
	arr[L] = 0;
	test1(L + 1, cnt);
	arr[L] = 1;
	test1(L + 1, cnt+1);
}
int T;
void test1_1(int L, int cnt) //cnt = 2 인 경우가 몇 개인지 출력
{
	if (L > N) {
		if (cnt == 2)
			printf("\n| T = %d |\n", ++T);
		printf("%d    ", cnt);
		print_arr();
		return;
	}
	arr[L] = 0;
	test1_1(L + 1, cnt);
	arr[L] = 1;
	test1_1(L + 1, cnt + 1);
}

void test1_2(int L, int cnt) //cnt = 2 인 경우가 몇 개인지 출력
{
	if (2 == cnt) { //나는 루프를 돌고 가지치기를 선택
		T++;	
		return;
	}
	if (L == N && cnt == 0) // 이후에 없을 경우 가지치기
		return;
	if (L > N) {
		return;
	}

	arr[L] = 0;
	test1_2(L + 1, cnt); 
	arr[L] = 1;
	// 다음 루프로 가기전에 2개 여부를 판별하는 방법이 존재
	test1_2(L + 1, cnt + 1);
}

void make_num(int L, int cnt) {
	const static int check_bit = 2;
	int check_bit_minus1 = check_bit - 1;

	if (L > N) {
		return;
	}

	if ((N - (L - cnt) + 1) == check_bit_minus1) {
		return;
	}
	arr[L] = 0;
	make_num(L + 1, cnt);

	if (cnt == 1) {
		++T;
		return;
	}
	arr[L] = 1;
	make_num(L + 1, cnt + 1);
}

void test2(int L)
{
	if (L > N) {
		int cnt = 0;
		for (int i = 0; i < L; i++) cnt += arr[i];
		printf("%d     ", cnt);
		print_arr();
		return; }
	for (int i = 0; i < 2; i++) {
		arr[L] = i;
		test2(L + 1);
	}
}

int main(void)
{
	T = 0;
	//test();
	//test1_2(1, 0);
	//test2(1);
	make_num(1, 0);
	printf("%d", T);
	return 0;
}

#endif


#if 0

int N = 5;
int k = 2;
int arr[10] = { 0 };
int data[10] = { 8, 4, 2, 1 };
int T = 0;
int loop = 0;

void print_arr2(int n) { //디버깅용 함수
	printf("%2d: ", loop);
	for (int i = 1; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}


void make_num3(int L, int cnt) {
	++loop;
	if (L > N) {
		return;
	}
	arr[L] = 0;
	make_num3(L + 1, cnt);
	if (cnt == 1) {
		++T;
		return;
	}
	arr[L] = 1;
	make_num3(L + 1, cnt + 1);
}

void make_num4(int L, int cnt) {
	++loop;
	// 필요한 1의 개수 < 남은 비트 개수
	if ((2 - cnt) < N - (L - 1)) {
		arr[L] = 0;
		make_num4(L + 1, cnt);
	}
	if (cnt == 1) {
		++T;
		return;
	}
	arr[L] = 1;
	make_num4(L + 1, cnt + 1);
}

int main(void) {
	for (N = 4; N < 10; N++) {
		printf("N = %d   \n", N);
		T = loop = 0;
		make_num3(1, 0);
		printf("A : T = %d, loop = %d\n", T, loop);

		T = loop = 0;
		make_num4(1, 0);
		printf("B : T = %d, loop = %d\n", T, loop);
	}
}
#endif




#if 0

int main(void) {
	int sushi[33000] = { 0 };
	int count[3001] = { 0 };
	int res = 0;

	int N, d, k, c;
	scanf("%d %d %d %d", &N, &d, &k, &c);

	int type_cnt = 0;   // 현재 상황에서 초밥의 종류

	// 초밥번호 입력
	for (int i = 0; i < N; i++) {
		scanf("%d", &sushi[i]);
	}

	// 회전 구현 위해 앞의 k개 더 입력
	for (int i = 0; i < k; i++) {
		sushi[N + i] = sushi[i];
	}

	// 맨 처음 k개 조합
	for (int i = 0; i < k; i++) {
		if (count[sushi[i]] == 0) {
			type_cnt++;
		}
		count[sushi[i]]++;
	}

	// 그 이후는 맨 앞 빼고, 맨 뒤 끼우며 체크
	for (int i = 0; i < N; i++) {
		int tmp = type_cnt;
		if (count[c] == 0) {
			tmp++;
		}
		if (tmp > res) {
			res = tmp;
		}

		count[sushi[i]]--;
		if (count[sushi[i]] == 0) {
			type_cnt--;
		}

		if (count[sushi[i + k]] == 0) {
			type_cnt++;
		}
		count[sushi[i + k]]++;
	}

	printf("%d\n", res);

	return 0;
}

#endif

#if 0
int main(void)
{
	char* fruit[] = { "orange", "apple", "mango", "cherry"};
	char** aptr[] = { fruit + 3, fruit + 2, fruit + 1, fruit };
	char*** bptr = aptr;

	printf("%s\n", * -- * ++bptr + 3);
	printf("%s\n", *(*(bptr-1)-1)); //앞뒤의 영향을 고려해야지...
}

#endif




#if 0

int cnt = 0;
int dans = 0;

void __find(int i, int j, bool*pan,int N ) {
	pan[i * N + j] = 0;
	cnt++;
	if ((i != 0) && pan[(i - 1) * N + j]) //up check
		__find(i - 1, j, pan, N);

	if ((i != N - 1) && pan[(i + 1) * N + j]) //down check
		__find(i + 1, j, pan, N);

	if ((j != 0) && pan[i * N + (j - 1)]) //left check
		__find(i, j - 1, pan, N);

	if ((j != N - 1) && pan[i * N + (j + 1)]) //right check
		__find(i, j + 1, pan, N);
}


int main(void) {
	int N;

	(void)scanf("%d", &N);
	
	int max_dan = N * N;

	bool* pan = (bool*)calloc(N * N, sizeof(bool));
	int* dan = (int*)calloc(N * N, sizeof(int));
	for (int i = 0; i < N*N; ++i)
		scanf("%1d", (pan + i)); //오!

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (pan[i*N + j]) {
				__find(i, j, pan, N);
				dan[dans + 1] = cnt;
				cnt = 0;
				dans++;
				dan[0]++;
			}
	for (int i = 0; i < max_dan; i++)
		printf("%d", dan[i]);
	free(pan);
	free(dan);
	return 0;
}

#endif //단지번호 문제 고치는 중  (배열로 저장 후 정렬 하기 qsort)


#if 0
int cnt = 0;

void __find(int i, int j, bool* pan, int N) {
	pan[i * N + j] = 0;
	cnt++;
	if ((i != 0) && pan[(i - 1) * N + j]) //up check
		__find(i - 1, j, pan, N);
	if ((i != N - 1) && pan[(i + 1) * N + j]) //down check
		__find(i + 1, j, pan, N);
	if ((j != 0) && pan[i * N + (j - 1)]) //left check
		__find(i, j - 1, pan, N);
	if ((j != N - 1) && pan[i * N + (j + 1)]) //right check
		__find(i, j + 1, pan, N);
}


int main(void) {
	int N = 7;

	scanf("%d", &N);

	bool* pan = (bool*)calloc(N * N, sizeof(bool));

	for (int i = 0; i < N * N; ++i)
		scanf("%1d", (pan + i)); //오!
	/*
bool pan[] = {0,1,1,0,1,0,0,
				0,1,1,0,1,0,1,
				1,1,1,0,1,0,1,
				0,0,0,0,1,1,1,
				0,1,0,0,0,0,0,
				0,1,1,1,1,1,0,
				0,1,1,1,0,0,0};
*/

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (pan[i * N + j]) {
				__find(i, j, pan, N);
				printf("%d\n", cnt);
				cnt = 0;
			}
	return 0;
}
#endif // 단지문제 >> 바뀌지 않는 pan, N의 경우 const or 전역으로 돌려 쓰는 방법 고려

#if 0

#define MAX_N (25 + 2)
int map1[MAX_N][MAX_N];
char map2[MAX_N][MAX_N];
int N;

void inputData(void) {
	char temp[MAX_N];
	(void)scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			(void)scanf("%1d", &map1[i][j]);
		}
	}
	for (int i = 0; i < N; ++i) {
		(void)scanf("%s", temp);
		for (int j = 0; j < N; ++j) {
			map1[i][j] = temp[j] - '0';        //scanf 횟수 적기에 권장
		}
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			(void)scanf("%1d", &map1[i][j]);
		}
	}
	for (int i = 1; i <= N; ++i) {
		(void)scanf("%s", temp + 1);
		for (int j = 1; j <= N; ++j) {
			map1[i][j] = temp[j] - '0';
		}
	}

	for (int i = 1; i <= N; ++i) {
		(void)scanf("%s", map2[i] + 1);
	}
}

// R,C의 상,하,좌,우 좌표 출력해보기
int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };
void print_RC(int R, int C) {
	for (int i = 0; i < 4; ++i) {
		printf("%d %d\n", R + dR[i], C + dC[i]);
	}
}

#endif //강사님의 참고 코드

#if 0
//리턴 사용시 어디서 리턴을 받을 수 있을 지 미리 체크해두고 작성하는것이 이로움
int search(int r, int c) {
	int result = 0;
	if (r < 0 || N <= r || c < 0 || N <= c) return 0;
	if (arr[r][c] == 1) {
		arr[r][c] = 0;
		++result;
		return result + search(r - 1, c) + search(r + 1, c) + search(r, c - 1) + search(r, c + 1);
	}
	return 0;
}

#endif //타인이 작성한 코드
