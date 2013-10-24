#ifndef _MKDIR_R_H_
#define _MKDIR_R_H_

/**
 * @brief Create directories according to the path
 * 
 * @param *path directory path
 * @param mode 
 * 
 * @return return 0 if success or -1 if failed
 */
int mkdir_r(char *path, unsigned int mode);

#endif	/* _MKDIR_R_H_ */
