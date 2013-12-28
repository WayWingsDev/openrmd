include ../Makefile.comm

CFLAGS	+= -I$(specialipc)
finc_obj = $(addprefix $(finc)/, tcpconn.o)

$(libname).so: $(frame_realplay) lib_special.h lib_special.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ $(LNKFLAGS) -lpthread \
		-lspecialipc

clean:
	rm -f $(libname).so tags
