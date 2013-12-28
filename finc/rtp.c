#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "rtp.h"

#define PRINT_DBG_INFO	0

/* the NAL unit type octet */
typedef struct {
	uint8_t	TYPE:5;		/* nal_unit_type */
	uint8_t	NRI :2;		/* nal_ref_idc */
	uint8_t	F   :1;		/* forbidden_zero_bit */
} nalu_hdr_t;

typedef struct {
	int forbidden_bit;
	int nal_ref_idc;
	int nal_unit_type;
} nalu_t;

/* the fraggnentation unit(FU) indicator octet */
typedef struct {
	uint8_t	TYPE:5;
	uint8_t	NRI :2;
	uint8_t	F   :1;
} fu_indicator_t;

/* the fraggnentation unit(FU) header */
typedef struct {
	uint8_t	TYPE:5;
	uint8_t	R   :1;
	uint8_t	E   :1;
	uint8_t	S   :1;
} fu_hdr_t;

/* NAL unit type */
typedef enum {
	NAL_STAP_A = 24,
	NAL_STAP_B = 25,
	NAL_MTAP16 = 26,
	NAL_MTAP24 = 27,
	NAL_FU_A   = 28,
	NAL_FU_B   = 29
} nal_unit_type_t;

/* if the buffer equal 0x000001 then return 0, otherwise, return -1 */
static inline int rtp_nalu_flag1_h264(char *buff)
{
	if (buff[0] == 0x00 && buff[1] == 0x00 && buff[2] == 0x01)
		return 0;
	else
		return -1;
}

/* if the buffer equal 0x00000001 then return 0, otherwise, return -1 */
static inline int rtp_nalu_flag2_h264(char *buff)
{
	if (buff[0] == 0x00 && buff[1] == 0x00 && buff[2] == 0x00 && 
			buff[3] == 0x01)
		return 0;
	else
		return -1;
}

/* packetization a NALU to one or more slice */
static inline int rtp_packetization_slice_h264(char *payload, int payload_len, 
		uint16_t *seq, uint32_t ssrc, uint32_t *ts_curr, 
		uint32_t ts_inc, rtp_slice_callback_t cb, void *arg, 
		nalu_t *nalu)
{
	char buff[RTP_SLICE_SIZE];
	rtp_hdr_t *rtp_hdr = (rtp_hdr_t *)&buff[0];
	fu_indicator_t *fu_ind;
	fu_hdr_t *fu_hdr;
	int num, left, no, pos, bytes;

	rtp_hdr->ver = RTP_VER;
	rtp_hdr->pad = 0;
	rtp_hdr->ext = 0;
	rtp_hdr->pt = RTP_PT_H264;
	rtp_hdr->ssrc = htonl(ssrc);
	rtp_hdr->cc = 0; /* TODO */
	*ts_curr += ts_inc;
	rtp_hdr->ts = htonl(*ts_curr);

	if (payload_len <= RTP_MTU) {
		rtp_hdr->mark = 1;
		rtp_hdr->seq = htons((*seq)++);
		
#if PRINT_DBG_INFO
		printf("%17c [seq:%5d]", ' ', *seq);
		printf("\n");
#endif

		nalu_hdr_t *nalu_hdr = (nalu_hdr_t *)&buff[RTP_HDR_FIX_SIZE];
		nalu_hdr->TYPE = nalu->nal_unit_type;
		nalu_hdr->NRI = nalu->nal_ref_idc >> 5;
		nalu_hdr->F = nalu->forbidden_bit >> 7;

		memcpy(&buff[RTP_HDR_FIX_SIZE + 1], payload + 1, 
				payload_len - 1);
		cb(buff, RTP_HDR_FIX_SIZE + payload_len, arg);
	} else {
		num = payload_len / RTP_MTU;
		left = payload_len % RTP_MTU;
		if (left == 0) {
			num -= 1;
			left = RTP_MTU;
		}

		buff[RTP_HDR_FIX_SIZE] = payload[0]; 
		fu_ind = (fu_indicator_t *)&buff[RTP_HDR_FIX_SIZE];
		fu_ind->TYPE = NAL_FU_A;
		fu_ind->NRI = nalu->nal_ref_idc >> 5;
		fu_ind->F = nalu->forbidden_bit >> 7;

		fu_hdr = (fu_hdr_t *)&buff[RTP_HDR_FIX_SIZE + 1];
		fu_hdr->TYPE = nalu->nal_unit_type;

		for (no = 0; no <= num; no++) {
			if (no == 0) {		/* first slice */
				rtp_hdr->mark = 0;
				fu_hdr->S = 1;
				fu_hdr->E = 0;
				fu_hdr->R = 0;
				bytes = RTP_MTU;
			} else if (no == num) {	/* last slice */
				rtp_hdr->mark = 1;
				fu_hdr->S = 0;
				fu_hdr->E = 1;
				fu_hdr->R = 0;
				bytes = left - 1;
			} else {		/* middle slice */
				rtp_hdr->mark = 0;
				fu_hdr->S = 0;
				fu_hdr->E = 0;
				fu_hdr->R = 0;
				bytes = RTP_MTU;
			}

			rtp_hdr->seq = htons((*seq)++);
			pos = no * RTP_MTU;

#if PRINT_DBG_INFO
			printf("%17c [seq:%5d] [bytes:%4d]", ' ', *seq, bytes);
			printf("\n");
#endif

			memcpy(&buff[RTP_HDR_FIX_SIZE + 2], 
					pos + (payload + 1), bytes);
			cb(buff, RTP_HDR_FIX_SIZE + 2 + bytes, arg);
		}
	}

	return 0;
}

