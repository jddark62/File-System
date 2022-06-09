//
// Created by jade on 6/6/22.
//
#include<stdio.h>
#include "main.h"

int main() {
    //createFileSystem();

    mountFileSystem();
    int file = allocate_file("another");

    set_filesize(file, 5000);

    char data = 'b';

    int i;
    for(i = 0; i < 49; i++){
        write_data (0, i*100, &data);
    }

    syncFileSystem();
    printFileSystem();

    printf("File System Created.\n");
}