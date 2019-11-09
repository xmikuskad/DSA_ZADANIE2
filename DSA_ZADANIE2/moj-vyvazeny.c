// moj-vyvazeny.c -- Dominik Mikuška, 21.10.2019 10:55

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLTree {
	int num;
	short height;
	struct AVLTree *left;
	struct AVLTree *right;
}AVLtree;

int SearchAVL(int numInc);
int InsertAVL(int num);
void FreeAVLTree();
void FreeMyAVLTree(AVLtree *tree);

// Vlastna implementacia nejakeho vyvazeneho BVS patri do tohto suboru.

// ...

AVLtree *mainTree = NULL;

int SearchMyAVL(AVLtree *treeInc, int num);
int InsertMyAVL(int numInc, AVLtree **treeInc);

void FreeAVLTree()
{
	FreeMyAVLTree(mainTree);
	mainTree = NULL;
}

void FreeMyAVLTree(AVLtree *tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		FreeMyAVLTree(tree->left);
	if (tree->right != NULL)
		FreeMyAVLTree(tree->right);
	free(tree);
}

int SearchAVL(int num)
{
	return SearchMyAVL(mainTree, num);
}

int SearchMyAVL(AVLtree *treeInc, int num)
{

	if (treeInc == NULL)
		return 1;

	if (num < treeInc->num)
	{
		return SearchMyAVL(treeInc->left, num);
	}
	else
		if (num > treeInc->num)
		{
			return SearchMyAVL(treeInc->right, num);
		}
		else
			return 0;
}


int GetMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int GetHeight(AVLtree *treeInc)
{
	if (treeInc == NULL)
		return -1;
	else
		return treeInc->height;
}

void SetHeight(AVLtree *treeInc)
{
	if (treeInc != NULL)
	{
		if ((treeInc)->left != NULL || (treeInc)->right != NULL)
		{
			(treeInc)->height = GetMax(GetHeight((treeInc)->left), GetHeight((treeInc)->right)) + 1;
		}
		else
		{
			(treeInc)->height = 0;
		}
	}
}

AVLtree* RotateLeft(AVLtree *treeInc)
{
	AVLtree *tmp = (treeInc)->right;
	//if ((treeInc)->right != NULL)
	//{
	(treeInc)->right = (tmp)->left;

	(tmp)->left = treeInc;


	SetHeight((tmp)->left);
	SetHeight((tmp)->right);
	//}
	SetHeight(tmp);

	return tmp;
}

AVLtree* RotateRight(AVLtree *treeInc)
{
	AVLtree *tmp = (treeInc)->left;
	//if ((treeInc)->left != NULL)
	//{
	(treeInc)->left = (tmp)->right;
	(tmp)->right = treeInc;



	SetHeight((tmp)->left);
	SetHeight((tmp)->right);
	//}

	SetHeight(tmp);

	return tmp;
}

AVLtree* RotateLeftRight(AVLtree *treeInc)
{
	(treeInc)->right = RotateRight((treeInc)->right);
	treeInc = RotateLeft(treeInc);

	return treeInc;
}

AVLtree* RotateRightLeft(AVLtree *treeInc)
{
	//print2D(mainTree);
	(treeInc)->left = RotateLeft((treeInc)->left);
	//print2D(mainTree);
	treeInc = RotateRight(treeInc);
	//print2D(mainTree);

	return treeInc;
}

int GetSpecialHeight(AVLtree *treeInc)
{
	if (treeInc == NULL)
	{
		return 0;
	}
	else
		return treeInc->height + 1;
}

int GetBalance(AVLtree *treeInc)
{
	if (treeInc == NULL)
	{
		return 0;
	}
	else
		return GetSpecialHeight(treeInc->left) - GetSpecialHeight(treeInc->right);
}

int InsertAVL(int num)
{
	return InsertMyAVL(num, &mainTree);
}

int InsertMyAVL(int numInc, AVLtree **treeInc)
{
	int tmp;
	if (*treeInc == NULL)
	{
		(*treeInc) = malloc(sizeof(AVLtree));
		(*treeInc)->left = NULL;
		(*treeInc)->right = NULL;
		(*treeInc)->num = numInc;
		(*treeInc)->height = 0;
		return sizeof(AVLtree);
	}
	else
	{
		if (numInc > (*treeInc)->num)
		{
			tmp = InsertMyAVL(numInc, &(*treeInc)->right);
			int mainBalance = abs(GetBalance(*treeInc));
			if (mainBalance >= 2)
			{
				int balance = GetBalance((*treeInc)->right);
				if (balance < 0)
				{
					*treeInc = RotateLeft(*treeInc);
				}
				else
					if (balance > 0)
					{
						*treeInc = RotateLeftRight(*treeInc);
					}
			}
		}
		else
			if (numInc <= (*treeInc)->num)
			{
				tmp = InsertMyAVL(numInc, &(*treeInc)->left);

				int mainBalance = abs(GetBalance(*treeInc));
				if (mainBalance >= 2)
				{
					int balance = GetBalance((*treeInc)->left);
					if (balance > 0)
					{
						*treeInc = RotateRight(*treeInc);
					}
					else
						if (balance < 0)
						{
							*treeInc = RotateRightLeft(*treeInc);
						}
				}
			}
			else
				tmp = 0;
	}
	SetHeight(*treeInc);
	return tmp;
}