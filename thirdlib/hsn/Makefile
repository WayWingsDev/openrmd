finc	= /programs/finc
CC	= gcc
CFLAGS	= -Wall -O2 -I$(finc)

finc_obj= $(addprefix $(finc)/, tcpconn.o recvn.o set_recv_timeout.o \
	set_send_timeout.o dlist.o)

libhsnnetsdk.so: hsnnetsdk.h hsnnetsdk.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread

all: libhsnnetsdk.so tst

tst:
	@cd test; make; cd ..;

clean:
	rm -f libhsnnetsdk.so

cleanall: clean
	@cd test; make clean; cd ..;
