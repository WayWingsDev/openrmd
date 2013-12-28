include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/yaandvr
finc_obj = 

$(libname).so: $(frame_realplay) lib_special.h lib_special.c $(finc_obj) \
	$(thirdlib)/yaandvr/plus.o
	g++ $(CFLAGS) -fpic -shared -o $@ $^ -lpthread $(LNKFLAGS) -lyndvr

clean:
	rm -f $(libname).so tags
