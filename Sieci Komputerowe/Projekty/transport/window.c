#include "transport.h"

void init_window(window *win, size_t file_size){
    //allocate memory for all entries in a window
    win->entries = malloc(WINDOW_SIZE * sizeof(entry));
    for(int i = 0; i < WINDOW_SIZE; i++){
        //allocate memory for data of an entry
        win->entries[i].data = malloc(ENTRY_SIZE * sizeof(char));
        win->entries->downloaded = false;
    }
    win->begin = 0;
    win->entries_num = (file_size + ENTRY_SIZE - 1) / ENTRY_SIZE;
}

void delete_window(window *win){
    for(int i = 0; i < WINDOW_SIZE; i++){
        free(win->entries[i].data);
    }
    free(win->entries);
}