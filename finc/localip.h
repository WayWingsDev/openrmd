#ifndef _LOCALIP_H_
#define _LOCALIP_H_

/**
 * @brief get a appointed interface's ip address
 * 
 * @param *interface network interface name
 * @param *ip [out] ip address
 * @param ip_size the ip address buffer size
 * 
 * @return 0 if success or -1 if error.
 */
int localip(const char *interface, char *ip, const int ip_size);

#endif	/* _LOCALIP_H_ */
