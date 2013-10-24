#ifndef _DP_PROTOCOL_H_
#define _DP_PROTOCOL_H_

/* command */
#define REALPLAY		"realplay"
#define STOPREALPLAY		"stop_realplay"

#define CHANNEL_FMT		"plat=%s dev_type=%d dev_id=%d channel=%d"
#define CMD_REALPLAY_FMT	"cmd=%s " CHANNEL_FMT
#define CMD_STOPREALPLAY_FMT	"cmd=stop_realplay"
#define CMD_PTZ_FMT		"cmd=ptz " CHANNEL_FMT " code=%04X param1=%d" \
	                        " param2=%d param3=%d"
#define CMD_SEARCH_FMT		"cmd=search " CHANNEL_FMT " type=%d start=%d" \
	                        " end=%d"
#define CMD_PLAYBACK_BYTIME_FMT	"cmd=playback_by_time " CHANNEL_FMT \
	                        " start=%d end=%d"
#define CMD_PLAYBACK_BYNAME_FMT	"cmd=playback_by_name " CHANNEL_FMT " name=%s"

#endif	/* _DP_PROTOCOL_H_ */
