finc	= /programs/finc
access_src_dir = access
trans_src_dir = trans
thirdlib= /programs/thirdlib
driver	= driver
ora	= /usr/oracle_client

CC	= gcc
CFLAGS	= -Wall -O2 -I$(finc) -I$(CURDIR) \
	-Wl,-rpath,./lib -L./lib -lpthread -ldl
CFLAGS	+= -g

# Enable session mutex
CFLAGS += -DENABLE_SESS_MTX

finc_obj= $(addprefix $(finc)/, get_absolute_filename.o lookup_so.o getrpath.o \
	getrname.o getcfg.o evenbits_compl.o udpsock.o udplsn.o mkdir_r.o \
	localip.o readbuf.o dlist.o hash.o set_recv_timeout.o \
	proc_runtime.o)
rmd_obj	= rmd.o rmd_devmgr.o rmd_sessmgr.o rmd_data_callback.o rmd_event.o

# configure
# y: enable module
# n: disable module

#CONFIG = TAM
CONFIG = ZC
#CONFIG = ELEC
#CONFIG = CHAOYANG

ifeq ($(CONFIG), TAM)
	userlog	= y
	rtspsvr	= y
	sipuas	= y
	udpsvr	= y
	unix_domain_svr = y
	rec	= y
	ptz	= y

	CFLAGS += -DRMD_DUMMY_INVITE
endif

ifeq ($(CONFIG), ZC)
	userlog	= y
	rtspsvr	= y
	#sipuas	= y
	udpsvr	= y
	unix_domain_svr = y
	rec	= y
	ptz	= y

	CFLAGS += -DRMD_DUMMY_INVITE
endif

ifeq ($(CONFIG), ELEC)
	userlog	= y
	rtspsvr	= n
	sipuas	= y
	unix_domain_svr = y
	rec	= n
	ptz	= n

	CFLAGS += -DRMD_ELEC_CONVERT -I/usr/include/mysql -lmysqlclient
	rmd_obj += elec_conv.o
endif

ifeq ($(CONFIG), CHAOYANG)
	userlog	= y
	rtspsvr	= y
	sipuas	= y
	udpsvr	= n
	unix_domain_svr = n
	rec	= n
	ptz	= n

	CFLAGS += -DRMD_DYNAMIC_DEVICES -DRMD_SEND_APPLY_MSG
endif

ifeq ($(userlog), y)
	finc_obj += $(finc)/syslog.o
endif

ifeq ($(rtspsvr), y)
	finc_obj += $(addprefix $(finc)/, udplsn.o rtp.o)
	rmd_obj += $(access_src_dir)/rmd_rtspsvr.o \
	$(access_src_dir)/rmd_rtcpsvr.o
	CFLAGS += -DRMD_HAS_RTSPSVR -lrtsp -lrt
endif

ifeq ($(sipuas), y)
	rmd_obj += $(access_src_dir)/rmd_sipuas.o
	CFLAGS += -DRMD_HAS_SIPUAS -I$(finc)/sip -lsipua
endif

ifeq ($(udpsvr), y)
	finc_obj += $(addprefix $(finc)/, udplsn.o)
	rmd_obj += $(access_src_dir)/rmd_udpsvr.o
	CFLAGS += -DRMD_HAS_UDPSVR
endif

ifeq ($(unix_domain_svr), y)
	finc_obj += $(addprefix $(finc)/, uudpsock.o)
	rmd_obj += $(access_src_dir)/rmd_uds.o
	CFLAGS += -DRMD_HAS_UDS
endif

ifeq ($(rec), y)
	finc_obj += $(addprefix $(finc)/, single_login.o tcpconn.o)
	rmd_obj += rmd_rec.o
	CFLAGS += -DRMD_HAS_REC -lpthread -lrtp
endif

ifeq ($(ptz), y)
	rmd_obj += rmd_ptz.o
	CFLAGS += -DRMD_HAS_PTZ
endif

openrmd: $(finc_obj) $(rmd_obj) rmd_driver_interface.h
	$(CC) $(CFLAGS) -o $@ $^
	@echo 'Done.'

$(rmd_obj): %.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

all: openrmd drivers device_cfg_ora device_cfg_elec device_cfg_zc

drivers:
	@cd $(driver); make; cd ..;
	@echo 'Done.'

device_cfg_ora: device_cfg.c device_cfg_ora.c $(addprefix $(finc)/, getcfg.o \
	localip.o)
	gcc -Wall -I$(finc) -I$(ora)/include -o $@ $^ -L$(ora) -lclntsh

device_cfg_elec: device_cfg.c device_cfg_elec.c \
	$(addprefix $(finc)/, getcfg.o)
	gcc -Wall -I$(finc) -I/usr/include/mysql -o $@ $^ -lmysqlclient

device_cfg_zc: device_cfg.c device_cfg_zc.c \
	$(addprefix $(finc)/, getcfg.o localip.o)
	gcc -Wall -I$(finc) -I/usr/include/mysql -Wl,-rpath,./lib -L./lib \
		-o $@ $^ -lmysqlclient

stat_svr_alone: $(access_src_dir)/rmd_uds.h stat_svr_alone.c \
	$(addprefix $(finc)/, getcfg.o uudplsn.o mcast_join.o udpsock.o \
	udplsn.o hash.o dlist.o getrpath.o)
	gcc -Wall -I$(finc) -o $@ $^ -lpthread

.PHONY: clean
clean:
	rm -f $(rmd_obj) openrmd device_cfg_ora device_cfg_elec device_cfg_zc stat_svr_alone

cleanall: clean
	@cd $(driver); make clean; cd ..;
	rm -f tags
