//
// Created by jade on 6/6/22.
//

#ifndef FILE_SYSTEM_MAIN_H
#define FILE_SYSTEM_MAIN_H

//meta information about the filesystem
//number of inodes
//number of disk blocks
//size of the disk blocks
struct superblock{
    int numInodes;
    int numBlocks;
    int sizeOfBlocks;
};

struct inode{
    int size;
    char name[8];
    int firstBlock;
};
struct block{
    int nextBlockNumber;
    char data[512];
};
void createFileSystem();   //Initializing the new file system
void mountFileSystem(); //Load the file system
void syncFileSystem();  //Write the file system

void printFileSystem();
#endif //FILE_SYSTEM_MAIN_H
