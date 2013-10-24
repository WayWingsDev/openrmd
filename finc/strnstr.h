#ifndef _STRNSTR_H
#define _STRNSTR_H

/*
 * Return pointer to first occurrence of string s2 in s1 (the first n bytes), 
 * or NULL if not present.
 */
char *strnstr(const char *s1, const char *s2, size_t n);

#endif /* _STRNSTR_H */
