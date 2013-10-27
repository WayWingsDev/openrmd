include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/hik/include
finc_obj = $(addprefix $(finc)/, single_login.o tcpconn.o dlist.o \
	base64_encode.o)

$(libname).so: $(frame_realplay) lib_special.h lib_special.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ \
<<<<<<< HEAD
		-lpthread $(LNKFLAGS) -lhcnetsdk -lhpr -lStreamTransClient -lSystemTransform
=======
		-lpthread $(LNKFLAGS) -lhcnetsdk -lhpr
>>>>>>> 64d671fb5303708a1b14f1d09bf9a4c3f9b79e1c

clean:
	rm -f $(libname).so tags
