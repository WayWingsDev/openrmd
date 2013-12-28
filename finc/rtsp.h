#ifndef _RTSP_H_
#define _RTSP_H_

/* rfc2326 */

#define RTSP_AGENT	"librtsp v0.9"	/* rtsp agent infor */
#define RTSP_VER	"RTSP/1.0"	/* rtsp version */
#define RTSP_PORT	554		/* default RTSP listen port */
#define RTSP_CMD_BUFF	(1024 * 4)	/* rtsp command buffer size */
#define RTSP_HDR_LEN	24		/* hdr field definitions's length */
#define RTSP_HDRCON_LEN 256		/* hdr field content length */
#define RTSP_METHOD_LEN 16		/* rtsp method length */
#define RTSP_URL_LEN	256		/* url length */
#define RTSP_CRLF	"\r\n"		/* line flag */
#define RTSP_CRLF_LEN	\
	strlen(RTSP_CRLF)
#define RTSP_PREFIX	"rtsp://"	/* rtsp request header prefix */
#define RTSP_PREFIX_LEN	\
	(strlen(RTSP_PREFIX))
#define RTSP_SPS_FIX	"sprop-parameter-sets="
#define RTSP_SPS_MAX	256		/* max length of sps */
#define RTSP_TIMEOUT	60		/* default RTCP package timeout(sec) */
#define RTSP_SID_LEN	128		/* session identifier max length */
#define RTSP_RTPPORT_MIN 10000		/* RTSP client min RTP port */
#define RTSP_RTPPORT_MAX 12000		/* RTSP client min RTP port */

/* rtsp method */
#define RTSP_OPTIONS	"OPTIONS"
#define RTSP_DESCRIBE	"DESCRIBE"
#define RTSP_ANNOUNCE	"ANNOUNCE"
#define RTSP_SETUP	"SETUP"
#define RTSP_PLAY	"PLAY"
#define RTSP_PAUSE	"PAUSE"
#define RTSP_TEARDOWN	"TEARDOWN"
#define RTSP_GET_PARAM	"GET_PARAMETER"
#define RTSP_SET_PARAM	"SET_PARAMETER"
#define RTSP_REDIRECT	"REDIRECT"
#define RTSP_RECORD	"RECORD"

/* rtsp header field index */
typedef enum {
	ACCEPT,
	ACCEPT_ENCODING,
	ACCEPT_LANGUAGE,
	ALLOW,
	AUTHORIZATION,
	BANDWIDTH,
	BLOCKSIZE,
	CACHE_CONTROL,
	CONFERENCE,
	CONNECTION,
	CONTENT_BASE,
	CONTENT_ENCODING,
	CONTENT_LANGUAGE,
	CONTENT_LENGTH,
	CONTENT_LOCATION,
	CONTENT_TYPE,
	CSEQ,
	DATE,
	EXPIRES,
	FROM,
	HOST,
	IF_MATCH,
	IF_MODIFIED_SINCE,
	LAST_MODIFIED,
	LOCATION,
	PROXY_AUTHENTICATE,
	PROXY_REQUIRE,
	PUBLIC,
	RANGE,
	REFERER,
	RETRY_AFTER,
	REQUIRE,
	RTP_INFO,
	SCALE,
	SPEED,
	SERVER,
	SESSION,
	TIMESTAMP,
	TRANSPORT,
	UNSUPPORTED,
	USER_AGENT,
	VARY,
	VIA,
	WWW_AUTHENTICATE
} rtsp_hdr_idx_t;

/* rtsp header field name */
static const char rtsp_hdr_fld[][RTSP_HDR_LEN] = {
	"Accept",
	"Accept-Encoding",
	"Accept-Language",
	"Allow",
	"Authorization",
	"Bandwidth",
	"Blocksize",
	"Cache-Control",
	"Conference",
	"Connection",
	"Content-Base",
	"Content-Encoding",
	"Content-Language",
	"Content-Length",
	"Content-Location",
	"Content-Type",
	"CSeq",
	"Date",
	"Expires",
	"From",
	"Host",
	"If-Match",
	"If-Modified-Since",
	"Last-Modified",
	"Location",
	"Proxy-Authenticate",
	"Proxy-Require",
	"Public",
	"Range",
	"Referer",
	"Retry-After",
	"Require",
	"RTP-Info",
	"Scale",
	"Speed",
	"Server",
	"Session",
	"Timestamp",
	"Transport",
	"Unsupported",
	"User-Agent",
	"Vary",
	"Via",
	"WWW-Authenticate"
};