inline int rtp_packetization_h264(RTP_PACKET_FUNC_PARAM)
{
	int total_bytes = *left_bytes + in_bytes;
	int pre_pos, cur_pos, flag_size, payload_len;
	char buff[total_bytes];
	nalu_t nalu;

	if (*left_bytes > 0)
		memcpy(buff, left_buff, *left_bytes);
	memcpy(&buff[*left_bytes], in_buff, in_bytes);

	pre_pos = 0;
	flag_size = 0;

	for (cur_pos = 0; cur_pos < total_bytes - 3; cur_pos++) {
		if (rtp_nalu_flag1_h264(&buff[cur_pos]) == 0) {
			flag_size = 3;
		} else if (cur_pos + 4 >= total_bytes) {
			break;
		} else if (rtp_nalu_flag2_h264(&buff[cur_pos]) == 0) {
			flag_size = 4;
		} else {
			continue;
		}
		
		payload_len = cur_pos - pre_pos;

#if PRINT_DBG_INFO
		printf("payload_len:%4d ", payload_len);
		int i;
		for (i = 0; i < payload_len; i++)
			printf("%02X ", (unsigned char)buff[pre_pos + i]);
		printf("\n");
#endif

		if (payload_len > 0) {
			nalu.forbidden_bit = buff[pre_pos] & 0x80;
			nalu.nal_ref_idc = buff[pre_pos] & 0x60;
			nalu.nal_unit_type = buff[pre_pos] & 0x1f;

			rtp_packetization_slice_h264(&buff[pre_pos], 
					payload_len, seq, ssrc, ts_curr, 
					ts_inc, cb, arg, &nalu);
		}
		pre_pos = cur_pos += flag_size;
	}

	/* put left data into left buffer */
	*left_bytes = total_bytes - pre_pos;

	if (*left_bytes > left_buff_size) {
		*left_bytes = 0;
		return -1;
	} else {
		//printf("%p %d %d\n", left_buff, pre_pos, *left_bytes);
		memcpy(left_buff, &buff[pre_pos], *left_bytes);
		return 0;
	}
}

