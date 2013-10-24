include ../Makefile.comm

finc_obj = $(addprefix $(finc)/, tcpconn.o)

libspecialipc.so: specialipc.h specialipc.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread

clean:
	rm -f libspecialipc.so tags
