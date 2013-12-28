#include "lookup_so.h"
#include "syshdr.h"
#include "getrpath.h"

char *lookup_so(char *path, char *prefix)
{
	DIR *dp;
	struct dirent *dirp;
	struct stat sb;
	char fullpath[PATH_MAX] = "", fullname[PATH_MAX] = "";

	if (path != NULL && path[0] == '/') {	/* absolute path */
		snprintf(fullpath, sizeof(fullpath), path);
	} else {
		if (getrpath(fullpath, sizeof(fullpath)) == -1)
			return NULL;
		snprintf(&fullpath[strlen(fullpath)], 
				sizeof(fullpath) - strlen(path), "/%s", path);
	}

	dp = opendir(fullpath);
	if (dp == NULL) {
		syslog(LOG_DEBUG, "opendir() error: %s", strerror(errno));
		return NULL;
	}

	char *p = NULL;
	int pos = 0;
	while ((dirp = readdir(dp)) != NULL) {
		snprintf(fullname, sizeof(fullname), "%s/%s", fullpath, 
				dirp->d_name);
		if (lstat(fullname, &sb) == -1)
			continue;

		if ((!S_ISREG(sb.st_mode) && !S_ISLNK(sb.st_mode)) || 
				sb.st_size == 0)
			continue;

		int len = strlen(prefix);
		int n = strlen(dirp->d_name);
		if (len == 0 ||
				(strncmp(dirp->d_name, prefix, len) == 0 &&
				 strncmp(&dirp->d_name[n - 3], ".so", 3) ==
				 0)) {
			size_t new = strlen(fullname) + 1;
			p = realloc(p, pos + new);
			memcpy(&p[pos], fullname, new - 1);
			pos += new;
			p[pos - 1] = '\n';
		}
	}
	closedir(dp);
	return p;
}
