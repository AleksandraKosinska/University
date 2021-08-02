#include "traceroute.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        return EXIT_FAILURE;
    }

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_port = ECHO_PORT;
    addr.sin_family = AF_INET;

    int check = inet_pton(AF_INET, argv[1], &addr.sin_addr);
    if (check != 1){
        if (check == 0){
            fprintf(stderr, "not in presentation format");
        }
        else{
            fprintf(stderr, "inet_pton error: %s\n", strerror(errno));
        }
        return EXIT_FAILURE;
    }

    if(traceroute(sockfd, &addr, argv[1]) == -1){
        return EXIT_FAILURE;
    }
    return 0;
}