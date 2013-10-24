include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/hik/include
finc_obj = $(addprefix $(finc)/, single_login.o tcpconn.o dlist.o \
	base64_encode.o)

$(libname).so: $(frame_realplay) lib_special.h lib_special.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ \
		-lpthread $(LNKFLAGS) -lhcnetsdk -lhpr -lStreamTransClient -lSystemTransform

clean:
	rm -f $(libname).so tags
