//#ifdef _MSC_VER
//#define _CRT_SECURE_NO_WARNINGS
//#endif
//
//#include <pcap.h>
//#include <stdio.h>
//#include <winsock2.h>
//#pragma comment(lib,"ws2_32.lib")
//#ifndef _WIN32
//#include <sys/socket.h>
//#include <netinet/in.h>
//#else
//
//#include <winsock.h>
//
//#endif
//
//#ifdef _WIN32
//
//#include <tchar.h>
//
//BOOL LoadNpcapDlls() {
//    _TCHAR npcap_dir[512];
//    UINT len;
//    len = GetSystemDirectory(npcap_dir, 480);
//    if (!len) {
//        fprintf(stderr, "Error in GetSystemDirectory: %x", GetLastError());
//        return FALSE;
//    }
//    _tcscat_s(npcap_dir, 512, _T("\\Npcap"));
//    if (SetDllDirectory(npcap_dir) == 0) {
//        fprintf(stderr, "Error in SetDllDirectory: %x", GetLastError());
//        return FALSE;
//    }
//    return TRUE;
//}
//
//#endif
//
//
//// Function prototypes
//void ifprint(pcap_if_t *d);
//
//char *iptos(u_long in);
//
//char *ip6tos(struct sockaddr *sockaddr, char *address, int addrlen);
//
//int main() {
//    pcap_if_t *alldevs;
//    pcap_if_t *d;
//    char errbuf[PCAP_ERRBUF_SIZE + 1];
//#ifdef _WIN32
//    /* Load Npcap and its functions. */
//    if (!LoadNpcapDlls()) {
//        fprintf(stderr, "Couldn't load Npcap\n");
//        exit(1);
//    }
//#endif
//    /* Retrieve the device list */
//    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
//        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
//        exit(1);
//    }
//    /* Scan the list printing every entry */
//    for (d = alldevs; d; d = d->next) {
//        ifprint(d);
//    }
//    /* Free the device list */
//    pcap_freealldevs(alldevs);
//    return 0;
//}
//
///* Print all the available information on the given interface */
//void ifprint(pcap_if_t *d) {
//    pcap_addr_t *a;
//    char ip6str[128];
//    /* Name */
//    printf("%s\n", d->name);
//    /* Description */
//    if (d->description)
//        printf("\tDescription: %s\n", d->description);
//    /* Loopback Address*/
//    printf("\tLoopback: %s\n", (d->flags & PCAP_IF_LOOPBACK) ? "yes" : "no");
//    /* IP addresses */
//    for (a = d->addresses; a; a = a->next) {
//        printf("\tAddress Family: #%d\n", a->addr->sa_family);
//        switch (a->addr->sa_family) {
//            case AF_INET:
//                printf("\tAddress Family Name: AF_INET\n");
//                if (a->addr)
//                    printf("\tAddress: %s\n", iptos(((struct sockaddr_in *) a->addr)->sin_addr.s_addr));
//                if (a->netmask)
//                    printf("\tNetmask: %s\n", iptos(((struct sockaddr_in *) a->netmask)->sin_addr.s_addr));
//                if (a->broadaddr)
//                    printf("\tBroadcast Address: %s\n", iptos(((struct sockaddr_in *) a->broadaddr)->sin_addr.s_addr));
//                if (a->dstaddr)
//                    printf("\tDestination Address: %s\n", iptos(((struct sockaddr_in *) a->dstaddr)->sin_addr.s_addr));
//                break;
//            case AF_INET6:
//                printf("\tAddress Family Name: AF_INET6\n");
//#ifndef __MINGW32__ /* Cygnus doesn't have IPv6 */
//                if (a->addr)
//                  printf("\tAddress: %s\n", ip6tos(a->addr, ip6str, sizeof(ip6str)));
//#endif
//                break;
//            default:
//                printf("\tAddress Family Name: Unknown\n");
//                break;
//        }
//    }
//    printf("\n");
//}
//
///* From tcptraceroute, convert a numeric IP address to a string */
//#define IPTOSBUFFERS    12
//
//char *iptos(u_long in) {
//    static char output[IPTOSBUFFERS][3 * 4 + 3 + 1];
//    static short which;
//    u_char *p;
//    p = (u_char *) &in;
//    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
//    sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
//    return output[which];
//}
//
//#ifndef __MINGW32__ /* Cygnus doesn't have IPv6 */
//char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen) {
//    socklen_t sockaddrlen;
//#ifdef _WIN32
//    sockaddrlen = sizeof(struct sockaddr_in6);
//#else
//    sockaddrlen = sizeof(struct sockaddr_storage);
//#endif
//    if(getnameinfo(sockaddr,
//        sockaddrlen,
//        address,
//        addrlen,
//        NULL,
//        0,
//        NI_NUMERICHOST) != 0) address = NULL;
//    return address;
//}
//#endif /* __MINGW32__ */
//
