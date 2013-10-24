include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/dahua/include
finc_obj = $(addprefix $(finc)/, single_login.o tcpconn.o dlist.o)

$(libname).so: $(frame_realplay) lib_special.h lib_special.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread $(LNKFLAGS) -ldhnetsdk -ldhdvr

clean:
	rm -f $(libname).so tags
