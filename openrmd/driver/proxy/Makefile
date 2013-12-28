finc	= /programs/finc
CC	= gcc
CFLAGS	= -Wall -O2 -I$(finc)
CFLAGS	+= -g

all: jxj_proxy

finc_obj= $(addprefix $(finc)/, tcplsn.o set_keepalive.o)

jxj_proxy: dp.o dp_cmd.o $(finc_obj) jxj_proxy.o
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -f *.o jxj_proxy tags
