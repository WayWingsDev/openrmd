CC	= gcc
CFLAGS	= -Wall -O2
CFLAGS	+= -g
SIPLIB	= `pkg-config --cflags --libs libpjproject`

libsipua.so: sipua.h sipua.c
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ $(SIPLIB)

test:
	@cd tst; make; cd ..;

clean:
	rm -f *.o libsipua.so

cleanall: clean
	@cd tst; make clean; cd ..;
