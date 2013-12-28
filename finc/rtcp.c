/*
 * NOTE on RTCP implementation:
 * - there is a single sender (us), no conferencing here! => n = sender = 1,
 * - as such we need not bother to include Receiver Reports,
 * - in unicast case, there is a single receiver => members = 1 + 1 = 2,
 *   and obviously n > 25% of members,
 * - in multicast case, we do not want to maintain the number of receivers
 *   and we assume it is big (i.e. than 3) because that's what broadcasting is
 *   all about,
 * - it is assumed we_sent = true (could be wrong), since we are THE sender,
 * - we always send SR + SDES, while running,
 * - FIXME: we do not implement separate rate limiting for SDES,
 * - we do not implement any profile-specific extensions for the time being.
 */

#include "syshdr.h"
#include "rtcp.h"
#include "udpsock.h"

#define NI_MAXNUMERICHOST 64
#define PACKAGE_STRING	"jasper 1.900.1"  /* full name and version of package */

/* Helper for GCC version checks */
#ifdef __GNUC__
# define VLC_GCC_VERSION(maj,min) \
	((__GNUC__ > (maj)) || (__GNUC__ == (maj) && __GNUC_MINOR__ >= (min)))
#else
# define VLC_GCC_VERSION(maj,min) (0)
#endif

#define hton16(i) bswap16(i)
#define hton32(i) bswap32(i)
#define hton64(i) bswap64(i)

#define GetDWBE(p) U32_AT(p)
#define ntoh32(i) hton32(i)

/* Byte swap (16 bits) */
static inline uint16_t bswap16(uint16_t x)
{
	return (x << 8) | (x >> 8);
}

/* Byte swap (32 bits) */
static inline uint32_t bswap32(uint32_t x)
{
#if VLC_GCC_VERSION(4,3)
	return __builtin_bswap32(x);
#else
	return ((x & 0x000000FF) << 24)
		| ((x & 0x0000FF00) <<  8)
		| ((x & 0x00FF0000) >>  8)
		| ((x & 0xFF000000) >> 24);
#endif
}

/* Byte swap (64 bits) */
static inline uint64_t bswap64(uint64_t x)
{
#if VLC_GCC_VERSION(4,3)
	return __builtin_bswap64(x);
#elif !defined (__cplusplus)
	return ((x & 0x00000000000000FF) << 56)
		| ((x & 0x000000000000FF00) << 40)
		| ((x & 0x0000000000FF0000) << 24)
		| ((x & 0x00000000FF000000) <<  8)
		| ((x & 0x000000FF00000000LLU) >>  8)
		| ((x & 0x0000FF0000000000LLU) >> 24)
		| ((x & 0x00FF000000000000LLU) >> 40)
		| ((x & 0xFF00000000000000LLU) >> 56);
#else
	return ((x & 0x00000000000000FFLLU) << 56)
		| ((x & 0x000000000000FF00LLU) << 40)
		| ((x & 0x0000000000FF0000LLU) << 24)
		| ((x & 0x00000000FF000000LLU) <<  8)
		| ((x & 0x000000FF00000000LLU) >>  8)
		| ((x & 0x0000FF0000000000LLU) >> 24)
		| ((x & 0x00FF000000000000LLU) >> 40)
		| ((x & 0xFF00000000000000LLU) >> 56);
#endif
}

/* Reads 32 bits in network byte order */
static inline uint32_t U32_AT(const void *p)
{
	uint32_t x;

	memcpy(&x, p, sizeof (x));
	return ntoh32(x);
}

/* Writes 16 bits in network byte order */
static inline void SetWBE(void *p, uint16_t w)
{
	w = hton16(w);
	memcpy(p, &w, sizeof (w));
}

/* Writes 64 bits in network byte order */
static inline void SetQWBE(void *p, uint64_t qw)
{
	qw = hton64(qw);
	memcpy(p, &qw, sizeof (qw));
}

/* Writes 32 bits in network byte order */
static inline void SetDWBE(void *p, uint32_t dw)
{
	dw = hton32(dw);
	memcpy(p, &dw, sizeof(dw));
}

/**
 * @return NTP 64-bits timestamp in host byte order.
 */
static inline uint64_t NTPtime64()
{
#if (_POSIX_TIMERS > 0)
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
#else
	struct timeval  tv;
	struct {
		uint32_t tv_sec;
		uint32_t tv_nsec;
	} ts;

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec;
	ts.tv_nsec = tv.tv_usec * 1000;
#endif

	/* Convert nanoseconds to 32-bits fraction (232 picosecond units) */
	uint64_t t = (uint64_t)(ts.tv_nsec) << 32;
	t /= 1000000000;

	/* There is 70 years (incl. 17 leap ones) offset to the Unix Epoch.
	 * No leap seconds during that period since they were not invented yet.
	 */
	t |= ((70LL * 365 + 17) * 24 * 60 * 60 + ts.tv_sec) << 32;
	return t;
}

