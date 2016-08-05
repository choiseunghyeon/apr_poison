#ifndef _ARPLIB_H
#define _ARPLIB_H


#include <stdint.h>

#define ETHERTYPE_IP 0x0800
#define ETHERTYPE_ARP 0x0806

#define ARPOP_REQUEST 1
#define ARPOP_REPLY 2
#define MAC_ADDRESS 6
#define IP_ADDRESS 4
struct ether_header
{

    uint8_t ether_dhost[MAC_ADDRESS];
    uint8_t ether_shost[MAC_ADDRESS];
    uint16_t ether_type;
}
__attribute__((__packed__));

struct arphdr
{
    uint16_t ar_hrd;
     uint16_t ar_pro;
      uint8_t ar_hln;
       uint8_t ar_pln;
        uint16_t ar_op;
}
__attribute__((__packed__));

struct ether_arp
{
    struct arphdr ea_hdr;

    uint8_t arp_sha[MAC_ADDRESS];
    uint8_t arp_spa[IP_ADDRESS];
    uint8_t arp_tha[MAC_ADDRESS];
    uint8_t arp_tpa[IP_ADDRESS];
}
__attribute__((__packed__));

#define arp_hrd ea_hdr.ar_hrd
#define arp_pro ea_hdr.ar_pro
#define arp_hln ea_hdr.ar_hln
#define arp_pln ea_hdr.ar_pln
#define arp_op ea_hdr.ar_op

struct arp_packet
{
    struct ether_header ether_header;
    struct ether_arp ether_arp;
}
__attribute__((__packed__));


void make_ether_header(struct ether_header *ether_header,
        uint8_t *dest, uint8_t *source, uint16_t type);

void make_arp_header(struct ether_arp *ether_arp,
        uint8_t *sha, uint32_t spa,
        uint8_t *tha, uint32_t tpa, uint32_t op);

void strmac_to_buffer(const char *str, uint8_t *mac);


#endif // ARPLIB_H