/* header fields number */
#define RTSP_HDR_FLDS (sizeof(rtsp_hdr_fld) / RTSP_HDR_LEN)

/* rtsp status code */
/* 1xx: informational */
#define RTSP_SC_100		"100 Continue"

/* 2xx: successful */
#define RTSP_SC_200		"200 OK"
#define RTSP_SC_201		"201 Created"
#define RTSP_SC_250		"250 Low on Storage Space"

/* 3xx: redirection */
#define RTSP_SC_300		"300 Multiple Choices"
#define RTSP_SC_301		"301 Moved Permanently"
#define RTSP_SC_302		"302 Moved Temporarily"
#define RTSP_SC_303		"303 See Other"
#define RTSP_SC_304		"304 Not Modified"
#define RTSP_SC_395		"305 Use Proxy"

/* 4xx: client error */
#define RTSP_SC_400		"400 Bad Request"
#define RTSP_SC_401		"401 CODE Unauthorized"
#define RTSP_SC_402		"402 Payment Required"
#define RTSP_SC_403		"403 Forbidden"
#define RTSP_SC_404		"404 Not Found"
#define RTSP_SC_405		"405 Method Not Allowed"
#define RTSP_SC_406		"406 Not Acceptable"
#define RTSP_SC_407		"407 Proxy Authentication Required"
#define RTSP_SC_408		"408 Request Time-out"
#define RTSP_SC_410		"410 Gone"
#define RTSP_SC_411		"411 Length Required"
#define RTSP_SC_412		"412 Precondition Failed"
#define RTSP_SC_413		"413 Request Entity Too Large"
#define RTSP_SC_414		"414 Request-URI Too Large"
#define RTSP_SC_415		"415 Unsupported Media Type"
#define RTSP_SC_451		"451 Parameter Not Understood"
#define RTSP_SC_452		"452 Conference Not Found"
#define RTSP_SC_453		"453 Not Enough Bandwidth"
#define RTSP_SC_454		"454 Session Not Found"
#define RTSP_SC_455		"455 Method Not Valid in This State"
#define RTSP_SC_456		"456 Header Field Not Valid for Resource"
#define RTSP_SC_457		"457 Invalid Range"
#define RTSP_SC_458		"458 Parameter Is Read-Only"
#define RTSP_SC_459		"459 Aggregate operation not allowed"
#define RTSP_SC_460		"460 Only aggregate operation allowed"
#define RTSP_SC_461		"461 Unsupported transport"
#define RTSP_SC_462		"462 Destination unreachable"

/* 5xx: server error */
#define RTSP_SC_500		"500 Internal Server Error"
#define RTSP_SC_501		"501 Not Implemented"
#define RTSP_SC_502		"502 Bad Gateway"
#define RTSP_SC_503		"503 Service Unavailable"
#define RTSP_SC_504		"504 Gateway Time-out"
#define RTSP_SC_505		"505 RTSP Version not supported"
#define RTSP_SC_551		"551 Option not supported"

/* server and client states */
#define RTSP_STAT_INIT		2
#define RTSP_STAT_READY		4
#define RTSP_STAT_PLAYING	8
#define RTSP_STAT_RECORDING	16

/* transport mode */
#define RTSP_TRANS_AVP		"RTP/AVP"
#define RTSP_TRANS_UDP		"RTP/AVP/UDP"
#define RTSP_TRANS_TCP		"RTP/AVP/TCP"
#define rtsp_isudp(x) \
	((strcmp(x, RTSP_TRANS_AVP) & \
	  strcmp(x, RTSP_TRANS_UDP)) == 0 ? 1 : 0)
#define rtsp_istcp(x) \
	(strcmp(x, RTSP_TRANS_TCP) == 0 ? 1 : 0)

/* cast mode */
#define RTSP_CAST_UNI		"unicast"
#define RTSP_CAST_MULTI		"multicast"

#endif	/* _RTSP_H_ */
