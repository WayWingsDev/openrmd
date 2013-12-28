CC	= gcc
CFLAGS	= -Wall -O2 -I.. -Wl,-rpath,. -L. -lsipua
CFLAGS	+= -g

all: uas uac

uas: uas.c
	$(CC) $(CFLAGS) -o $@ $^

uac: uac.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f uas uac
