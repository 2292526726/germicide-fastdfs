#include "stringutil.h"
#include "getlocalip.h"

int get_local_ip(char *ips,char * notiprule)
{
        int fd, intrface;
        struct ifreq buf[INET_ADDRSTRLEN];
        struct ifconf ifc;
        char * ip;
        if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
        {
                ifc.ifc_len = sizeof(buf);
                ifc.ifc_buf = (caddr_t)buf;
                if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
                {
                        char temp[MAX_LENGTH];
                        memset(temp, 0, sizeof(temp));
                        intrface = ifc.ifc_len/sizeof(struct ifreq);
                        while (intrface-- > 0)
                        {
                                if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))
                                {
                                        ip=(inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));
                                        if(!(is_end_with(ip,notiprule))){
                                          strcat(temp, ip);
                                          strcat(temp, "|");
                                        }
                                }
                                
                        }
                        char * ipstemp= (char *)malloc((strlen(temp)-1)*sizeof(char));
                        memcpy(ipstemp,temp,(strlen(temp)-1));
                        strcat(ips,ipstemp);
                        free(ipstemp);
                }
        close(fd);
        return 0;
        }
        return -1;
}
