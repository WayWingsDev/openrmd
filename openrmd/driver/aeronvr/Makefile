include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/aeronvr
CFLAGS	+= -DNONE_BLOCKING
finc_obj = 

$(libname).so: $(frame_rec) lib_special.h lib_special.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ $(LNKFLAGS) -laeronvr -lpthread

clean:
	rm -f $(libname).so tags
