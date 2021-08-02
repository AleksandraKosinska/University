#include "traceroute.h"

int send_three_socks(int sockfd, int ttl, int pid, struct sockaddr_in addr){
    for(int i = 0; i < 3; i++){
        if(send_sock(sockfd, ttl, pid, addr) == -1){
            return -1;
        }
    }
    return 0;
}

int send_sock(int sockfd, int ttl, int pid, struct sockaddr_in addr){
    struct icmp header;
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_hun.ih_idseq.icd_id = pid;
    header.icmp_hun.ih_idseq.icd_seq = ttl;
    header.icmp_cksum = 0;
    header.icmp_cksum = compute_icmp_checksum((u_int16_t*)&header, sizeof(header));
    setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
    if(sendto(sockfd, &header, sizeof(header), 0, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        fprintf(stderr, "sendto error: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

u_int16_t compute_icmp_checksum (const void *buff, int length){
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}