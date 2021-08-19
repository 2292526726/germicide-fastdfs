#ifndef __GET_LOCALIP_H__
#define __GET_LOCALIP_H__

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

int get_local_ip(char *ips,char * notiprule);

#endif /* __GET_LOCALIP_H__ */