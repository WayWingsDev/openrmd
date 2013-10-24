include ../Makefile.comm

$(libname).so: $(frame_realplay) lib_special.h lib_special.c
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread $(LNKFLAGS) -lrtsp

clean:
	rm -f $(libname).so tags