inline int rtp_packetization_h264_simple(RTP_PACKET_FUNC_PARAM)
{
	char slice[RTP_SLICE_SIZE];
	rtp_hdr_t *rtp_hdr = (rtp_hdr_t *)&slice[0];
	int num;
	int left;
	int i;
	int pos;
	int n;

	rtp_hdr->ver = RTP_VER;
	rtp_hdr->pad = 0;
	rtp_hdr->ext = 0;
	rtp_hdr->pt = RTP_PT_H264;
	rtp_hdr->ssrc = htonl(ssrc);
	rtp_hdr->cc = 0; /* TODO */
	*ts_curr += ts_inc;
	rtp_hdr->ts = htonl(*ts_curr);

	if (in_bytes <= RTP_MTU) {
		rtp_hdr->mark = 1;
		rtp_hdr->seq = htons((*seq)++);
		memcpy(&slice[RTP_HDR_FIX_SIZE], in_buff, in_bytes);
		cb(slice, RTP_HDR_FIX_SIZE + in_bytes, arg);
		return 0;
	}

	num = in_bytes / RTP_MTU;
	left = in_bytes % RTP_MTU;
	if (left == 0) {
		num -= 1;
		left = RTP_MTU;
	}

	for (i = 0; i <= num; i++) {
		if (i == 0) {		/* first slice */
			rtp_hdr->mark = 0;
			n = RTP_MTU;
		} else if (i == num) {	/* last slice */
			rtp_hdr->mark = 1;
			n = left;
		} else {		/* middle slice */
			rtp_hdr->mark = 0;
			n = RTP_MTU;
		}

		rtp_hdr->seq = htons((*seq)++);
		pos = i * RTP_MTU;

		memcpy(&slice[RTP_HDR_FIX_SIZE], in_buff + pos, n);
		cb(slice, RTP_HDR_FIX_SIZE + n, arg);
	}

	return 0;
}

inline void rtp_print_hdr(const char *buff)
{
	uint16_t flag;
	rtp_hdr_t hdr;

	flag = ntohs(*(uint16_t *)buff);

	/* convert value from network to host byte order */
	hdr.ver = (flag & 0xC000) >> 14;
	hdr.pad = (flag & 0x2000) >> 13;
	hdr.ext = (flag & 0x1000) >> 12;
	hdr.cc  = (flag & 0x0F00) >> 8;
	hdr.mark= (flag & 0x0080) >> 7;
	hdr.pt  = (flag & 0x007F);
	hdr.seq = ntohs(*(uint16_t *)&buff[2]);
	hdr.ts  = ntohl(*(uint32_t *)&buff[4]);
	hdr.ssrc = ntohl(*(uint32_t *)&buff[8]);

	printf("ver:%d pad:%d ext:%d cc:%d mark:%d pt:%3d seq:%5d ts:%6u " 
			" ssrc:0x%8X\n",
			hdr.ver, hdr.pad, hdr.ext, hdr.cc, hdr.mark, hdr.pt, 
			hdr.seq, hdr.ts, hdr.ssrc);
}

inline int rtp_get_h264_data(const char *in_buff, const int in_bytes, 
		char *out_buff, const int out_buff_size)
{
	if (in_bytes < RTP_HDR_FIX_SIZE + 1)
		return -1;

	const uint8_t sc[] = {0, 0, 1};
	const int sc_len = sizeof(sc);
	const char *in_pos = &in_buff[RTP_HDR_FIX_SIZE];
	int in_len = in_bytes - RTP_HDR_FIX_SIZE;

	/* get NAL type */
	uint8_t type = (uint8_t)in_pos[0] & 0x1F;	/* 00011111 */
	if (type >= 1 && type <= 23) {	/* single frame */
		if (sc_len + in_len > out_buff_size)
			return -1;
		memcpy(out_buff, sc, sc_len);
		memcpy(&out_buff[sc_len], in_pos, in_len);
		return (sc_len + in_len);
	} else if (type == NAL_FU_A) {
		if ((uint8_t)in_pos[1] >> 7 == 1) { /* start of a multi frame */
			if (sc_len + 1 + in_len - 2 > out_buff_size)
				return -1;
			memcpy(out_buff, sc, sc_len);
			out_buff[sc_len] = ((uint8_t)in_pos[0] & 0xE0) |
				((uint8_t)in_pos[1] & 0x1F);
			memcpy(&out_buff[sc_len + 1], &in_pos[2], in_len - 2);
			return (sc_len + 1 + in_len - 2);
		} else {
			if (in_len > out_buff_size)
				return -1;
			memcpy(out_buff, &in_pos[2], in_len - 2);
			return (in_len - 2);
		}
	} 

	return -1;	/* if "type == 0": error; other: un-supported */
}
