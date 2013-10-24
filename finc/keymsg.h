#ifndef _KEYMSG_H_
#define _KEYMSG_H_

#include <linux/input.h>

/* down: 0-up 1-down
 * shift: 1-shift down
 */
typedef void (*keymsg_callback_t)(int keycode, int down, int shift);

/*
cat /proc/bus/input/devices
---------------------------------------------------------------------
I: Bus=0011 Vendor=0001 Product=0001 Version=ab54
N: Name="AT Translated Set 2 keyboard"
P: Phys=isa0060/serio0/input0
S: Sysfs=/devices/platform/i8042/serio0/input/input4
U: Uniq=
H: Handlers=kbd event4 
B: EV=120013
B: KEY=4 2000000 3803078 f800d001 feffffdf ffefffff ffffffff fffffffe
B: MSC=10
B: LED=7
---------------------------------------------------------------------
So, the keyboard event device is "/dev/input/event4"
*/
int keymsg_init(char *kbd_event_interface, keymsg_callback_t cbk);

int keymsg_destory();

#endif	/* _KEYMSG_H_ */
