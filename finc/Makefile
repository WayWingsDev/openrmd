CC	= gcc
#CC	= arm-linux-gcc
CFLAGS	= -Wall -O2
CFLAGS	+= -g

arch_x64= n
ifeq ($(arch_x64), y)
	CFLAGS += -fpic
endif

obj	= $(patsubst %.c,%.o,$(wildcard *.c))
so	= librtsp.so librtp.so sipso

default: $(obj) $(so) tags
all: default tst

$(obj): %.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

librtsp_obj = eplsvr.o tcplsn.o freads.o recvn.o tcpconn.o getrname.o \
	getsvrip.o getcliip.o readbuf.o base64_decode.o udplsn.o \
	strnstr.o udpsock.o set_keepalive.o rtp.o rtcp.o set_recv_timeout.o \
	set_nonblock.o
librtsp.so: rtsp.h rtspsvr.c rtspcli.c $(librtsp_obj) hash.o dlist.o
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -lpthread -lrt

librtp_obj = rtp.o
librtp.so: $(librtp_obj)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^

tags:
	@ctags *

tst:
	@cd test; make; cd ..;

sipso:
	@cd sip; make; cd ..;

.PHONY: clean
clean:
	rm -f $(obj) tags $(librtsp_obj) $(librtp_obj) $(so)

cleanall: clean
	@cd test; make clean; cd ..;
	@cd sip; make clean; cd ..;
