#ifndef _DP_INITERFACE_H_
#define _DP_INITERFACE_H_

struct dp_t {
	int lsn_port;

	int (*init)();
	unsigned long (*get_last_error)();
	int (*login)(char *ip, int port, char *user, char *pwd);
	int (*realplay)();
	int (*stop_realplay)();
	int (*ptzctl)();
	int (*search_file)();
	int (*playback)();
	int (*stop_playback)();
	int (*logout)();
	int (*cleanup)();
};

#endif /* _DP_INITERFACE_H_ */