rtcp_t *rtcp_open(int rtcp_sock, struct sockaddr_in rtcp_addr, 
		int report_type)
{
	rtcp_t *rtcp;
	uint8_t *ptr;
	char src[NI_MAXNUMERICHOST] = "0.0.0.0:00000";

	rtcp = malloc(sizeof (*rtcp));
	if (rtcp == NULL)
		return NULL;

	rtcp->sock = rtcp_sock;
	rtcp->addr = rtcp_addr;
	rtcp->bytes = rtcp->packets = rtcp->counter = 0;

	ptr = (uint8_t *)strchr(src, '%');
	if (ptr != NULL)
		*ptr = '\0';	/* remove scope ID frop IPv6 addresses */

	/* Sender/Receiver report */
	ptr = rtcp->payload;
	ptr[0] = 2 << 6; 	/* V = 2, P = RC = 0 */
	ptr[1] = report_type;	/* payload type */
	SetWBE(ptr + 2, 6); 	/* length = 6 (7 double words) */
	memset(ptr + 4, 0, 4); 	/* SSRC unknown yet */
	SetQWBE(ptr + 8, NTPtime64());
	memset(ptr + 16, 0, 12);/* timestamp and counters */
	ptr += 28;

	/* Source description */
	uint8_t *sdes = ptr;
	ptr[0] = (2 << 6) | 1; 	/* V = 2, P = 0, SC = 1 */
	ptr[1] = 202; 		/* payload type: Source Description */
	uint8_t *lenptr = ptr + 2;
	memset(ptr + 4, 0, 4); 	/* SSRC unknown yet */
	ptr += 8;

	ptr[0] = 1; 		/* CNAME - mandatory */
	ptr[1] = strlen(src);
	memcpy(ptr + 2, src, ptr[1]);
	ptr += ptr[1] + 2;

	static const char tool[] = PACKAGE_STRING;
	ptr[0] = 6; 		/* TOOL */
	ptr[1] = (sizeof(tool) > 256) ? 255 : (sizeof(tool) - 1);
	memcpy(ptr + 2, tool, ptr[1]);
	ptr += ptr[1] + 2;

	while ((ptr - sdes) & 3)/* 32-bits padding */
		*ptr++ = 0;
	SetWBE(lenptr, (ptr - sdes - 1) >> 2);

	rtcp->length = ptr - rtcp->payload;
	return rtcp;
}

void rtcp_close(rtcp_t *rtcp)
{
	if (rtcp == NULL)
		return;

	uint8_t *ptr = rtcp->payload;
	uint64_t now64 = NTPtime64();
	SetQWBE(ptr + 8, now64); 	/* Update the Sender Report timestamp */

	/* Bye */
	ptr += rtcp->length;
	ptr[0] = (2 << 6) | 1; 		/* V = 2, P = 0, SC = 1 */
	ptr[1] = 203; 			/* payload type: Bye */
	SetWBE(ptr + 2, 1);

	/* Copy SSRC from Sender Report */
	memcpy(ptr + 4, rtcp->payload + 4, 4);
	rtcp->length += 8;

	/* We are THE sender, so we are more important than anybody else, so
	 * we can afford not to check bandwidth constraints here. */
	send(rtcp->sock, rtcp->payload, rtcp->length, 0);
	free(rtcp);
}

void rtcp_send(rtcp_t *rtcp, char *rtp_buff, int rtp_buff_len)
{
	if (rtcp == NULL)
		return;
	if (rtp_buff_len < 12)		/* RTP packet too short */
		return;

	uint8_t *ptr;
	uint32_t last;
	uint64_t now64;
	int bytes;

	/* Updates statistics */
	rtcp->packets++;
	rtcp->bytes += rtp_buff_len;
	rtcp->counter += rtp_buff_len;

	ptr = rtcp->payload;
	last = GetDWBE(ptr + 8); 	/* last RTCP SR send time */
	now64 = NTPtime64();

	memcpy(ptr + 4, rtp_buff + 8, 4); 	/* SR SSRC */
	SetQWBE(ptr + 8, now64);
	memcpy(ptr + 16, rtp_buff + 4, 4); 	/* RTP timestamp */
	SetDWBE(ptr + 20, rtcp->packets);
	SetDWBE(ptr + 24, rtcp->bytes);
	memcpy(ptr + 28 + 4, rtp_buff + 8, 4); 	/* SDES SSRC */

	bytes = sendto(rtcp->sock, ptr, rtcp->length, 0,
			(const struct sockaddr *)&rtcp->addr,
			(socklen_t)sizeof(struct sockaddr_in));
	if (bytes == rtcp->length)
		rtcp->counter = 0;
}
