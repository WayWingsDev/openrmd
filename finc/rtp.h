#ifndef _RTP_H
#define _RTP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define RTP_VER		2	/* RTP version */
#define RTP_MTU		1420	/* max size of RTP packet's payload */

/* rtp payload type */
#define RTP_PT_H264	96
#define RTP_PT_MJPEG	26

/* RTP packet header */
typedef struct {
	uint8_t   cc	:4;	/* source count */
	uint8_t   ext	:1;	/* extension flag */
	uint8_t   pad	:1;	/* padding flag */
	uint8_t   ver	:2;	/* version */
	uint8_t   pt	:7;	/* payload type */
	uint8_t   mark  :1;	/* marker flag */

	uint16_t  seq;		/* sequence number */
	uint32_t  ts;	 	/* timestamp */
	uint32_t  ssrc;	 	/* synchronization source identifier */
} rtp_hdr_t;

/* RTP packet header fixed size */
#define RTP_HDR_FIX_SIZE 	(int)(sizeof(rtp_hdr_t))

/* RTP slice buffer size */
#define	RTP_SLICE_SIZE		(RTP_MTU + RTP_HDR_FIX_SIZE + 20)

#define RTP_PACKET_FUNC_PARAM	\
	char *left_buff, int left_buff_size, \
	int *left_bytes, char *in_buff, int in_bytes, \
	uint16_t *seq, uint32_t ssrc, \
	uint32_t *ts_curr, uint32_t ts_inc, \
	rtp_slice_callback_t cb, void *arg
typedef void (*rtp_slice_callback_t)(char *buff, int bytes, void *arg);
typedef int (*rtp_packetization_callback_t)(RTP_PACKET_FUNC_PARAM);

/*
 * rfc3984(H.264)
 * packetization H.264 data RTP payload format, hold left contents in left 
 * buffer. call the callback function to process the RTP packet.
 */
inline int rtp_packetization_h264(RTP_PACKET_FUNC_PARAM);

/* For nari */
inline int rtp_packetization_h264_simple(RTP_PACKET_FUNC_PARAM);

/* print RTP header */
inline void rtp_print_hdr(const char *buff);

/* get H.264 data from a rtp package.
 * Note: out_buff must be large than RTP_SLICE_SIZE
 */
inline int rtp_get_h264_data(const char *in_buff, const int in_bytes, 
		char *out_buff, const int out_buff_size);

unsigned long rtp_recv_start(int rtsp_sock, int queue_len,
		rtp_slice_callback_t cbk, void *param);

int rtp_recv_stop(unsigned long rtp_recv_handle);

#ifdef __cplusplus
}
#endif

#endif	/* _RTP_H */
