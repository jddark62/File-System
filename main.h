//
// Created by jade on 6/6/22.
//

#ifndef FILE_SYSTEM_MAIN_H
#define FILE_SYSTEM_MAIN_H

//meta information about the filesystem
//number of inodes
//number of disk blocks
//size of the disk blocks
#define BLOCKSIZE 512
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
    char data[BLOCKSIZE];
};
void createFileSystem();   //Initializing the new file system
void mountFileSystem(); //Load the file system
void syncFileSystem();  //Write the file system
void printFileSystem();
// returns filenumber
int allocate_file (char name[8]);
void set_filesize (int filenum, int size);
void write_data (int filenum, int pos, char *data);
int find_empty_inode();
int find_empty_block();
void shortenFile (int bn);
#endif //FILE_SYSTEM_MAIN_H
