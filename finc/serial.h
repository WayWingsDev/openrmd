#ifndef _SERIAL_H_
#define _SERIAL_H_

typedef void (*serial_data_callback_t)(unsigned long handle, 
		unsigned char *buff, int bytes, void *arg);

/* parity: 'N': none 'E': even 'O': odd 'S': space */
unsigned long serial_open(char *name, int baud_rate, int data_bits, int parity, 
		int stop_bits, serial_data_callback_t cbk, void *param);

int serial_send_data(unsigned long handle, unsigned char *buff, int bytes);

int serial_close(unsigned long handle);

#endif	/* _SERIAL_H_ */
