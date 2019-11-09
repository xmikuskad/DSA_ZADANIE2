// zadanie2.c -- Dominik Mikuška, 21.10.2019 10:55
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <Windows.h>

#include "zadanie2.h"

#define INSERT 1
#define SEARCH 0

//Ak pouzivame windows, tak pouzijeme jeho optimalnejsie funkcie na meranie casu
#ifdef __linux
#define WINDOWSFLAG 0
#else
#define WINDOWSFLAG 1
#endif
//#define WINDOWSFLAG 0

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


void BasicTest(int max, int debugCount)
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


	double **timeElapsed = malloc(10 * sizeof(double*));

	//Prvych 5 je rychlost insertu a druhych 5 je rychlost searchu
	for (int i = 0; i < 10; i++)
	{
		timeElapsed[i] = calloc((max + debugCount - 1) / debugCount, sizeof(double));
	}

	int averageCount = 0;

	while (averageCount < 3)
	{
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


		long long arrayCounter = 0;
		for (int i = 0; i < max; i++)
		{
			CallBVS(&timeTogetherBVS, i+1, &BVSSize, INSERT);
			CallRB(&timeTogetherRB, i+1, &RBSize, INSERT);
			CallNotMyHT(&timeTogetherNMHT, i+1, &NotMyHTSize, INSERT);
			CallAVL(&timeTogetherAVL, i+1, &AVLSize, INSERT);
			CallMyHT(&timeTogetherMyHT, i+1, &MyHTSize, INSERT);

			if (i != 0 && i%debugCount == 0)
			{
				timeElapsed[0][arrayCounter] += timeTogetherBVS;
				timeElapsed[1][arrayCounter] += timeTogetherRB;
				timeElapsed[2][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3][arrayCounter] += timeTogetherAVL;
				timeElapsed[4][arrayCounter] += timeTogetherMyHT;

				arrayCounter++;
			}


		}

		timeElapsed[0][arrayCounter] += timeTogetherBVS;
		timeElapsed[1][arrayCounter] += timeTogetherRB;
		timeElapsed[2][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3][arrayCounter] += timeTogetherAVL;
		timeElapsed[4][arrayCounter] += timeTogetherMyHT;

		timeTogetherBVS = 0;
		timeTogetherRB = 0;
		timeTogetherNMHT = 0;
		timeTogetherAVL = 0;
		timeTogetherMyHT = 0;


		arrayCounter = 0;
		for (int i = 0; i < max; i++)
		{
			CallBVS(&timeTogetherBVS, i+1, &BVSSize, SEARCH);
			CallRB(&timeTogetherRB, i+1, &RBSize, SEARCH);
			CallNotMyHT(&timeTogetherNMHT, i+1, &NotMyHTSize, SEARCH);
			CallAVL(&timeTogetherAVL, i+1, &AVLSize, SEARCH);
			CallMyHT(&timeTogetherMyHT, i+1, &MyHTSize, SEARCH);

			if (i != 0 && i%debugCount == 0)
			{
				timeElapsed[0 + 5][arrayCounter] += timeTogetherBVS;
				timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
				timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
				timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;

				arrayCounter++;
			}
		}

		timeElapsed[0 + 5][arrayCounter] += timeTogetherBVS;
		timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
		timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
		timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;


		FreeBVSTree();
		EraseRBTree();
		hashtbl_destroy();
		FreeAVLTree();
		FreeMyHT();

		averageCount++;
	}

	//Vypis priemeru
	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		//My BVS Tree
		printf("[BASIC %d] BVS Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[0][i] / 3);
		printf("Space used: %lld Bytes\n\n", BVSSize);

		//Red Black Tree
		printf("[BASIC %d] RB Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[1][i] / 3);
		printf("Space used: %lld Bytes\n\n", RBSize);

		//Not My Hashtable
		printf("[BASIC %d] NotMyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[2][i] / 3);
		printf("Space used: %lld Bytes\n\n", NotMyHTSize);

		//My AVL Tree
		printf("[BASIC %d] AVL Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[3][i] / 3);
		printf("Space used: %lld Bytes\n\n", AVLSize);

		//My HT
		printf("[BASIC %d] MyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[4][i] / 3);
		printf("Space used: %lld Bytes\n\n", MyHTSize);
	}

	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		//My BVS Tree
		printf("[BASIC %d] BVS Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[0 + 5][i] / 3);

		//Red Black Tree
		printf("[BASIC %d] RB Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[1 + 5][i] / 3);

		//Not My Hashtable
		printf("[BASIC %d] NotMyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[2 + 5][i] / 3);

		//My AVL Tree
		printf("[BASIC %d] AVL Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[3 + 5][i] / 3);

		//My HT
		printf("[BASIC %d] MyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[4 + 5][i] / 3);
	}

	FILE *file;

	file = fopen("basic.txt", "w+");

	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		fprintf(file, "%d\n", position);

	}


	int j = 0;
	while (j < 5)
	{
		switch (j)
		{
		case 0:	fprintf(file, "\nBVS\n");
			break;
		case 1:	fprintf(file, "\nRB\n");
			break;
		case 2:	fprintf(file, "\nNotMyHT\n");
			break;
		case 3:	fprintf(file, "\nAVL\n");
			break;
		case 4:	fprintf(file, "\nMyHT\n");
			break;
		default:
			break;
		}

		for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
		{
			int position = (i + 1)*debugCount;

			if (position > max)
				position = max;


			//fprintf(file, "%d - ", position);
			fprintf(file, "%f\n", timeElapsed[j][i] / 3);
		}
		fprintf(file, "\n-----END OF INSERT-----\n");
		j++;
	}

	while (j < 10)
	{

		switch (j)
		{
		case 5:	fprintf(file, "\nBVS\n");
			break;
		case 6:	fprintf(file, "\nRB\n");
			break;
		case 7:	fprintf(file, "\nNotMyHT\n");
			break;
		case 8:	fprintf(file, "\nAVL\n");
			break;
		case 9:	fprintf(file, "\nMyHT\n");
			break;
		default:
			break;
		}
		for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
		{
			int position = (i + 1)*debugCount;

			if (position > max)
				position = max;


			//fprintf(file, "%d - ", position);
			fprintf(file, "%f\n", timeElapsed[j][i] / 3);
		}
		fprintf(file, "\n-----END OF SEARCH-----\n");
		j++;
	}

	fclose(file);


	for (int i = 0; i < 10; i++)
	{
		free(timeElapsed[i]);
	}
	free(timeElapsed);
}

void RandomTest(int max,int debugCount)
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

	srand(time(0));	//Different results everytime

	double **timeElapsed = malloc(10 * sizeof(double*));

	//Prvych 5 je rychlost insertu a druhych 5 je rychlost searchu
	for (int i = 0; i < 10; i++)
	{
		timeElapsed[i] = calloc((max + debugCount - 1) / debugCount, sizeof(double));
	}

	int averageCount = 0;

	while (averageCount < 3)
	{
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

		int	*arrayForSearch = malloc(max * sizeof(int));

		long long arrayCounter = 0;
		for (int i = 0; i < max; i++)
		{
			int randomNum = rand() % 1000000;
			arrayForSearch[i] = randomNum;
			CallBVS(&timeTogetherBVS, randomNum, &BVSSize, INSERT);
			CallRB(&timeTogetherRB, randomNum, &RBSize, INSERT);
			CallNotMyHT(&timeTogetherNMHT, randomNum, &NotMyHTSize, INSERT);
			CallAVL(&timeTogetherAVL, randomNum, &AVLSize, INSERT);
			CallMyHT(&timeTogetherMyHT, randomNum, &MyHTSize, INSERT);

			if (i != 0 && i%debugCount == 0)
			{
				timeElapsed[0][arrayCounter] += timeTogetherBVS;
				timeElapsed[1][arrayCounter] += timeTogetherRB;
				timeElapsed[2][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3][arrayCounter] += timeTogetherAVL;
				timeElapsed[4][arrayCounter] += timeTogetherMyHT;

				arrayCounter++;
			}
		}

		timeElapsed[0][arrayCounter] += timeTogetherBVS;
		timeElapsed[1][arrayCounter] += timeTogetherRB;
		timeElapsed[2][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3][arrayCounter] += timeTogetherAVL;
		timeElapsed[4][arrayCounter] += timeTogetherMyHT;

		timeTogetherBVS = 0;
		timeTogetherRB = 0;
		timeTogetherNMHT = 0;
		timeTogetherAVL = 0;
		timeTogetherMyHT = 0;

		arrayCounter = 0;
		int j = 0;
		for (int i = max - 1; i >= 0; i--, j++)
		{
			CallBVS(&timeTogetherBVS, arrayForSearch[i], &BVSSize, SEARCH);
			CallRB(&timeTogetherRB, arrayForSearch[i], &RBSize, SEARCH);
			CallNotMyHT(&timeTogetherNMHT, arrayForSearch[i], &NotMyHTSize, SEARCH);
			CallAVL(&timeTogetherAVL, arrayForSearch[i], &AVLSize, SEARCH);
			CallMyHT(&timeTogetherMyHT, arrayForSearch[i], &MyHTSize, SEARCH);

			if (j != 0 && j%debugCount == 0)
			{
				timeElapsed[0 + 5][arrayCounter] += timeTogetherBVS;
				timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
				timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
				timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;

				arrayCounter++;
			}


		}

		timeElapsed[0 + 5][arrayCounter] += timeTogetherBVS;
		timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
		timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
		timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;

	
		FreeBVSTree();
		EraseRBTree();
		hashtbl_destroy();
		FreeAVLTree();
		FreeMyHT();

		free(arrayForSearch);

		averageCount++;
	}

	//Vypis priemeru
	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		//My BVS Tree
		printf("[RANDOM %d] BVS Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[0][i] / 3);
		printf("Space used: %lld Bytes\n\n", BVSSize);

		//Red Black Tree
		printf("[RANDOM %d] RB Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[1][i] / 3);
		printf("Space used: %lld Bytes\n\n", RBSize);

		//Not My Hashtable
		printf("[RANDOM %d] NotMyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[2][i] / 3);
		printf("Space used: %lld Bytes\n\n", NotMyHTSize);

		//My AVL Tree
		printf("[RANDOM %d] AVL Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[3][i] / 3);
		printf("Space used: %lld Bytes\n\n", AVLSize);

		//My HT
		printf("[RANDOM %d] MyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[4][i] / 3);
		printf("Space used: %lld Bytes\n\n", MyHTSize);
	}

	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		//My BVS Tree
		printf("[RANDOM %d] BVS Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[0 + 5][i] / 3);

		//Red Black Tree
		printf("[RANDOM %d] RB Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[1 + 5][i] / 3);

		//Not My Hashtable
		printf("[RANDOM %d] NotMyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[2 + 5][i] / 3);

		//My AVL Tree
		printf("[RANDOM %d] AVL Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[3 + 5][i] / 3);

		//My HT
		printf("[RANDOM %d] MyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[4 + 5][i] / 3);
	}

	FILE *file;

	file = fopen("random.txt", "w+");

	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		fprintf(file, "%d\n", position);

	}


	int j = 0;
	while (j < 5)
	{
		switch (j)
		{
		case 0:	fprintf(file, "\nBVS\n");
			break;
		case 1:	fprintf(file, "\nRB\n");
			break;
		case 2:	fprintf(file, "\nNotMyHT\n");
			break;
		case 3:	fprintf(file, "\nAVL\n");
			break;
		case 4:	fprintf(file, "\nMyHT\n");
			break;
		default:
			break;
		}

		for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
		{
			int position = (i + 1)*debugCount;

			if (position > max)
				position = max;


			//fprintf(file, "%d - ", position);
			fprintf(file, "%f\n", timeElapsed[j][i] / 3);
		}
		fprintf(file, "\n-----END OF INSERT-----\n");
		j++;
	}

	while (j < 10)
	{

		switch (j)
		{
		case 5:	fprintf(file, "\nBVS\n");
			break;
		case 6:	fprintf(file, "\nRB\n");
			break;
		case 7:	fprintf(file, "\nNotMyHT\n");
			break;
		case 8:	fprintf(file, "\nAVL\n");
			break;
		case 9:	fprintf(file, "\nMyHT\n");
			break;
		default:
			break;
		}
		for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
		{
			int position = (i + 1)*debugCount;

			if (position > max)
				position = max;


			//fprintf(file, "%d - ", position);
			fprintf(file, "%f\n", timeElapsed[j][i] / 3);
		}
		fprintf(file, "\n-----END OF SEARCH-----\n");
		j++;
	}

	fclose(file);

	for (int i = 0; i < 10; i++)
	{
		free(timeElapsed[i]);
	}
	free(timeElapsed);
}

void SameTest(int max, int debugCount)
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


	double **timeElapsed = malloc(10 * sizeof(double*));

	//Prvych 5 je rychlost insertu a druhych 5 je rychlost searchu
	for (int i = 0; i < 10; i++)
	{
		timeElapsed[i] = calloc((max + debugCount - 1) / debugCount, sizeof(double));
	}

	int averageCount = 0;

	while (averageCount < 3)
	{
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

		int number = 5;

		long long arrayCounter = 0;
		for (int i = 0; i < max; i++)
		{
			CallBVS(&timeTogetherBVS, number, &BVSSize, INSERT);
			CallRB(&timeTogetherRB, number, &RBSize, INSERT);
			CallNotMyHT(&timeTogetherNMHT, number, &NotMyHTSize, INSERT);
			CallAVL(&timeTogetherAVL, number, &AVLSize, INSERT);
			CallMyHT(&timeTogetherMyHT, number, &MyHTSize, INSERT);

			if (i != 0 && i%debugCount == 0)
			{
				timeElapsed[0][arrayCounter] += timeTogetherBVS;
				timeElapsed[1][arrayCounter] += timeTogetherRB;
				timeElapsed[2][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3][arrayCounter] += timeTogetherAVL;
				timeElapsed[4][arrayCounter] += timeTogetherMyHT;

				arrayCounter++;
			}


		}

		timeElapsed[0][arrayCounter] += timeTogetherBVS;
		timeElapsed[1][arrayCounter] += timeTogetherRB;
		timeElapsed[2][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3][arrayCounter] += timeTogetherAVL;
		timeElapsed[4][arrayCounter] += timeTogetherMyHT;

		timeTogetherBVS = 0;
		timeTogetherRB = 0;
		timeTogetherNMHT = 0;
		timeTogetherAVL = 0;
		timeTogetherMyHT = 0;


		arrayCounter = 0;
		for (int i = 0; i < max; i++)
		{
			CallBVS(&timeTogetherBVS, number, &BVSSize, SEARCH);
			CallRB(&timeTogetherRB, number, &RBSize, SEARCH);
			CallNotMyHT(&timeTogetherNMHT, number, &NotMyHTSize, SEARCH);
			CallAVL(&timeTogetherAVL, number, &AVLSize, SEARCH);
			CallMyHT(&timeTogetherMyHT, number, &MyHTSize, SEARCH);

			if (i != 0 && i%debugCount == 0)
			{
				timeElapsed[0 + 5][arrayCounter] += timeTogetherBVS;
				timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
				timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
				timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;

				arrayCounter++;
			}
		}

		timeElapsed[0 + 5][arrayCounter] += timeTogetherBVS;
		timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
		timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
		timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;


		FreeBVSTree();
		EraseRBTree();
		hashtbl_destroy();
		FreeAVLTree();
		FreeMyHT();
		
		averageCount++;
	}

	//Vypis priemeru
	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		//My BVS Tree
		printf("[SAME %d] BVS Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[0][i] / 3);
		printf("Space used: %lld Bytes\n\n", BVSSize);

		//Red Black Tree
		printf("[SAME %d] RB Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[1][i] / 3);
		printf("Space used: %lld Bytes\n\n", RBSize);

		//Not My Hashtable
		printf("[SAME %d] NotMyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[2][i] / 3);
		printf("Space used: %lld Bytes\n\n", NotMyHTSize);

		//My AVL Tree
		printf("[SAME %d] AVL Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[3][i] / 3);
		printf("Space used: %lld Bytes\n\n", AVLSize);

		//My HT
		printf("[SAME %d] MyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[4][i] / 3);
		printf("Space used: %lld Bytes\n\n", MyHTSize);
	}

	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		//My BVS Tree
		printf("[SAME %d] BVS Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[0 + 5][i] / 3);

		//Red Black Tree
		printf("[SAME %d] RB Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[1 + 5][i] / 3);

		//Not My Hashtable
		printf("[SAME %d] NotMyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[2 + 5][i] / 3);

		//My AVL Tree
		printf("[SAME %d] AVL Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[3 + 5][i] / 3);

		//My HT
		printf("[SAME %d] MyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[4 + 5][i] / 3);
	}

	FILE *file;

	file = fopen("same.txt", "w+");

	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		fprintf(file, "%d\n", position);

	}


	int j = 0;
	while (j < 5)
	{
		switch (j)
		{
		case 0:	fprintf(file, "\nBVS\n");
			break;
		case 1:	fprintf(file, "\nRB\n");
			break;
		case 2:	fprintf(file, "\nNotMyHT\n");
			break;
		case 3:	fprintf(file, "\nAVL\n");
			break;
		case 4:	fprintf(file, "\nMyHT\n");
			break;
		default:
			break;
		}

		for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
		{
			int position = (i + 1)*debugCount;

			if (position > max)
				position = max;


			//fprintf(file, "%d - ", position);
			fprintf(file, "%f\n", timeElapsed[j][i] / 3);
		}
		fprintf(file, "\n-----END OF INSERT-----\n");
		j++;
	}

	while (j < 10)
	{

		switch (j)
		{
		case 5:	fprintf(file, "\nBVS\n");
			break;
		case 6:	fprintf(file, "\nRB\n");
			break;
		case 7:	fprintf(file, "\nNotMyHT\n");
			break;
		case 8:	fprintf(file, "\nAVL\n");
			break;
		case 9:	fprintf(file, "\nMyHT\n");
			break;
		default:
			break;
		}
		for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
		{
			int position = (i + 1)*debugCount;

			if (position > max)
				position = max;


			//fprintf(file, "%d - ", position);
			fprintf(file, "%f\n", timeElapsed[j][i] / 3);
		}
		fprintf(file, "\n-----END OF SEARCH-----\n");
		j++;
	}

	fclose(file);

	for (int i = 0; i < 10; i++)
	{
		free(timeElapsed[i]);
	}
	free(timeElapsed);
}

// Funkcia main() by mala obsahovat testovanie
int main()
{
	SameTest(20000, 1000);
	RandomTest(20000, 1000);
	BasicTest(20000, 1000);


	system("pause");
	return 0;
}