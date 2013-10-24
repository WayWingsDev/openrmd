#include "keydown.h"

int keydown()
{
	char c;
	struct termios new, stored;

 	tcgetattr(0, &stored);
	new = stored;
	new.c_lflag &= (~ICANON);
	new.c_cc[VTIME] = 0;

	tcgetattr(0, &stored);
	new.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new);

	c = getchar();

	tcsetattr(0, TCSANOW, &stored);

	return c;
}
