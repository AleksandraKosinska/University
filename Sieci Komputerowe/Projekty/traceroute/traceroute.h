#ifndef traceroute_h
#define traceroute_h

#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <assert.h>

#define ECHO_PORT 7

struct reply{
    struct in_addr addr;
    int time;
};

int traceroute(int sockfd, struct sockaddr_in *addr, char *sender);
int send_three_socks(int sockfd, int ttl, int pid, struct sockaddr_in addr);
int receive(int sockfd, int ttl, int pid, struct sockaddr_in addr, struct reply *reply_table);
int send_sock(int sockfd, int ttl, int pid, struct sockaddr_in addr);
u_int16_t compute_icmp_checksum (const void *buff, int length);
pid_t getpid(void);
int print(int ttl, int received, struct reply *reply_table, char *sender);

#endif