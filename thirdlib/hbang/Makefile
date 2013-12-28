finc	= /programs/finc
CC	= gcc
CFLAGS	= -Wall -O2 -I$(finc)

finc_obj= $(addprefix $(finc)/, tcpconn.o recvn.o dlist.o set_recv_timeout.o \
	set_send_timeout.o split_day.o stack.o vector.o read_flag.o \
	search_flag.o)

libhbnetsdk.so: hbnetsdk.h hbnetsdk.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread -lssl

all: libhbnetsdk.so tst

tst:
	@cd test; make; cd ..;

clean:
	rm -f libhbnetsdk.so

cleanall: clean
	@cd test; make clean; cd ..;
