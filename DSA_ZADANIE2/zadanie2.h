// zadanie2.h -- Dominik Mikuška, 21.10.2019 10:55

//BVS Tree
typedef struct BVSTree
{
	int value;
	struct BVSTree *left;
	struct BVSTree *right;
} BVStree;

int SearchBVS(int valueInc);
int InsertBVS(int valueInc);
void FreeMyBVSTree(BVStree *tree);
void FreeBVSTree();

//Red Black Tree
// Prebraty kod z https://github.com/sebastiencs/red-black-tree
/*
** rbtree.h for rbtree in /home/chapuis_s/rendu/rbtree
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Jan 26 19:41:38 2015 chapui_s
** Last update Mon Feb 16 01:01:46 2015 chapui_s
*/
typedef enum rbcolor
{
	BLACK = 0,
	RED = 1
}t_rbcolor;

typedef unsigned int t_key;
typedef unsigned int t_value;

typedef struct s_rbnode
{
	t_key			key;
	t_value		value;
	t_rbcolor		color;
	struct s_rbnode	*left;
	struct s_rbnode	*right;

}t_rbnode;

int		get_key_RB(t_key key);
int		insert_RB(t_key key, t_value value);
void		erase_tree_RB(t_rbnode *node);
void		EraseRBTree();
// Koniec prebrateho kodu z https://github.com/sebastiencs/red-black-tree

//Foreign hashing
// Prebraty kod z https://github.com/qzchenwl/hashtable
typedef size_t HSIZE;

typedef struct hashnode {
	char *key;
	void *data;
	struct hashnode *next;
} ENTRY;

typedef struct hashtbl {
	HSIZE size;
	HSIZE count;
	ENTRY **nodes;
	HSIZE(*hashfunc)(const char *);
} HASHTBL;

void hashtbl_destroy();
int hashtbl_get(const char *key);
int hashtbl_insert_first(const char *key, void *data);
void hashtbl_create(HSIZE size);

// Koniec prebrateho kodu z https://github.com/qzchenwl/hashtable

//AVL Tree

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

//My hash

typedef struct MyTable {
	int size;
	int usedSize;
	int *elements;
}myTable;

int SearchMyHT(int number);
int InsertMyHT(int number);
void FreeMyHT();