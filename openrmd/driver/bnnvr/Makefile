include ../Makefile.comm

CFLAGS	+= -I$(thirdlib)/brainaire/include
CFLAGS	+= -DNONE_BLOCKING
finc_obj = 

$(libname).so: $(frame_rec) lib_special.h lib_special.c $(finc_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ $(LNKFLAGS) \
		-lNVRCLIENTAPI -lpthread

clean:
	rm -f $(libname).so tags
