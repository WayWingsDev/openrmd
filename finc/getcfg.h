#ifndef _GETCFG_H_
#define _GETCFG_H_

/* value type */
typedef enum {
	GETCFG_INT32,	/* int */
	GETCFG_UINT32,	/* unsigned int */
	GETCFG_UINT64,	/* unsigned long long */
	GETCFG_STR	/* string */
} getcfg_val_t;

/**
 * @brief Get value from a config file.
 * 
 * @param *file Config file name.
 * @param *key Key field name.
 * @param *val [out] The value of key.
 * @param t The value's type.
 * 
 * @return 0 if success or -1 if error.
 */
int getcfg(char *file, char *key, void *val, getcfg_val_t t);

#endif	/* _GETCFG_H_ */
