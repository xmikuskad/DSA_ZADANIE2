// zadanie2.c -- Dominik Mikuška, 21.10.2019 10:55
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <Windows.h>

#include "zadanie2.h"

#define TRUE 1
#define FALSE 0

//Ak pouzivame windows, tak pouzijeme jeho optimalnejsie funkcie na meranie casu
#ifdef __linux
#define WINDOWSFLAG 0
#else
#define WINDOWSFLAG 1
#endif

#if WINDOWSFLAG > 0
#include <windows.h>
void CallBVS(double* timeTogether, int num, unsigned long long *BVSSize, char insert)
{
	LARGE_INTEGER start, end, tmp;

	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*BVSSize += InsertBVS(num);
		QueryPerformanceCounter(&end);

	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (SearchBVS(num)) printf("not found BVS\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
}

void CallRB(double* timeTogether, int num, unsigned long long *RBSize, char insert)
{
	LARGE_INTEGER start, end, tmp;

	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*RBSize += insert_RB(num, num);
		QueryPerformanceCounter(&end);
	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (get_key_RB(num)) printf("not found RB\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
}

void CallNotMyHT(double* timeTogether, int num, unsigned long long *NotMyHTSize, char insert)
{
	LARGE_INTEGER start, end, tmp;
	char *tmp2 = malloc(31);
	sprintf(tmp2, "%d", num);
	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*NotMyHTSize = hashtbl_insert_first(tmp2, tmp2);
		QueryPerformanceCounter(&end);
	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (hashtbl_get(tmp2)) printf("not found NMHT\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
	free(tmp2);
}

void CallAVL(double* timeTogether, int num, unsigned long long *AVLSize, char insert)
{
	LARGE_INTEGER start, end, tmp;

	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*AVLSize += InsertAVL(num);
		QueryPerformanceCounter(&end);

	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (SearchAVL(num)) printf("not found AVL\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
}

void CallMyHT(double* timeTogether, int num, unsigned long long *MyHTSize, char insert)
{
	LARGE_INTEGER start, end, tmp;

	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*MyHTSize = InsertMyHT(num);
		QueryPerformanceCounter(&end);

	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (SearchMyHT(num)) printf("not found MyHT\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
}

#else

void CallBVS(double* timeTogether, int num, unsigned long long *BVSSize, char insert)
{
	clock_t start, end;

	if (insert)
	{
		start = clock();
		*BVSSize += InsertBVS(num);
		end = clock();

	}
	else
	{
		start = clock();
		if (SearchBVS(num)) printf("not found BVS\n");
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}

void CallRB(double* timeTogether, int num, unsigned long long *RBSize, char insert)
{
	clock_t start, end;

	if (insert)
	{
		start = clock();
		*RBSize += insert_RB(num, num);
		end = clock();

	}
	else
	{
		start = clock();
		if (get_key_RB(num)) printf("not found RB\n");
		//get_key_RB(num);
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}

void CallNotMyHT(double* timeTogether, int num, unsigned long long *NotMyHTSize, char insert)
{
	clock_t start, end;

	char *tmp = malloc(31);
	sprintf(tmp, "%d", num);

	if (insert)
	{
		start = clock();
		*NotMyHTSize = hashtbl_insert_first(tmp, tmp);
		end = clock();

	}
	else
	{
		start = clock();
		if (hashtbl_get(tmp))	printf("not found NMHT\n");
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
	free(tmp);
}

void CallAVL(double* timeTogether, int num, unsigned long long *AVLSize, char insert)
{
	clock_t start, end;

	if (insert)
	{
		start = clock();
		*AVLSize += InsertAVL(num);
		end = clock();

	}
	else
	{
		start = clock();
		if (SearchAVL(num)) printf("not found AVL\n");
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}

void CallMyHT(double* timeTogether, int num, unsigned long long *MyHTSize, char insert)
{
	clock_t start, end;

	if (insert)
	{
		start = clock();
		*MyHTSize = InsertMyHT(num);
		end = clock();

	}
	else
	{
		start = clock();
		if (SearchMyHT(num)) printf("not found MyHT\n");
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}


#endif

/*
void CallBVS(double* timeTogether, int num, unsigned long long *BVSSize, char insert)
{
	if (WINDOWSFLAG)
	{
		LARGE_INTEGER start, end, tmp;

		if (insert)
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			*BVSSize += InsertBVS(num);
			QueryPerformanceCounter(&end);

		}
		else
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			if (SearchBVS(num)) printf("not found BVS\n");
			QueryPerformanceCounter(&end);
		}

		*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
	}
	else
	{
		clock_t start, end;

		if (insert)
		{
			start = clock();
			*BVSSize += InsertBVS(num);
			end = clock();

		}
		else
		{
			start = clock();
			if (SearchBVS(num)) printf("not found BVS\n");
			end = clock();
		}
		*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
	}

}

void CallRB(double* timeTogether, int num, unsigned long long *RBSize, char insert)
{
	if (WINDOWSFLAG)
	{
		LARGE_INTEGER start, end, tmp;

		if (insert)
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			*RBSize += insert_RB(num, num);
			QueryPerformanceCounter(&end);
		}
		else
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			if (get_key_RB(num)) printf("not found RB\n");
			QueryPerformanceCounter(&end);
		}

		*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
	}
	else
	{
		clock_t start, end;

		if (insert)
		{
			start = clock();
			*RBSize += insert_RB(num, num);
			end = clock();

		}
		else
		{
			start = clock();
			if (get_key_RB(num)) printf("not found RB\n");
			//get_key_RB(num);
			end = clock();
		}
		*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
}

void CallNotMyHT(double* timeTogether, int num, unsigned long long *NotMyHTSize, char insert)
{
	if (WINDOWSFLAG)
	{
		LARGE_INTEGER start, end, tmp;
		char *tmp2 = malloc(31);
		sprintf(tmp2, "%d", num);
		if (insert)
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			*NotMyHTSize = hashtbl_insert_first(tmp2, tmp2);
			QueryPerformanceCounter(&end);
		}
		else
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			if (hashtbl_get(tmp2)) printf("not found NMHT\n");
			QueryPerformanceCounter(&end);
		}

		*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
		free(tmp2);
	}
	else
	{
		clock_t start, end;

		char *tmp = malloc(31);
		sprintf(tmp, "%d", num);

		if (insert)
		{
			start = clock();
			*NotMyHTSize = hashtbl_insert_first(tmp, tmp);
			end = clock();

		}
		else
		{
			start = clock();
			if (hashtbl_get(tmp))	printf("not found NMHT\n");
			end = clock();
		}
		*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
		free(tmp);
	}
}

void CallAVL(double* timeTogether, int num, unsigned long long *AVLSize, char insert)
{
	if (WINDOWSFLAG)
	{
		LARGE_INTEGER start, end, tmp;

		if (insert)
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			*AVLSize += InsertAVL(num);
			QueryPerformanceCounter(&end);

		}
		else
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			if (SearchAVL(num)) printf("not found AVL\n");
			QueryPerformanceCounter(&end);
		}

		*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
	}
	else
	{
		clock_t start, end;

		if (insert)
		{
			start = clock();
			*AVLSize += InsertAVL(num);
			end = clock();

		}
		else
		{
			start = clock();
			if (SearchAVL(num)) printf("not found AVL\n");
			end = clock();
		}
		*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
}

void CallMyHT(double* timeTogether, int num, unsigned long long *MyHTSize, char insert)
{
	if (WINDOWSFLAG)
	{
		LARGE_INTEGER start, end, tmp;

		if (insert)
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			*MyHTSize += InsertMyHT(num);
			QueryPerformanceCounter(&end);

		}
		else
		{
			QueryPerformanceFrequency(&tmp);
			QueryPerformanceCounter(&start);
			if (SearchMyHT(num)) printf("not found MyHT\n");
			QueryPerformanceCounter(&end);
		}

		*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
	}
	else
	{
		clock_t start, end;

		if (insert)
		{
			start = clock();
			*MyHTSize += InsertMyHT(num);
			end = clock();

		}
		else
		{
			start = clock();
			if (SearchMyHT(num)) printf("not found MyHT\n");
			end = clock();
		}
		*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
}
*/
void BasicTest(int max)
{
	unsigned long long NotMyHTSize = 0;
	unsigned long long RBSize = 0;
	unsigned long long BVSSize = 0;
	unsigned long long AVLSize = 0;
	unsigned long long MyHTSize = 0;
	double timeTogether = 0;

	//My BVS Tree
	timeTogether = 0;
	//INSERTS
	for (int i = 1; i <= max; i++)
	{
		CallBVS(&timeTogether, i, &BVSSize, TRUE);
	}

	printf("[BASIC] BVS Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	//SEARCH
	timeTogether = 0;
	BVSSize = 0;

	for (int i = 1; i <= max; i++)
	{
		CallBVS(&timeTogether, i, &BVSSize, FALSE);
	}

	printf("[BASIC] BVS Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	FreeBVSTree();


	//Red Black Tree
	timeTogether = 0;
	//INSERTS
	for (int i = 1; i <= max; i++)
	{
		CallRB(&timeTogether, i, &RBSize, TRUE);
	}

	printf("[BASIC] RB Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", RBSize);

	//SEARCH
	timeTogether = 0;
	RBSize = 0;

	for (int i = 1; i <= max; i++)
	{
		CallRB(&timeTogether, i, &RBSize, FALSE);
	}

	printf("[BASIC] RB Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", RBSize);

	EraseRBTree();

	//Not My Hashtable
	timeTogether = 0;
	//hashtbl_create(1013);

	//INSERTS
	for (int i = 1; i <= max; i++)
	{
		CallNotMyHT(&timeTogether, i, &NotMyHTSize, TRUE);
	}

	printf("[BASIC] NotMyHT Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", NotMyHTSize);

	//SEARCH
	timeTogether = 0;
	NotMyHTSize = 0;

	for (int i = 1; i <= max; i++)
	{
		CallNotMyHT(&timeTogether, i, &NotMyHTSize, FALSE);
	}

	printf("[BASIC] NotMyHT Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", NotMyHTSize);

	hashtbl_destroy();

	//My AVL Tree
	timeTogether = 0;
	//INSERTS
	for (int i = 1; i <= max; i++)
	{
		CallAVL(&timeTogether, i, &AVLSize, TRUE);
	}

	printf("[BASIC] AVL Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	//SEARCH
	timeTogether = 0;
	AVLSize = 0;

	for (int i = 1; i <= max; i++)
	{
		CallAVL(&timeTogether, i, &AVLSize, FALSE);
	}

	printf("[BASIC] AVL Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	FreeAVLTree();

	//My HT
	timeTogether = 0;
	//INSERTS
	for (int i = 1; i <= max; i++)
	{
		CallMyHT(&timeTogether, i, &MyHTSize, TRUE);
	}

	printf("[BASIC] MyHT Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", MyHTSize);

	//SEARCH
	timeTogether = 0;
	MyHTSize = 0;

	for (int i = 1; i <= max; i++)
	{
		CallMyHT(&timeTogether, i, &MyHTSize, FALSE);
	}

	printf("[BASIC] MyHT Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", MyHTSize);

	FreeMyHT();
}

void RandomTest(int max)
{
	unsigned long long NotMyHTSize = 0;
	unsigned long long RBSize = 0;
	unsigned long long BVSSize = 0;
	unsigned long long AVLSize = 0;
	unsigned long long MyHTSize = 0;
	double timeTogetherBVS = 0;
	double timeTogetherRB = 0;
	double timeTogetherNMHT = 0;
	double timeTogetherAVL = 0;
	double timeTogetherMyHT = 0;

	int	*arrayForSearch = malloc(max * sizeof(int));

	srand(time(0));	//Different results everytime

	for (int i = 0; i < max; i++)
	{
		int randomNum = rand() % 1000000;
		arrayForSearch[i] = randomNum;
		CallBVS(&timeTogetherBVS, randomNum, &BVSSize, TRUE);
		CallRB(&timeTogetherRB, randomNum, &RBSize, TRUE);
		CallNotMyHT(&timeTogetherNMHT, randomNum, &NotMyHTSize, TRUE);
		CallAVL(&timeTogetherAVL, randomNum, &AVLSize, TRUE);
		CallMyHT(&timeTogetherMyHT, randomNum, &MyHTSize, TRUE);
	}

	//My BVS Tree
	printf("[RANDOM] BVS Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherBVS);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	//Red Black Tree
	printf("[RANDOM] RB Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherRB);
	printf("Space used: %lld Bytes\n\n", RBSize);

	//Not My Hashtable
	printf("[RANDOM] NotMyHT Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherNMHT);
	printf("Space used: %lld Bytes\n\n", NotMyHTSize);

	//My AVL Tree
	printf("[RANDOM] AVL Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherAVL);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	//My HT
	printf("[RANDOM] MyHT Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherMyHT);
	printf("Space used: %lld Bytes\n\n", MyHTSize);

	timeTogetherBVS = 0;
	timeTogetherRB = 0;
	timeTogetherNMHT = 0;
	timeTogetherAVL = 0;
	timeTogetherMyHT = 0;
	NotMyHTSize = 0;
	RBSize = 0;
	BVSSize = 0;
	AVLSize = 0;
	MyHTSize = 0;

	for (int i = max - 1; i >= 0; i--)
	{
		CallBVS(&timeTogetherBVS, arrayForSearch[i], &BVSSize, FALSE);
		CallRB(&timeTogetherRB, arrayForSearch[i], &RBSize, FALSE);
		CallNotMyHT(&timeTogetherNMHT, arrayForSearch[i], &NotMyHTSize, FALSE);
		CallAVL(&timeTogetherAVL, arrayForSearch[i], &AVLSize, FALSE);
		CallMyHT(&timeTogetherMyHT, arrayForSearch[i], &MyHTSize, FALSE);
	}


	//My BVS Tree
	printf("[RANDOM] BVS Search\n");
	printf("Time taken: %f seconds\n", timeTogetherBVS);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	FreeBVSTree();


	//Red Black Tree
	printf("[RANDOM] RB Search\n");
	printf("Time taken: %f seconds\n", timeTogetherRB);
	printf("Space used: %lld Bytes\n\n", RBSize);

	EraseRBTree();

	//Not My Hashtable
	printf("[RANDOM] NotMyHT Search\n");
	printf("Time taken: %f seconds\n", timeTogetherNMHT);
	printf("Space used: %lld Bytes\n\n", NotMyHTSize);

	hashtbl_destroy();

	//My AVL Tree
	printf("[RANDOM] AVL Search\n");
	printf("Time taken: %f seconds\n", timeTogetherAVL);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	FreeAVLTree();

	//My HT
	printf("[RANDOM] MyHT Search\n");
	printf("Time taken: %f seconds\n", timeTogetherMyHT);
	printf("Space used: %lld Bytes\n\n", MyHTSize);

	FreeMyHT();

	free(arrayForSearch);

	timeTogetherBVS = 0;
	timeTogetherRB = 0;
	timeTogetherNMHT = 0;
	timeTogetherAVL = 0;
	timeTogetherMyHT = 0;
	NotMyHTSize = 0;
	RBSize = 0;
	BVSSize = 0;
	AVLSize = 0;
	MyHTSize = 0;
}

void SameTest(int max)
{
	unsigned long long NotMyHTSize = 0;
	unsigned long long RBSize = 0;
	unsigned long long BVSSize = 0;
	unsigned long long AVLSize = 0;
	unsigned long long MyHTSize = 0;
	double timeTogetherBVS = 0;
	double timeTogetherRB = 0;
	double timeTogetherNMHT = 0;
	double timeTogetherAVL = 0;
	double timeTogetherMyHT = 0;

	//int	*arrayForSearch = malloc(max * sizeof(int));

	int number = 5;

	for (int i = 0; i < max; i++)
	{
		CallBVS(&timeTogetherBVS, number, &BVSSize, TRUE);
		CallRB(&timeTogetherRB, number, &RBSize, TRUE);
		CallNotMyHT(&timeTogetherNMHT, number, &NotMyHTSize, TRUE);
		CallAVL(&timeTogetherAVL, number, &AVLSize, TRUE);
		CallMyHT(&timeTogetherMyHT, number, &MyHTSize, TRUE);
	}

	//My BVS Tree
	printf("[SAME] BVS Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherBVS);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	//Red Black Tree
	printf("[SAME] RB Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherRB);
	printf("Space used: %lld Bytes\n\n", RBSize);

	//Not My Hashtable
	printf("[SAME] NotMyHT Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherNMHT);
	printf("Space used: %lld Bytes\n\n", NotMyHTSize);

	//My AVL Tree
	printf("[SAME] AVL Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherAVL);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	//My HT
	printf("[SAME] MyHT Insert\n");
	printf("Time taken: %f seconds\n", timeTogetherMyHT);
	printf("Space used: %lld Bytes\n\n", MyHTSize);

	timeTogetherBVS = 0;
	timeTogetherRB = 0;
	timeTogetherNMHT = 0;
	timeTogetherAVL = 0;
	timeTogetherMyHT = 0;
	NotMyHTSize = 0;
	RBSize = 0;
	BVSSize = 0;
	AVLSize = 0;
	MyHTSize = 0;

	for (int i = max - 1; i >= 0; i--)
	{
		CallBVS(&timeTogetherBVS, number, &BVSSize, FALSE);
		CallRB(&timeTogetherRB, number, &RBSize, FALSE);
		CallNotMyHT(&timeTogetherNMHT, number, &NotMyHTSize, FALSE);
		CallAVL(&timeTogetherAVL, number, &AVLSize, FALSE);
		CallMyHT(&timeTogetherMyHT, number, &MyHTSize, FALSE);
	}


	//My BVS Tree
	printf("[SAME] BVS Search\n");
	printf("Time taken: %f seconds\n", timeTogetherBVS);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	FreeBVSTree();


	//Red Black Tree
	printf("[SAME] RB Search\n");
	printf("Time taken: %f seconds\n", timeTogetherRB);
	printf("Space used: %lld Bytes\n\n", RBSize);

	EraseRBTree();

	//Not My Hashtable
	printf("[SAME] NotMyHT Search\n");
	printf("Time taken: %f seconds\n", timeTogetherNMHT);
	printf("Space used: %lld Bytes\n\n", NotMyHTSize);

	hashtbl_destroy();

	//My AVL Tree
	printf("[SAME] AVL Search\n");
	printf("Time taken: %f seconds\n", timeTogetherAVL);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	FreeAVLTree();

	//My HT
	printf("[SAME] MyHT Search\n");
	printf("Time taken: %f seconds\n", timeTogetherMyHT);
	printf("Space used: %lld Bytes\n\n", MyHTSize);

	FreeMyHT();

}

// Funkcia main() by mala obsahovat testovanie
int main()
{
	//BasicTest(30000);
	//RandomTest(30000);
	//RandomTest(10);
	//SameTest(200);

	//BasicTest(100000);
	//RandomTest(100000);
	SameTest(20);

	system("pause");
	return 0;
}