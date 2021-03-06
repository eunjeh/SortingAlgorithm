// sorting_project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	NUMOFNUMBERS	50000	// 5만개, 7.5만개, 10만개, 12.5만개, ..., 50만개까지 증가시키며 시간 측정할 것

long randNumbers[NUMOFNUMBERS]; 
long sorted[NUMOFNUMBERS]; 

//함수선언
void selectionSort(long A[], long n);
long theLargest(long A[], long last);
void merge(long *data, long start, long mid, long end);
void merge_sort(long *data, long start, long end);
int*countingSort(long A[], int n, int k);


int main(int argc, char* argv[])
{
	register long n, i; //register에서 동작할 수 있도록 변수 생성
	clock_t before;
	double elapsed_time;
	int*output; //counting sort의 리턴배열이 될 것임.
	output = (int*)malloc(sizeof(int)*NUMOFNUMBERS); //동적할당

	printf("알고리즘입문 2019년 1학기 소팅 프로젝트 시작합니다.\n\n");

	srand((unsigned)time(NULL)); //난수표로 난수를 생성한다. rand함수 전에 실행

	before = clock(); //시간 측정 시작
	for (i = NUMOFNUMBERS - 1; i >= 0; i--) { //난수 생성
		n = rand();
		n += ((i + 1) / RAND_MAX) * RAND_MAX;
		randNumbers[NUMOFNUMBERS - 1 - i] = n;
	}
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	printf("%d 개의 랜덤 넘버 생성에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	/*std::cout << "정렬전 숫자 입력 값들 출력:\n\n";
	for (i = 0; i < NUMOFNUMBERS; i++)
	printf("%ld ", randNumbers[i]);
	printf("\n\n");*/

	// 여기에 각종 정렬 알고리즘을 구현해서 실행시키고 그 실행 시간을 출력합니다.
	// 예: Selection Sort는 다음과 같습니다.
	before = clock();

	/* 주석을 풀어서 원하는 sorting을 사용해야합니다. 함수를 호출하는 부분입니다.*/
	//selectionSort(randNumbers, NUMOFNUMBERS);
	//merge_sort(randNumbers, 0, NUMOFNUMBERS);
	int max = 0;
	for (int j = 0; j < NUMOFNUMBERS; j++) {
		if (randNumbers[j] > max) {
			max = randNumbers[j];
		}
	} //생성된 난수들의 배열에서 가장 큰 값 찾기
	output = countingSort(randNumbers, NUMOFNUMBERS, max);

	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.

	/* 주석을 풀어서 어떤 sorting방식의 결과인지를 print합니다.*/
	//fprintf(stdout, "%d 개의 랜덤 넘버를 selection sort 하는 데에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);
	//fprintf(stdout, "%d 개의 랜덤 넘버를 merge sort 하는 데에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);
	fprintf(stdout, "%d 개의 랜덤 넘버를 counting sort 하는 데에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	/*printf("정렬 결과 출력:\n\n");
	for (i = 0; i < NUMOFNUMBERS; i++)
		printf("%ld ", output[i]);
	printf("\n\n");*/ //출력할 배열은 주석을 풀고 selection와 merge는 randNumbers, counting은 output이라고 입력해야합니다.

	return 0;
}

void selectionSort(long A[], long n)
{
	int last, k, tmp;

	for (last = n - 1; last >= 1; last--) {
		k = theLargest(A, last);	// A[0...last] 중 가장 큰 수 A[k] 찾기
		tmp = A[last];
		A[last] = A[k];
		A[k] = tmp;
	}
}

long theLargest(long A[], long last)
{
	long largest, i;

	largest = 0;
	for (i = 1; i <= last; i++)
		if (A[i] > A[largest])
			largest = i;
	return largest;
}

void merge(long *data, long start, long mid, long end) {
	long i = start;
	long j = mid + 1;
	long k = start;

	while (i <= mid && j <= end) {
		if (data[i] <= data[j]) { //왼쪽이 작다면
			sorted[k] = data[i];  //작은 것을 정렬배열에 대입
			i++; //다음 숫자로 이동
		}
		else {
			// data[i] > data[j] 오른쪽이 작다면
			sorted[k] = data[j]; //작은 것을 정렬배열에 대입
			j++; //다음 숫자로 이동
		}
		k++;
	}
	if (i > mid) { //i가 먼저 정렬완료되면 j의 나머지는 갖다 붙인다.
		for (int t = j; t <= end; t++) {
			sorted[k] = data[t];
			k++;
		}
	}
	else { //j가 먼저 정렬완료되면 i의 나머지는 갖다 붙인다.
		for (int t = i; t <= mid; t++) {
			sorted[k] = data[t];
			k++;
		}
	}

	for (int t = start; t <= end; t++) { // 정렬된 배열을 원래 배열로 삽입
		data[t] = sorted[t];
	}
}

void merge_sort(long *data, long start, long end) { //재귀함수로 쓰인다.
	if (start < end) {
		int mid = (start + end) / 2; 
		merge_sort(data, start, mid); // 좌측 정렬 
		merge_sort(data, mid + 1, end); // 우측 정렬 
		merge(data, start, mid, end); //둘로 쪼개지는 재귀가 끝나고 1개 남았을때부터 병합이 호출됨.
	}
}

int*countingSort(long A[], int n, int k) { //n은 정렬할 배열 크기, k는 정렬할 수들중 최댓값.

	int i;
	
	/*정렬을 위해 임시배열 B와 C를 동적할당한다.*/
	int*C; //A배열에서 어떤 숫자가 몇 번 나오는지 세어 놓는 배열.
	C = (int*)malloc(sizeof(int)*k);
	int*B; //정렬된 배열
	B = (int*)malloc(sizeof(int)*n);

	for (i = 0; i <= k; i++) { //초기화
		C[i] = 0; 
	}
	for (i = 0; i < n; i++) { //A배열에서 어떤 숫자의 빈도와 C배열의 인덱스가 같음
		C[A[i]]++;
	}
	for (i = 1; i <= k; i++) { //누적(현재 바로 전까지 모든 빈도를 누적)
		C[i] = C[i] + C[i - 1];
	}
	for (i = n - 1; i >= 0; i--) { //B라는 배열에 수들을 정렬한다.
		B[C[A[i]] - 1] = A[i];
		C[A[i]]--;
	}
	return B; //정렬된 배열 리턴
}