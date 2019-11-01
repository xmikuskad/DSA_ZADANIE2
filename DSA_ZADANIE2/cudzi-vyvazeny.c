// cudzi-vyvazeny.c -- Dominik Mikuška, 21.10.2019 10:55

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>	//Vyzaduje prebraty kod

#include "zadanie2.h"

// Prevzata implementacia ineho vyvazeneho BVS patri do tohto suboru.
// Dolezite: uvedte zdroj odkial ste to prevzali -- musi existovat v case konzultacii!

// ...

//LINK: https://github.com/thabongshot/redblack
//Vyzaduje vela uprav: https://github.com/louiswins/RB-Tree/blob/master/RBtree.c
//Tiez celkom ez: https://github.com/sebastiencs/red-black-tree/blob/master/rbtree.c



//AKTUALNY POKUS: https://github.com/sebastiencs/red-black-tree

//CELY TENTO KOD JE PREBRATY Z https://github.com/sebastiencs/red-black-tree !

/*
** rbtree.c for epitech in /home/chapui_s/travaux/rbtree/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb 16 00:30:33 2015 chapui_s
** Last update Mon Feb 16 00:51:05 2015 chapui_s
*/


t_rbnode		*mainRBTree = (t_rbnode*)0;

static inline int	is_red(t_rbnode *node)
{
	return ((node) ? (node->color == RED) : (0));
}

static inline int	my_compare_RB(unsigned int key1, unsigned int key2)
{
	return ((key1 == key2) ? (0) : ((key1 < key2) ? (-1) : (1)));
}

static void		flip_color(t_rbnode *node)
{
	node->color = !(node->color);
	node->left->color = !(node->left->color);
	node->right->color = !(node->right->color);
}

static t_rbnode		*rotate_left_RB(t_rbnode *left)
{
	t_rbnode		*right;

	if (!left)
		return ((t_rbnode*)0);
	right = left->right;
	left->right = right->left;
	right->left = left;
	right->color = left->color;
	left->color = RED;
	return (right);
}

static t_rbnode		*rotate_right_RB(t_rbnode *right)
{
	t_rbnode		*left;

	if (!right)
		return ((t_rbnode*)0);
	left = right->left;
	right->left = left->right;
	left->right = right;
	left->color = right->color;
	right->color = RED;
	return (left);
}

t_rbnode                *create_node_RB(t_key key,
	t_value value)
{
	t_rbnode              *new;

	if ((new = (t_rbnode*)malloc(sizeof(*new))) == (t_rbnode*)0)
		return ((t_rbnode*)0);
	new->key = key;
	new->value = value;
	new->color = RED;
	new->left = (t_rbnode*)0;
	new->right = (t_rbnode*)0;
	return (new);
}

static t_rbnode		*insert_this_RB(t_rbnode *node, t_key key, t_value value)
{
	int			res;

	if (!node)
		return (create_node_RB(key, value));
	res = my_compare_RB(key, node->key);
	if (res == 0)
		node->value = value;
	else if (res < 0)
		node->left = insert_this_RB(node->left, key, value);
	else
		node->right = insert_this_RB(node->right, key, value);
	if (is_red(node->right) && !is_red(node->left))
		node = rotate_left_RB(node);
	if (is_red(node->left) && is_red(node->left->left))
		node = rotate_right_RB(node);
	if (is_red(node->left) && is_red(node->right))
		flip_color(node);
	return (node);
}

int		insert_RB(t_key key, t_value value)
{
	mainRBTree = insert_this_RB(mainRBTree, key, value);
	if (mainRBTree)
		mainRBTree->color = BLACK;
	return sizeof(t_rbnode);
}

int		get_key_RB(t_key key)
{
	int		cmp;

	t_rbnode *node = mainRBTree;

	while (node)
	{
		if (!(cmp = my_compare_RB(key, node->key)))
			return 0;
		node = ((cmp < 0) ? (node->left) : (node->right));
	}
	return 1;
}

inline t_rbnode		*balance_me_that(t_rbnode *node)
{
	if (is_red(node->right))
		node = rotate_left_RB(node);
	if (is_red(node->left) && is_red(node->left->left))
		node = rotate_right_RB(node);
	if (is_red(node->left) && is_red(node->right))
		flip_color(node);
	return (node);
}

void EraseRBTree()
{
	erase_tree_RB(mainRBTree);
}

void erase_tree_RB(t_rbnode *node)
{
	if (node)
	{
		if (node->left)
			erase_tree_RB(node->left);
		if (node->right)
			erase_tree_RB(node->right);
		node->left = (t_rbnode*)0;
		node->right = (t_rbnode*)0;
		free(node);
	}
}