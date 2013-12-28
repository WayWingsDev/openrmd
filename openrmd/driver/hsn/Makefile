include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/hsn
finc_obj = 

$(libname).so: $(frame_realplay) lib_special.h lib_special.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ \
		-lpthread $(LNKFLAGS) -lhsnnetsdk

clean:
	rm -f $(libname).so tags
