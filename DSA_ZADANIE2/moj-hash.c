// moj-hash.c -- Dominik Mikuška, 21.10.2019 10:55

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Vlastna implementacia hashovania.

// ...

#define FACTOR  0.75

typedef struct MyTable {
	int size;
	int usedSize;
	int *elements;
}myTable;

myTable *myHTable = NULL;

int CreateTable(int sizeInc)
{
	if (myHTable == NULL)
	{
		myHTable = malloc(sizeof(myTable));
		myHTable->size = sizeInc;
		myHTable->usedSize = 0;
		myHTable->elements = calloc(sizeInc, sizeof(int));
	}
	return sizeof(myHTable);
}

int HashFunction(int num, int attempt, int size)
{
	return  (num + attempt) % size;
}

myTable* InsertMyHTFunc(myTable *tmpTable, int number)
{
	int attempt = 0;
	while (1)
	{

		if (tmpTable->elements[HashFunction(number, attempt, tmpTable->size)] != 0)
		{
			attempt++;
		}
		else
		{
			tmpTable->elements[HashFunction(number, attempt, tmpTable->size)] = number;
			tmpTable->usedSize++;
			break;
		}
	}

	return tmpTable;
}

void ResizeTable()
{
	myTable *tmpTable = malloc(sizeof(myTable));
	tmpTable->size = 2 * (myHTable->size);
	int maxElementsLoaded = myHTable->usedSize;
	tmpTable->elements = calloc(tmpTable->size, sizeof(int));
	tmpTable->usedSize = 0;

	int numCount = 0;
	int i = 0;


	//Zrychlenie - obcas netreba prehladat celu tabulku!
	while (numCount < maxElementsLoaded && i < myHTable->size)
	{
		int number = myHTable->elements[i];
		if (number != 0)
		{
			numCount++;
			tmpTable = InsertMyHTFunc(tmpTable, number);
		}

		i++;
	}

	free(myHTable->elements);
	free(myHTable);
	myHTable = tmpTable;

}

int SearchMyHT(int number)
{
	int i = 0;
	while (1)
	{
		if (myHTable->elements[HashFunction(number, i, myHTable->size)] == number) {
			return 0;
		}
		else
			i++;

		if (i > myHTable->size)
			return 1;
	}
}

int InsertMyHT(int number)
{
	if (myHTable == NULL)
	{
		CreateTable(1000);
	}

	InsertMyHTFunc(myHTable, number);
	if ((double)((double)myHTable->usedSize / (double)myHTable->size) > (double)FACTOR)
	{
		ResizeTable();
	}
	return sizeof(myHTable);
}


void FreeMyHT()
{
	free(myHTable->elements);
	free(myHTable);
	myHTable = NULL;
}
