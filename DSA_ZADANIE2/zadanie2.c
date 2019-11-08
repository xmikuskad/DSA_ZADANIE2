// zadanie2.c -- Dominik Mikuška, 21.10.2019 10:55
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "zadanie2.h"

#define TRUE 1
#define FALSE 0


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
	//itoa(num, tmp, 10);
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
		if (hashtbl_get(tmp))
			printf("not found NMHT\n");
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
		if (SearchAVL(num)) printf("not found BVS\n");
		end = clock();
	}
	*timeTogether += ((double)(end - start)) / CLOCKS_PER_SEC;
}

void BasicTest()
{
	unsigned long long NotMyHTSize = 0;
	unsigned long long RBSize = 0;
	unsigned long long BVSSize = 0;
	unsigned long long AVLSize = 0;
	double timeTogether = 0;

	//My BVS Tree
	timeTogether = 0;
	//INSERTS
	for (int i = 1; i <= 30000; i++)
	{
		CallBVS(&timeTogether, i, &BVSSize, TRUE);
	}

	printf("[BASIC] BVS Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", BVSSize);

	//SEARCH
	timeTogether = 0;
	BVSSize = 0;

	for (int i = 1; i <= 30000; i++)
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
	for (int i = 1; i <= 30000; i++)
	{
		CallRB(&timeTogether, i, &RBSize, TRUE);
	}

	printf("[BASIC] RB Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", RBSize);

	//SEARCH
	timeTogether = 0;
	RBSize = 0;

	for (int i = 1; i <= 30000; i++)
	{
		CallRB(&timeTogether, i, &RBSize, FALSE);
	}

	printf("[BASIC] RB Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", RBSize);

	EraseRBTree();

	//Not My Hashtable
	timeTogether = 0;
	hashtbl_create(1013);

	//INSERTS
	for (int i = 1; i <= 30000; i++)
	{
		CallNotMyHT(&timeTogether, i, &NotMyHTSize, TRUE);
	}

	printf("[BASIC] NotMyHT Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", NotMyHTSize);

	//SEARCH
	timeTogether = 0;
	NotMyHTSize = 0;

	for (int i = 1; i <= 30000; i++)
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
	for (int i = 1; i <= 30000; i++)
	{
		CallAVL(&timeTogether, i, &AVLSize, TRUE);
	}

	printf("[BASIC] AVL Insert\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	//SEARCH
	timeTogether = 0;
	AVLSize = 0;

	for (int i = 1; i <= 30000; i++)
	{
		CallAVL(&timeTogether, i, &AVLSize, FALSE);
	}

	printf("[BASIC] AVL Search\n");
	printf("Time taken: %f seconds\n", timeTogether);
	printf("Space used: %lld Bytes\n\n", AVLSize);

	FreeAVLTree();
}

void RandomTest()
{
	unsigned long long NotMyHTSize = 0;
	unsigned long long RBSize = 0;
	unsigned long long BVSSize = 0;
	unsigned long long AVLSize = 0;
	double timeTogetherBVS = 0;
	double timeTogetherRB = 0;
	double timeTogetherNMHT = 0;
	double timeTogetherAVL = 0;

	int	*arrayForSearch = malloc(30000 * sizeof(int));

	hashtbl_create(1013);

	srand(time(0));	//Different results everytime

	for (int i = 0; i < 30000; i++)
	{
		int randomNum = rand() % 1000000;
		arrayForSearch[i] = randomNum;
		CallBVS(&timeTogetherBVS, randomNum, &BVSSize, TRUE);
		CallRB(&timeTogetherRB, randomNum, &RBSize, TRUE);
		CallNotMyHT(&timeTogetherNMHT, randomNum, &NotMyHTSize, TRUE);
		CallAVL(&timeTogetherAVL, randomNum, &AVLSize, TRUE);
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

	timeTogetherBVS = 0;
	timeTogetherRB = 0;
	timeTogetherNMHT = 0;
	timeTogetherAVL = 0;
	NotMyHTSize = 0;
	RBSize = 0;
	BVSSize = 0;
	AVLSize = 0;

	for (int i = 30000 - 1; i >= 0; i--)
	{
		CallBVS(&timeTogetherBVS, arrayForSearch[i], &BVSSize, FALSE);
		CallRB(&timeTogetherRB, arrayForSearch[i], &RBSize, FALSE);
		CallNotMyHT(&timeTogetherNMHT, arrayForSearch[i], &NotMyHTSize, FALSE);
		CallAVL(&timeTogetherAVL, arrayForSearch[i], &AVLSize, FALSE);
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

	free(arrayForSearch);
}

//Otazky:
//Cas programu len 30 sec?
//Globalne premenne na start?
//Pripocitat do dlzky programu aj uvolnovanie/init hash TB?

// Funkcia main() by mala obsahovat testovanie
int main()
{
	BasicTest();
	RandomTest();


	system("pause");
	return 0;
}