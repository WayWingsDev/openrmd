include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/yaan
finc_obj = 

$(libname).so: $(frame_realplay) lib_special.h lib_special.c $(finc_obj)
	g++ $(CFLAGS) -fpic -shared -o $@ $^ -lpthread $(LNKFLAGS) -lynnet

clean:
	rm -f $(libname).so tags
