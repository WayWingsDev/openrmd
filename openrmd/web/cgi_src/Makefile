finc	= /programs/finc
CC	= gcc
CFLAGS	= -Wall -O2 -I$(finc)

all: process_state.cgi device_config.cgi

process_state.cgi: process_state.c $(addprefix $(finc)/, procnum.o)
	$(CC) $(CFLAGS) -o $@ $^

device_config.cgi: device_config.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f process_state.cgi device_config.cgi
