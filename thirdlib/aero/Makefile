finc	= /programs/finc
CC	= gcc
CFLAGS	= -Wall -O2 -g -I$(finc)

finc_obj= $(addprefix $(finc)/, tcpconn.o recvn.o set_recv_timeout.o \
	set_send_timeout.o)

libaeronetsdk.so: aeronetsdk.h aeronetsdk.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread

all: libaeronetsdk.so tst

tst:
	@cd test; make; cd ..;

clean:
	rm -f libaeronetsdk.so

cleanall: clean
	@cd test; make clean; cd ..;
	rm -f tags
