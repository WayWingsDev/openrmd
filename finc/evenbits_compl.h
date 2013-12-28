#ifndef _EVENBITS_COMPL_H_
#define _EVENBITS_COMPL_H_

/**
 * @brief encrypt/de-encrypt a string (even bitwise complement).
 * 
 * @param *buff the string want to to encrypt/de-encrypt. when success, 
 * 		hold the result string.
 * @param buff_size buffer size.
 * 
 * @return zero if success or -1 if error.
 */
int evenbits_compl(char *buff, int buff_size);

#endif	/* _EVENBITS_COMPL_H_ */
