CC	= gcc
#CC	= arm-linux-gcc
CFLAGS	= -Wall -O2
CFLAGS	+= -g
LNKFLAGS= -Wl,-rpath,. -L.

finc	= /programs/finc
CFLAGS	+= -I$(finc)

all: librmdsdk.so realplay_test ptz_test

so_obj= $(addprefix $(finc)/, syslog.o tcpconn.o getrname.o freads.o recvn.o \
	readbuf.o base64_decode.o udplsn.o udpsock.o rtp.o rtcp.o rtspcli.o \
	set_recv_timeout.o proc_runtime.o)

librmdsdk.so: $(so_obj) rmd_sdk.h rmd_sdk.c
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread -lrt

realplay_test: rmd_sdk.h realplay_test.c
	$(CC) $(CFLAGS) $(LNKFLAGS) -o $@ $^ -lrmdsdk

ptz_test: rmd_sdk.h ptz_test.c $(addprefix $(finc)/, keymsg.o)
	$(CC) $(CFLAGS) $(LNKFLAGS) -o $@ $^ -lrmdsdk

clean:
	rm -f librmdsdk.so realplay_test ptz_test tags
