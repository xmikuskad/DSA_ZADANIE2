// bvs.c -- Dominik Mikuška, 21.10.2019 10:55

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zadanie2.h"

// Implementacia nevyvazeneho BVS patri do tohto suboru.

// ...
extern void bvs()
{
	printf("BVS BVS\n");
}

extern int SearchBVS(BVStree *treeInc, int valueInc)
{
	/*if (treeInc == NULL)
		return 1;

	if (treeInc->value == valueInc)
		return 0;

	if (valueInc <= treeInc->value)
		return SearchBVS(treeInc->left, valueInc);
	else
		return SearchBVS(treeInc->right, valueInc);*/

	BVStree *tmp = treeInc;

	while (1)
	{
		if (tmp == NULL)
			return 1;

		if (tmp->value == valueInc)
			return 0;

		if (valueInc <= treeInc->value)
			//return SearchBVS(treeInc->left, valueInc);
			tmp = tmp->left;
		else
			//return SearchBVS(treeInc->right, valueInc);
			tmp = tmp->right;
	}
	
}

extern int InsertBVS(BVStree **treeInc, int valueInc)
{
	BVStree **tmp = treeInc;

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

extern void FreeBVSTree(BVStree *tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		FreeBVSTree(tree->left);
	if (tree->right != NULL)
		FreeBVSTree(tree->right);
	free(tree);
}