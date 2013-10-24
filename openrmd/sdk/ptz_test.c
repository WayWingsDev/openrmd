#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rmd_sdk.h"
#include "keymsg.h"

#define KBD_EVENT_INTERFACE	"/dev/input/event4"
#define SVR_PORT	5545
#define PLAT		"1001"

static int esc = 0;
static unsigned long handle = -1;
static int command, param1, param2, param3;

static void keymsg_callback(int keycode, int down, int shift)
{
	if (keycode == KEY_ESC)
		esc = 1;

	printf("\r");
	fflush(stdout);

	switch (keycode) {
		case 103:	/* up */
			command = down ? 0x0402 : 0x0401;
			break;
		case 108:	/* down */
			command = down ? 0x0404 : 0x0403;
			break;
		case 105:	/* left */
			command = down ? 0x0504 : 0x0503;
			break;
		case 106:	/* right */
			command = down ? 0x0502 : 0x0501;
			break;
		default:
			return;
	}

	param1 = 5;
	param2 = 5;
	param3 = 0;

	rmd_ptz_send(handle, command, param1, param2, param3);
}

int main(int argc, char **argv)
{
	if (argc != 5) {
		printf("Usage: %s <server ip> <dev type> <dev id> "
				"<channel id>\n", argv[0]);
		exit(1);
	}

	/* initialize sdk */
	if (rmd_sdk_init() != 0) {
		printf("rmd_sdk_init() failed\n");
		exit(1);
	}

	handle = rmd_ptz_start(argv[1], SVR_PORT, PLAT, atoi(argv[2]),
		atoi(argv[3]), atoi(argv[4]));
	if (handle == -1) {
		printf("rmd_ptz_start() failed\n");
		exit(1);
	}

	if (keymsg_init(KBD_EVENT_INTERFACE, keymsg_callback) != 0) {
		printf("keymsg_init() failed\n");
		exit(1);
	}

	while (esc == 0)
		sleep(1);
	keymsg_destory();

	rmd_ptz_stop(handle);

	/* cleanup sdk */
	rmd_sdk_cleanup();

	return 0;
}
