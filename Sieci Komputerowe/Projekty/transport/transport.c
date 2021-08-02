#include "transport.h"

size_t min(size_t a, size_t b){
    return ((a)<(b))?(a):(b);
}
//send request
void get(int sockfd, struct sockaddr_in addr, size_t start, size_t bytes){
    char *buffer = malloc(35);
    sprintf(buffer, "GET %ld %ld\n", start, bytes);
    size_t buf_len = strlen(buffer);
    if(sendto(sockfd, buffer, buf_len, 0, (struct sockaddr *) &addr, sizeof(addr)) < 0){
        fprintf(stderr, "sendto error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    free(buffer);
}
//send 3 request for every not downloaded entry in window
void get_data(int sockfd, window *win, struct sockaddr_in addr, size_t bytes_downloaded, size_t bytes_to_download){
    entry *en = win->entries;
    for(int j = 0; j < 2; j++){
        for(int i = win->begin; i < win->begin + WINDOW_SIZE && i < win->entries_num; i++){
            if(en[i % WINDOW_SIZE].downloaded == false){
                get(sockfd, addr, i * ENTRY_SIZE, min(ENTRY_SIZE, bytes_to_download - bytes_downloaded));
            }
        }
    }
}

int wait_for_data(int sockfd, struct timeval *tv){
    fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);
    int ready = select(sockfd+1, &descriptors, NULL, NULL, tv);
    if(ready < 0){
        fprintf(stderr, "select error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if(ready == 0){
        tv->tv_sec = 3;
        tv->tv_usec = 0;
    }
    return ready;
}



int receive_data(int sockfd, struct sockaddr_in addr, window *win, size_t *bytes_downloaded){
    size_t recv_start = 0;
    size_t recv_bytes = 0;
    struct sockaddr_in in_addr;
    socklen_t addr_in_len = sizeof(in_addr);
    char *buffer = malloc(IP_MAXPACKET);
    ssize_t packet_len = recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr *) &in_addr, &addr_in_len);
    if (packet_len < 0) {
        fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
        exit(EXIT_FAILURE);
    }
    if((sscanf(buffer, "DATA %ld %ld\n", &recv_start, &recv_bytes) != 2) || (addr.sin_port != in_addr.sin_port)){
        return 0;
    }
    //idx of entry in a whole file
    int idx = recv_start / ENTRY_SIZE;
    if(idx < win->begin){
        free(buffer);
        return 0;
    }
    //idx in a window
    idx %= WINDOW_SIZE;
    if(win->entries[idx].downloaded == false){
        memcpy(win->entries[idx].data, strchr(buffer, '\n') + 1, recv_bytes);
        win->entries[idx].downloaded = true;
        *bytes_downloaded += recv_bytes;
        free(buffer);
        return 1;
    }
    free(buffer);
    return 0;
}

void write_to_file(FILE *file, window *win, size_t bytes_to_download){
    entry *en = win->entries;
    int idx = win->begin % WINDOW_SIZE;
    int counter = 0;
    int entry_size = ENTRY_SIZE;
    while(en[idx].downloaded == true && win->begin < win->entries_num && counter < WINDOW_SIZE){
        if(win->begin == win->entries_num - 1){
            entry_size = ENTRY_SIZE - (win->entries_num * ENTRY_SIZE) + bytes_to_download;
        }
        for(int i = 0; i < entry_size; i++){
            fputc(en[idx].data[i], file);
        }
        en[idx].downloaded = false;
        idx = (idx + 1)%WINDOW_SIZE;
        win->begin++;
        counter++;
    }
}

int download(int sockfd, struct sockaddr_in addr, char *file_name, size_t bytes_to_download){
    FILE *file = fopen(file_name, "w");
    if(file == NULL){
        fprintf(stderr, "fopen error: %s\n", strerror(errno));
        EXIT_FAILURE;
    }

    //time variable for select
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;

    size_t bytes_downloaded = 0;

    window win;
    init_window(&win, bytes_to_download);
    size_t percent = win.entries_num * ENTRY_SIZE;

    while(win.begin < win.entries_num){
        get_data(sockfd, &win, addr, bytes_downloaded, bytes_to_download);
        if(wait_for_data(sockfd, &tv) > 0){
            if(receive_data(sockfd, addr, &win, &bytes_downloaded) == 1){
                write_to_file(file, &win, bytes_to_download);
                printf("%.3f%%\n", 100.0 * (float)(bytes_downloaded)/(float)(percent));
            }
        }
    }
    delete_window(&win);
    fclose(file);

    return EXIT_SUCCESS;
}