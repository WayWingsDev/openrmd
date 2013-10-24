#ifndef _RTCP_H
#define _RTCP_H

#define RTCP_SENDER_REPORT	200
#define RTCP_RECEIVER_REPORT	201
#define RTCP_RECV_TIMEOUT	5
#define RTCP_SEND_SLOT		15

typedef struct {
	size_t   length;  	/* RTCP packet length */
	uint8_t  payload[28 + 8 + (2 * 257) + 8];
	int      sock;  	/* RTCP socket handler */
	struct   sockaddr_in addr;

	uint32_t packets; 	/* RTP packets sent */
	uint32_t bytes;   	/* RTP bytes sent */
	unsigned counter; 	/* RTP packets sent since last RTCP packet */
} rtcp_t;

rtcp_t *rtcp_open(int rtcp_sock, struct sockaddr_in rtcp_addr, 
		int report_type);
void rtcp_send(rtcp_t *rtcp, char *rtp_buff, int rtp_buff_len);
void rtcp_close(rtcp_t *rtcp);

#endif	/* _RTCP_H */
