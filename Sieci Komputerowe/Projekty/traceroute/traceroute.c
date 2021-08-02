#include "traceroute.h"

int traceroute(int sockfd, struct sockaddr_in *addr, char *sender){
    int pid = getpid();
    for(int ttl = 1; ttl <= 30; ttl++){
        if(send_three_socks(sockfd, ttl, pid, *addr) == -1){
            return -1;
        }
        struct reply reply_table[3];
        int received = receive(sockfd, ttl, pid, *addr, reply_table);
        if(received == -1){
            return -1;
        }
        else if (print(ttl, received, reply_table, sender) == 0){
            return 0;
        }
    }
    return 0;
}

int print(int ttl, int received, struct reply *reply_table, char *sender){
    printf("%d. ", ttl);
    if(received == 0){
        printf("*\n");
    }
    else{
        char ip_table[received][20];
        for(int i = 0; i < received; i++){
            inet_ntop(AF_INET, &((reply_table + i)->addr), ip_table[i], sizeof(ip_table[i]));
        }
        printf("%s", ip_table[0]);
        if(received > 1 && strcmp(ip_table[0], ip_table[1]) != 0){
            printf(" %s", ip_table[1]);
        }
        if(received > 2 && strcmp(ip_table[0], ip_table[2]) != 0 && strcmp(ip_table[1], ip_table[2])){
            printf(" %s", ip_table[2]);
        }
        if(received == 3){
            int avg_time = 0;
            for(int i = 0; i < 3; i++){
                avg_time += (reply_table + i)->time;
            }
            avg_time /= 3000;
            printf(" %dms\n", avg_time);

        }
        else{
            printf(" ???\n");
        }
        if(strcmp(ip_table[0], sender) == 0){
            return 0;
        }
    }
    return 1;
}

