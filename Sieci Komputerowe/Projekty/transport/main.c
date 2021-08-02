#include "transport.h"

int main(int argc, char *argv[]){
    if(argc != 5){
        fprintf(stderr, "wrong number of arguments");
        return EXIT_FAILURE;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    int addr_check = inet_pton(AF_INET, argv[1], &addr.sin_addr);
    if (addr_check != 1){
        if (addr_check == 0){
            fprintf(stderr, "address not in presentation format\n");
        }
        else{
            fprintf(stderr, "inet_pton error: %s\n", strerror(errno));
        }
        return EXIT_FAILURE;
    }

    int port = atoi(argv[2]);
    if(port < 1 || port > 65535){
        fprintf(stderr, "port out of range\n");
        return EXIT_FAILURE;
    }
    addr.sin_port = htons(port);

    char *file_name = argv[3];

    size_t file_size = atoi(argv[4]);
    if(file_size < 1){
        if(file_size == 0){
            printf("file size is 0\n");
            return EXIT_SUCCESS;
        }
        fprintf(stderr, "file size < 0\n");
        return EXIT_FAILURE;
    }

    if(download(sockfd, addr, file_name, file_size) == EXIT_FAILURE){
        fprintf(stderr, "download failure\n");
        return EXIT_FAILURE;
    }

}