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


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
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



