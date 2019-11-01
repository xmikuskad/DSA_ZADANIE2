// zadanie2.c -- Dominik Mikuška, 21.10.2019 10:55
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "zadanie2.h"

#define TRUE 1
#define FALSE 0


void CallBVS(double* timeTogether,int num, unsigned long long *BVSSize, char insert)
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
		if (SearchBVS(num)) printf("not found\n");
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}

void BasicTestBVS()
{
	unsigned long long BVSSize = 0;
	double timeTogether = 0;

	//INSERTS
	for (int i = 1; i <= 30000; i++)
	{
		CallBVS(&timeTogether, i, &BVSSize, TRUE);
	}

	printf("BVS Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	//SEARCH
	timeTogether = 0;
	BVSSize = 0;

	for (int i = 1; i <= 30000; i++)
	{
		CallBVS(&timeTogether, i, &BVSSize, FALSE);
	}

	printf("BVS Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n", BVSSize);

	//FreeBVSTree();

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
		if (get_key_RB(num)) printf("not found\n");
		//get_key_RB(num);
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}

void BasicTestRB()
{
	unsigned long long RBSize = 0;
	double timeTogether = 0;

	//INSERTS
	for (int i = 1; i <= 30000; i++)
	{
		CallRB(&timeTogether, i, &RBSize, TRUE);
	}

	printf("\nRB Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", RBSize);

	//SEARCH
	timeTogether = 0;
	RBSize = 0;

	for (int i = 1; i <= 30000; i++)
	{
		CallRB(&timeTogether, i, &RBSize, FALSE);
	}

	printf("RB Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n", RBSize);

}

// Funkcia main() by mala obsahovat testovanie
int main()
{
	BasicTestBVS();
	BasicTestRB();



	system("pause");
	return 0;
}