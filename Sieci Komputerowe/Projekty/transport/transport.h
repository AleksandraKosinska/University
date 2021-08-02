#ifndef transport_h
#define transport_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#define WINDOW_SIZE 3000
#define ENTRY_SIZE 1000

//one entry in window
typedef struct{
    char *data;
    bool downloaded;
} entry;

//window
typedef struct{
    //all entries in a window
    entry *entries;
    //idx of entry from whole file, begin of entries in window
    int begin;
    //number of entries to download
    int entries_num;
} window;

//window
void init_window(window *win, size_t file_size);
void delete_window(window *win);

//transport
size_t min(size_t a, size_t b);
void get(int sockfd, struct sockaddr_in addr, size_t start, size_t bytes);
void get_data(int sockfd, window *win, struct sockaddr_in addr, size_t bytes_downloaded, size_t bytes_to_download);
int wait_for_data(int sockfd, struct timeval *tv);
int receive_data(int sockfd, struct sockaddr_in addr, window *win, size_t *bytes_downloaded);
void write_to_file(FILE *file, window *win, size_t bytes_to_download);
int download(int sockfd, struct sockaddr_in addr, char *file_name, size_t file_size);

#endif