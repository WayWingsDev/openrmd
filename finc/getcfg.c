#include "syshdr.h"
#include "getcfg.h"

int getcfg(char *file, char *key, void *val, getcfg_val_t t)
{
	FILE *fp;
	char line[PATH_MAX], pkey[PATH_MAX], pval[PATH_MAX];

	if ((fp = fopen(file, "r")) == NULL)
		return -1;

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (sscanf(line, "%[^=]=%s", pkey, pval) != 2 ||
				strcmp(pkey, key) != 0)
			continue;

		if (t == GETCFG_INT32)
			*(int *)val = atol(pval);
		else if (t == GETCFG_UINT32)
			*(uint32_t *)val = strtoul(pval, NULL, 0);
		else if (t == GETCFG_UINT64)
			*(uint64_t *)val = strtoull(pval, NULL, 0);
		else
			snprintf(val, strlen(pval) + 1, pval);

		fclose(fp);
		return 0;
	}

	fclose(fp);
	return -1;
}
