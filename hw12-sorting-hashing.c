#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	// array 생성 시, 동적 할당할 크기 -> 소수
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

// array 관련 함수
int initialize(int **a); // array를 초기화하는 함수
int freeArray(int *a); // array의 할당된 메모리 영역을 해제하는 함수
void printArray(int *a); // array의 값들을 출력하는 함수

// Sort 함수들
int selectionSort(int *a); // 선택정렬 함수
int insertionSort(int *a); // 삽입정렬 함수
int bubbleSort(int *a); // 버블정렬 함수
int shellSort(int *a); // 쉘정렬 함수
int quickSort(int *a, int n); // 퀵정렬 함수

// hashing 관련 함수
int hashCode(int key);
int hashing(int *a, int **ht);
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL)); // 매번 다른 random 값을 생성하기 위함.

	printf("[----- [김지민] [2021041068] -----]\n\n");

	do{ // 조작 메뉴얼 출력
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		// 조작키 입력
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { // 선택한 조작키에 따른 동작 수행
		case 'z': case 'Z': // z, Z 조작키 입력 시, array 초기화
			initialize(&array);
			break;
		case 'q': case 'Q': // q, Q 조작키 입력 시, array의 할당된 메모리 영역 해제
			freeArray(array);
			break;
		case 's': case 'S': // s, S 조작키 입력 시,
			selectionSort(array);
			break;
		case 'i': case 'I': // i, I 조작키 입력 시,
			insertionSort(array);
			break;
		case 'b': case 'B': // b, B 조작키 입력 시,
			bubbleSort(array);
			break; 
		case 'l': case 'L': // l, L 조작키 입력 시,
			shellSort(array);
			break;
		case 'k': case 'K': // k, K 조작키 입력 시,
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H': // h, H 조작키 입력 시,
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E': // e, E 조작키 입력 시,
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': // p, P 조작키 입력 시, array의 값들을 출력
			printArray(array);
			break;
		default: // 그 이외의 조작키 입력 시, 오류 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q, Q 조작키 입력 시에만 프로그램 종료

	return 1;
}

int initialize(int** a) // array를 초기화하는 함수
{
	int *temp = NULL;

	
	if(*a == NULL) { // array의 할당된 메모리가 없을 경우, Max_ARRAY_SIZE만큼 int형 메모리 할당한다.
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  // main에 있는 array에서 할당받은 메모리를 접근할 수 있도록 주소값을 복사해 넘겨준다.
	} else // array에 할당된 메모리가 존재할 경우, 그 메모리 주소값을 복사해 temp에 복사해 넘겨준다.
		temp = *a;

		for(int i = 0; i < MAX_ARRAY_SIZE; i++) // temp가 포인팅하는 array을 random값으로 초기화한다.
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a) // array의 할당된 메모리 영역을 해제하는 함수
{
	if(a != NULL) // 할당된 메모리가 존재할 경우, 포인터가 가리키는 메모리 영역을 free
		free(a);
	return 0;
}

void printArray(int *a) // array의 값들을 출력하는 함수
{
	if (a == NULL) { // array가 존재하지 않을 경우, 오류 메시지 출력 후 종료
		printf("nothing to print.\n");
		return;
	}

	// array가 존재할 경우
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // array의 요소들을 인덱스를 이용해 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // array의 요소들에 담긴 값들을 인덱스에 맞춰 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) // 선택정렬 함수
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 선택정렬하기 전의 array 출력

	// 최소값을 찾아서 맨 앞에서부터 채워 오름차순으로 정렬(앞의 정렬된 부분은 접근하지 않고, 정렬되지 않은 뒤의 sub_array만 접근) 
	for (i = 0; i < MAX_ARRAY_SIZE; i++) // array의 맨 앞에서부터 최소값을 정렬
	{
		// 최소값을 정렬하려는 sub_array의 첫 번째 요소의 값으로 임의 지정
		minindex = i;
		min = a[i];

		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // sub_array 중 최소값 탐색
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		// 최소값과 sub_array의 첫 번째 요소값을 교환
		a[minindex] = a[i];
		a[i] = min;
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 선택정렬된 array를 출력
	
	return 0;
}

int insertionSort(int *a) // 삽입정렬 함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 삽입정렬하기 전의 array 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // array의 두 번째 요소부터 마지막 요소까지 삽입될 인덱스를 찾아 그 부분에 삽입
	{
		t = a[i]; // 삽입할 요소의 값
		j = i; // 삽입할 인덱스를 탐색할 변수
		while (a[j-1] > t && j > 0) // 삽입할 인덱스(위치) 탐색 및 재배열
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t; // 삽입할 인덱스의 요소에 값을 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 삽입정렬된 array를 출력

	return 0;
}

int bubbleSort(int *a) // 버블정렬 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 버블정렬하기 전의 array 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // array의 크기만큼 반복
	{
		for (j = 1; j < MAX_ARRAY_SIZE-i; j++) // 정렬되지 않은 앞의 sub_array의 최대값을 하나씩 sub_array의 마지막 인덱스에 쌓아 오름차순으로 정렬 
		{
			if (a[j-1] > a[j]) // 이웃한 요소 둘을 비교해 앞 요소의 값이 더 클 경우, 값을 서로 교환하여 오름차순으로 정렬 
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 버블정렬된 array 출력

	return 0;
}

int shellSort(int *a) // 쉘정렬 함수
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 쉘정렬하기 전의 array 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // array의 탐색 간격을 절반씩 줄여 나간다. 
	{
		for (i = 0; i < h; i++) // 탐색한 부분리스트 첫 번째 요소의 다음 요소의 부분리스트 탐색을 위한 i 인덱스 증가
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // array 탐색 간격만큼 범위를 증가시키며 부분리스트를 탐색
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v) // 삽입정렬과 유사하게, 부분리스트의 마지막 요소의 값이 삽입될 위치 탐색 및 재배열 
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 쉘정렬된 array 출력

	return 0;
}

int quickSort(int *a, int n) // 퀵정렬 함수 (recursive방식으로 구현)
{
	int v, t;
	int i, j;

	if (n > 1) // 정렬할 요소가 남았을 경우
	{
		v = a[n-1]; // 마지막 요소의 값
		i = -1; // 인덱스 0번부터 조사하기 위한 초기화
		j = n - 1; // 마지막 요소의 인덱스

		while(1)
		{
			while(a[++i] < v); // sub_array의 마지막 요소의 값보다 크거나 같은 값을 가진 요소의 인덱스 i 탐색
			while(a[--j] > v); // sub_array의 마지막 요소의 값보다 작거나 같은 값을 가진 요소의 인덱스 j 탐색

			if (i >= j) break; // i값이 j값보다 크거나 같은 값일 경우, while문 탈출
			
			// 탐색한 i와 j 인덱스의 요소에 담긴 값을 교환 
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		// while문을 탈출했을 때의 i 인덱스의 요소값과 sub_array의 마지막 요소값을 교환
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // 인덱스 i를 기준으로 앞과 인덱스 i의 요소까지의 sub_array에 대해 퀵정렬
		quickSort(a+i+1, n-i-1); // 인덱스 i를 기준으로 뒤의 sub_array에 대해 퀵정렬
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  
	} else {
		hashtable = *ht;	
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



