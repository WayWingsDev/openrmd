#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "listfile.h"

void listfile(char *path, char *suffix, listfile_callback_t fn, void *param)
{
	DIR *dp;
	struct dirent *dirp;
	struct stat sb;
	char fullname[PATH_MAX];
	int suffix_len = strlen(suffix);
	int suffix_pos;

	dp = opendir(path);
	if (dp == NULL) {
		printf("open dir: %s error\n", path);
		return;
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0 ||
				strcmp(dirp->d_name, "..") == 0)
			continue;

		snprintf(fullname, sizeof(fullname), "%s/%s", 
				path, dirp->d_name);
		if (lstat(fullname, &sb) == -1)
			continue;
		if (S_ISDIR(sb.st_mode))
			listfile(fullname, suffix, fn, param);
		else {
			suffix_pos = strlen(dirp->d_name) - suffix_len;
			if (suffix_pos < 0)
				continue;
			if (strcmp(&dirp->d_name[suffix_pos], suffix) != 0)
				continue;

			fn(dirp->d_name, param);
		}
	}

	closedir(dp);
}
