#ifndef _STR_TOLOWER_H_
#define _STR_TOLOWER_H_

/* Contert string to lowercase, for example, "Fangxm" to "fangxm" */
void str_tolower(char *str)
{
	while (*str) {
		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
		str++;
	}
}

#endif	/* _STR_TOLOWER_H_ */
