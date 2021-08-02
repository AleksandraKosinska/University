#include "traceroute.h"


int receive(int sockfd, int ttl, int pid, struct sockaddr_in addr, struct reply *reply_table){

    socklen_t addr_len = sizeof(addr);
    fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int received = 0;
    while(received < 3){
        int ready = select(sockfd+1, &descriptors, NULL, NULL, &tv);
        if(ready < 0){
            fprintf(stderr, "select error: %s\n", strerror(errno));
            return -1;
        }
        else if(ready == 0){
            return received;
        }
        else if(ready > 0){
            u_int8_t buffer[IP_MAXPACKET];
            ssize_t packet_len = recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&addr, &addr_len);
            if (packet_len < 0) {
                fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
                return -1;
            }
            struct ip *ip_header = (struct ip*)buffer;
            u_int8_t *icmp_packet = buffer + 4 * ip_header->ip_hl;
            struct icmp *icmp_header = (struct icmp*) icmp_packet;
            if(icmp_header->icmp_type == ICMP_TIME_EXCEEDED){
                struct ip *ip_header_te = (struct ip*)(icmp_packet + 8);
                u_int8_t *icmp_packet_te = icmp_packet + 8 + 4 * ip_header_te->ip_hl;
                struct icmp *icmp_header_te = (struct icmp*) icmp_packet_te;
                if(icmp_header_te->icmp_hun.ih_idseq.icd_id == pid && icmp_header_te->icmp_hun.ih_idseq.icd_seq == ttl){
                    (reply_table + received)->addr = ip_header->ip_src;
                    (reply_table + received)->time = 1000000 - tv.tv_usec;
                    received++;
                }
            }
            else if(icmp_header->icmp_type == ICMP_ECHOREPLY){
                if(icmp_header->icmp_hun.ih_idseq.icd_id == pid && icmp_header->icmp_hun.ih_idseq.icd_seq == ttl){
                    (reply_table + received)->addr = ip_header->ip_src;
                    (reply_table + received)->time = 1000000 - tv.tv_usec;
                    received++;
                }
            }
        }
    }
    return received;
}