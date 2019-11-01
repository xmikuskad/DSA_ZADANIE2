// zadanie2.h -- Dominik Mikuška, 21.10.2019 10:55

#pragma once

typedef struct BVSTree
{
	int value;
	struct BVSTree *left;
	struct BVSTree *right;
} BVStree;

/*#include "moj-vyvazeny.c"
#include "moj-hash.c"
#include "cudzi-vyvazeny.c"
#include "cudzi-hash.c"
#include "bvs.c"*/