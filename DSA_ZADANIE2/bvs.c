// bvs.c -- Dominik Mikuška, 21.10.2019 10:55

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zadanie2.h"

// Implementacia nevyvazeneho BVS patri do tohto suboru.

static BVStree *mainBVSTree = NULL;

int SearchBVS(int valueInc)
{
	BVStree *tmp = mainBVSTree;

	while (1)
	{
		if (tmp == NULL)
			return 1;

		if (tmp->value == valueInc)
			return 0;

		if (valueInc <= tmp->value)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	
}

int InsertBVS(int valueInc)
{
	BVStree **tmp = &mainBVSTree;

	while (1)
	{
		if (*tmp == NULL)
		{
			(*tmp) = malloc(sizeof(BVStree));
			(*tmp)->left = NULL;
			(*tmp)->right = NULL;
			(*tmp)->value = valueInc;

			return sizeof(BVStree);
		}
		else
		{
			if (valueInc <= (*tmp)->value)
			{
				tmp = &(*tmp)->left;
			}
			else
			{
				tmp = &(*tmp)->right;
			}
		}
	}

}

void FreeBVSTree()
{
	FreeMyBVSTree(mainBVSTree);
}

void FreeMyBVSTree(BVStree *tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		FreeMyBVSTree(tree->left);
	if (tree->right != NULL)
		FreeMyBVSTree(tree->right);
	free(tree);
}