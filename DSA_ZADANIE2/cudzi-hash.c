// cudzi-hash.c -- Dominik Mikuška, 21.10.2019 10:55

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "zadanie2.h"

// Prevzata implementacia ineho hashovania patri do tohto suboru.
// Dolezite: uvedte zdroj odkial ste to prevzali -- musi existovat v case konzultacii!

// ...
//Zatial najrozumnejsie: https://github.com/davidar/c-hashtable/blob/master/hashtable.c
//VERY EZ: https://github.com/jakogut/tinyht/blob/master/hash_table.c
//Celkom tazke na pochopenie: https://github.com/emiltayl/hashtable/blob/master/hashtable.c
//Lahke na pochopenie: https://github.com/qzchenwl/hashtable/blob/master/src/hashtbl.c


//POKUS: https://github.com/qzchenwl/hashtable

//CELY TENTO KOD JE PREBRATY Z https://github.com/qzchenwl/hashtable
HASHTBL *not_my_table;

int hashtbl_resize(HASHTBL *hashtbl, HSIZE size);
int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data);

static HSIZE bkdr_hash(const char *key)
{
	HSIZE seed = 131; // 31 131 1313 13131 131313 etc.
	HSIZE hash = 0;

	while (*key)
		hash = hash * seed + (*key++);

	return hash;
}

void hashtbl_create(HSIZE size)
{

	if (!(not_my_table = malloc(sizeof(HASHTBL))))
	{
		printf("MALLOC ERROR!\n");
		return;
	}

	if (!(not_my_table->nodes = calloc(size, sizeof(ENTRY*)))) {
		printf("CALLOC ERROR!\n");
		free(not_my_table);
		return;
	}

	not_my_table->size = size;
	not_my_table->count = 0;

	not_my_table->hashfunc = bkdr_hash;
}

void hashtbl_destroy()
{
	HSIZE n;
	ENTRY *node, *oldnode;
	HASHTBL *hashtbl = not_my_table;

	for (n = 0; n < hashtbl->size; ++n) {
		node = hashtbl->nodes[n];
		while (node) {
			free(node->key);
			oldnode = node;
			node = node->next;
			free(oldnode);
		}
	}
	free(hashtbl->nodes);
	free(hashtbl);
}

int hashtbl_insert_first(const char *key, void *data)
{
	return hashtbl_insert(not_my_table, key, data);
}

int hashtbl_insert(HASHTBL *hashtbl, const char *key, void *data)
{
	/* resize table if the threshold is exceeded
 * default threshold is:
 * <table size> * <load factor 0.75> */
	if (hashtbl->count >= hashtbl->size * 0.75) {
		hashtbl_resize(hashtbl, hashtbl->size * 2 + 1);
	}

	ENTRY *node;
	HSIZE hash = hashtbl->hashfunc(key) % hashtbl->size;

	node = hashtbl->nodes[hash];

	/* check if the key is already in the hashtbl */
	while (node) {
		if (!strcmp(node->key, key)) {
			node->data = data;
			return 0;
		}
		node = node->next;
	}

	/* create new entry */
	if (!(node = malloc(sizeof(ENTRY))))
		return -1;
	if (!(node->key = _strdup(key))) {
		free(node);
		return -1;
	}
	node->data = data;
	node->next = hashtbl->nodes[hash];
	hashtbl->nodes[hash] = node;
	hashtbl->count++;

	return hashtbl->size;
}

int hashtbl_get(const char *key)
{
	HASHTBL *hashtbl = not_my_table;
	ENTRY *node;
	HSIZE hash = hashtbl->hashfunc(key) % hashtbl->size;

	node = hashtbl->nodes[hash];
	while (node) {
		if (!strcmp(node->key, key)) {
			return 0;
		}
		node = node->next;
	}

	return 1;
}

int hashtbl_remove(HASHTBL *hashtbl, const char *key)
{
	ENTRY *node, *prevnode = NULL;
	HSIZE hash = hashtbl->hashfunc(key) % hashtbl->size;

	node = hashtbl->nodes[hash];
	while (node) {
		if (!strcmp(node->key, key)) {
			free(node->key);
			if (prevnode)
				prevnode->next = node->next;
			else
				hashtbl->nodes[hash] = node->next;
			free(node);
			hashtbl->count--;
			return 0;
		}
		prevnode = node;
		node = node->next;
	}

	return -1;
}

int hashtbl_resize(HASHTBL *hashtbl, HSIZE size)
{
	HASHTBL newtbl;
	HSIZE n;
	ENTRY *node, *next;

	newtbl.size = size;
	newtbl.count = 0;
	newtbl.hashfunc = hashtbl->hashfunc;

	if (!(newtbl.nodes = calloc(size, sizeof(ENTRY*))))
		return -1;

	for (n = 0; n < hashtbl->size; ++n) {
		for (node = hashtbl->nodes[n]; node; node = next) {
			next = node->next;
			hashtbl_insert(&newtbl, node->key, node->data);
			hashtbl_remove(hashtbl, node->key);

		}
	}

	free(hashtbl->nodes);
	hashtbl->size = newtbl.size;
	hashtbl->count = newtbl.count;
	hashtbl->nodes = newtbl.nodes;

	return 0;
}
