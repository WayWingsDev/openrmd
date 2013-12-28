#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "dlist.h"

#define MULTIPILER	31

/* hash item */
#define hash_item_t dlist_node_t

struct hash_table_t {
	hash_item_t **table;	/* pointer of hash table start address */
	int         size;	/* hash table size */
	hash_func_t hashfunc;	/* hash function */
};

inline unsigned int hash_func_val(const int table_size, void *data)
{
	return (unsigned int)data % table_size;
}

inline unsigned int hash_func_str(const int table_size, void *data)
{
	unsigned int h;
	unsigned char *p;

	h = 0;
	for (p = (unsigned char *)data; *p != '\0'; p++)
		h = MULTIPILER * h + *p;
	return h % table_size;
}

hash_table_t *hash_init(int table_size, hash_func_t hashfunc)
{
	hash_table_t *table;

	if (table_size <= 0)
		return NULL;

	table = malloc(sizeof(hash_table_t));
	if (table == NULL)
		return NULL;
	table->table = calloc(table_size, sizeof(hash_item_t *));
	if (table->table == NULL) {
		free(table);
		return NULL;
	}
	table->size = table_size;
	table->hashfunc = hashfunc;

	return table;
}

inline int hash_add(hash_table_t *table, void *data)
{
	unsigned int index;

	if (table == NULL)
		return -1;

	index = table->hashfunc(table->size, data);
	return dlist_add(&table->table[index], data);
}

inline int hash_del(hash_table_t *table, void *data, ds_cmpfunc_t cmp, 
		void *val, ds_callback_t cb, void *param)
{
	unsigned int index;

	if (table == NULL)
		return -1;

	index = table->hashfunc(table->size, data);
	return dlist_del(&table->table[index], cmp, val, cb, param);
}

inline int hash_entry(hash_table_t *table, void *data, ds_cmpfunc_t cmp, 
		void *val, void **item)
{
	unsigned int index;

	if (table == NULL || item == NULL)
		return -1;

	index = table->hashfunc(table->size, data);
	return dlist_entry(table->table[index], cmp, val, item);
}

inline int hash_modify(hash_table_t *table, void *data, 
		ds_cmpfunc_t cmp, void *val, ds_callback_t cb, 
		void *param)
{
	unsigned int index;

	if (table == NULL)
		return -1;

	index = table->hashfunc(table->size, data);
	return dlist_modify(table->table[index], cmp, val, cb, param);
}

inline int hash_move(hash_table_t *table_src, hash_table_t *table_dst, 
		void *data, ds_cmpfunc_t cmp, void *val)
{
	unsigned int isrc = table_src->hashfunc(table_src->size, data);
	unsigned int idst = table_dst->hashfunc(table_dst->size, data);

	return dlist_move(&table_src->table[isrc], &table_dst->table[idst], 
		cmp, val);
}

inline void hash_for_each(hash_table_t *table, ds_callback_t cb, void *param)
{
	int i;

	if (table == NULL)
		return;
	
	for (i = 0; i < table->size; i++) {
		//printf("%02d: ", i);
		dlist_for_each(table->table[i], cb, param);
		//printf("\n");
	}
}

inline void hash_for_each_del(hash_table_t *table, ds_callback_t cb, 
		void *param)
{
	int i;

	if (table == NULL)
		return;
	
	for (i = 0; i < table->size; i++)
		dlist_for_each_del(&table->table[i], cb, param);
}

inline void hash_sort(hash_table_t *table, int opt)
{
}

void hash_clear(hash_table_t *table, ds_callback_t cb, void *param)
{
	int i;

	if (table == NULL)
		return;
	
	for (i = 0; i < table->size; i++)
		dlist_clear(&table->table[i], cb, param);
}

void hash_destory(hash_table_t *table)
{
	if (table) {
		free(table->table);
		free(table);
	}
}
