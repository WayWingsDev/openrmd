include ../Makefile.comm

CFLAGS	+= -I$(specialipc)
finc_obj = $(addprefix $(finc)/, tcpconn.o recvn.o set_recv_timeout.o)

$(libname).so: $(frame_realplay) lib_special.h lib_special.c \
	lib_special_ptz.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ $(LNKFLAGS) -lpthread \
		-lspecialipc

clean:
	rm -f $(libname).so tags
