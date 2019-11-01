// zadanie2.c -- Dominik Mikuška, 21.10.2019 10:55

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "zadanie2.h"

#define TRUE 1
#define FALSE 0


void CallBVS(double* timeTogether, BVStree **mainTree, int num, unsigned long long *BVSSize, char insert)
{
	clock_t start, end;

	if (insert)
	{
		start = clock();
		*BVSSize += InsertBVS(mainTree, num);
		end = clock();

	}
	else
	{
		start = clock();
		if (SearchBVS(*mainTree, num)) printf("not found\n");
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}

void BasicTestBVS(BVStree **mainBVSTree)
{
	unsigned long long BVSSize = 0;
	double timeTogether = 0;

	//INSERTS
	for (int i = 1; i <= 30000; i++)
	{
		CallBVS(&timeTogether, mainBVSTree, i, &BVSSize, TRUE);
	}

	printf("BVS Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	//SEARCH
	timeTogether = 0;
	BVSSize = 0;

	for (int i = 1; i <= 30000; i++)
	{
		CallBVS(&timeTogether, mainBVSTree, i, &BVSSize, FALSE);
	}

	printf("BVS Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n", BVSSize);

}

// Funkcia main() by mala obsahovat testovanie
int main()
{
	BVStree *mainBVSTree = NULL;

	BasicTestBVS(&mainBVSTree);



	system("pause");
	return 0;
}