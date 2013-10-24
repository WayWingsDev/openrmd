#include "proc_runtime.h"

static atomic_t runtime;
static int started = 0;

static void *runtime_thread(void *arg)
{
	int n;

	atomic_set(&runtime, 0);

	for (;;) {
		atomic_inc(&runtime);
		n = atomic_read(&runtime);
		if (n >= ((1<<24) - 1))
			atomic_set(&runtime, 0);
		sleep(1);
	}

	return NULL;
}

int proc_runtime_init()
{
	pthread_t tid;

	if (started == 1)	/* one process one runtime thread */
		return 0;

	if (pthread_create(&tid, NULL, runtime_thread, NULL) != 0)
		return -1;
	pthread_detach(tid);
	started = 1;
	return 0;
}

time_t proc_runtime_get()
{
	return atomic_read(&runtime);
}
