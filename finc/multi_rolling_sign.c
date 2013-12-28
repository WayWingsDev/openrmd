#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multi_rolling_sign.h"

static char sign[] = "|/-\\";

struct multi_rolling_t {
	int columns;
	int *pos;
};

multi_rolling_t *multi_rolling_init(const int columns)
{
	multi_rolling_t *mr = calloc(sizeof(multi_rolling_t), 1);
	if (mr == NULL)
		return NULL;
	mr->columns = columns;
	mr->pos = calloc(sizeof(int), columns);
	if (mr->pos == NULL) {
		free(mr);
		return NULL;
	}
	return mr;
}

void multi_rolling_sign(multi_rolling_t *mr, int index)
{
	if (mr == NULL || index < 0 || index > mr->columns)
		return;

	mr->pos[index] = (mr->pos[index] + 1) % (sizeof(sign) - 1);

	int i;
	for (i = 0; i < mr->columns; i++)
		printf("%c", sign[mr->pos[i]]);
	printf("\r");
	fflush(stdout);
}
