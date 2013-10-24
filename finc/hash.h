#ifndef _HASH_H_
#define _HASH_H_

#include "ds_comm.h"

/* hash table */
typedef struct hash_table_t hash_table_t;

/* hash function typedef */
typedef unsigned int (*hash_func_t)(const int table_size, void *data);

/* default hash functions */
inline unsigned int hash_func_val(const int table_size, void *data);
inline unsigned int hash_func_str(const int table_size, void *data);

/* initialize a new table */
hash_table_t *hash_init(int table_size, hash_func_t hashfunc);

/* add a new item into table, return 0 if success or -1 if failed */
inline int hash_add(hash_table_t *table, void *data);

/* delete a item from table */
inline int hash_del(hash_table_t *table, void *data, ds_cmpfunc_t cmp, 
		void *val, ds_callback_t cb, void *param);

/* get a node from table */
inline int hash_entry(hash_table_t *table, void *data, ds_cmpfunc_t cmp, 
		void *val, void **item);

/*  */
inline int hash_modify(hash_table_t *table, void *data, 
		ds_cmpfunc_t cmp, void *val, ds_callback_t cb, 
		void *param);

/* move a node from table_src to table_dst. return 0 if success, 
 * or -1 if failed. */
inline int hash_move(hash_table_t *table_src, hash_table_t *table_dst, 
		void *data, ds_cmpfunc_t cmp, void *val);

/*  */
inline void hash_for_each(hash_table_t *table, ds_callback_t cb, void *param);

inline void hash_for_each_del(hash_table_t *table, ds_callback_t cb, 
		void *param);

/*  */
inline void hash_sort(hash_table_t *table, int opt);

/*  */
void hash_clear(hash_table_t *table, ds_callback_t cb, void *param);

/*  */
void hash_destory(hash_table_t *table);

#endif	/* _HASH_H_ */
