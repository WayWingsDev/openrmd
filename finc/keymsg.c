#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "keymsg.h"

static int kbd_fd = -1;
static int leftshift_down = 0;
static int rightshift_down = 0;

static void *keymsg_thread(void *arg)
{
	struct input_event evt;
	int n;

	while (1) {
		n = read(kbd_fd, &evt, sizeof(evt));
		if (n <= 0)
			break;
		if (n != sizeof(evt))
			continue;

		if (evt.type == EV_KEY) {
			if (evt.code == KEY_LEFTSHIFT)
				leftshift_down = evt.value ? 1 : 0;
			else if (evt.code == KEY_RIGHTSHIFT)
				rightshift_down = evt.value ? 1 : 0;

			((keymsg_callback_t)arg)(evt.code, evt.value, 
				leftshift_down | rightshift_down);
		}
	}

	return NULL;
}

int keymsg_init(char *kbd_event_interface, keymsg_callback_t cbk)
{
	pthread_t tid;

	kbd_fd = open(kbd_event_interface, O_RDONLY);
	if (kbd_fd <= 0)
		return -1;

	if (pthread_create(&tid, NULL, keymsg_thread, (void *)cbk) != 0) {
		close(kbd_fd);
		return -1;
	}
	pthread_detach(tid);
	return 0;
}

int keymsg_destory()
{
	close(kbd_fd);
	return 0;
}
