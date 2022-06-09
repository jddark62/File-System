//
// Created by jade on 6/6/22.
//

#include "main.h"
#include <stdlib.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>


struct superblock sb;

//array of what currently is open
struct inode *inodes;
struct block *dbs;

//Initializing new filesystem
void createFileSystem()
{
    sb.numInodes = 10;
    sb.numBlocks = 100;
    sb.sizeOfBlocks = sizeof (struct block);

    int i;
    inodes = malloc (sizeof (struct inode) * sb.numInodes);
    for (i = 0; i < sb.numInodes; i++)
    {
        inodes[i]. size =-1;
        inodes[i].firstBlock = -1;
        strcpy(inodes[i].name, "emptyfi");
    } //initializing nodes
    dbs = malloc (sizeof (struct block) * sb.numBlocks);
    for (i = 0; i < sb.numBlocks; i++){
        dbs[i].nextBlockNumber = -1;
    }
}

void mountFileSystem()
{
    FILE *file;
    file = fopen("fs_data", "r");
    inodes = malloc (sizeof (struct inode) * sb.numInodes);
    dbs = malloc (sizeof (struct block) * sb.numBlocks);
    //SUPERBLOCK
    fread (&sb, sizeof(struct superblock), 1, file);

    fread(inodes, sizeof (struct inode), sb.numInodes, file);
    fread(dbs, sizeof(struct block), sb.numBlocks, file);
    fclose(file);
}

void syncFileSystem()
{
    FILE *file;
    file = fopen("fs_data", "w+");

    // SUPERBLOCK
    fwrite(&sb, sizeof (struct superblock), 1, file);

    //inodes
    fwrite(inodes, sizeof(struct inode), sb.numInodes, file);
    fwrite(dbs, sizeof(struct block), sb.numBlocks, file);
    fclose(file);

}//SYNC FILE SYSTEM

void printFileSystem() {
    printf ("Superblock INFO\n");
    printf("\tnum inodes %d\n", sb.numInodes);
    printf("\tnum blocks %d\n", sb.numBlocks);
    printf("\tsize blocks %d\n", sb.sizeOfBlocks);

    printf("inodes\n");

    int i;
    //inodes = malloc (sizeof (struct inode) * sb.numInodes);
    for(i=0; i< sb.numInodes; i++){
        printf("\tsize: %d block : %d name: %s\n", inodes[i].size, inodes[i].firstBlock, inodes[i].name);
    } //initialize inodes
    //dbs = malloc(sizeof (struct block) * sb.numBlocks);
    for(i=0; i< sb.numBlocks; i++){
        printf("\tblock num: %d next block %d\n", i, dbs[i].nextBlockNumber);
    }
}


int allocate_file (char name[8])
{
    //find an empty inode
    int in = find_empty_inode();
    //claim it
    int block = find_empty_block();
    //find/claim a disk block

    //claim them
    inodes[in].firstBlock = block;
    dbs[block].nextBlockNumber = -2;

    strcpy (inodes[in].name, name);
    //return file descriptor
    return in;


} //allocate_file

int find_empty_inode()
{
    int i;
    for( i=0; i < sb.numInodes; i++) {
        if(inodes[i].firstBlock == -1) {
            return i;
        }
    }
    return -1;
}

int find_empty_block()
{
    int i;
    for( i=0; i < sb.numBlocks; i++) {
        if(dbs[i].nextBlockNumber == -1) {
            return i;
        }
    }
    return -1;
}

int get_block_num (int file, int offset){
    int togo = offset;
    int bn = inodes[file].firstBlock;

    while(togo > 0){
        bn = dbs[bn].nextBlockNumber;
        togo--;
    }
    return bn;
}
void set_filesize (int filenum, int size){
    // how many blocks should we have
    int empty;
    int tmp = size + BLOCKSIZE - 1;
    int num = tmp / BLOCKSIZE;
    int bn = inodes[filenum].firstBlock;
    num--;
    //grow the file if necessary
    while(num>0){
        //check next block number
        int next_num = dbs[bn].nextBlockNumber;
        if (next_num == -2) {
            empty = find_empty_block();
            dbs[bn].nextBlockNumber = empty;
            dbs[empty].nextBlockNumber = -2;
        }
        bn = dbs[bn].nextBlockNumber;
        num--;

    }

    //shorten if necessary
    shortenFile(bn);
    dbs[bn].nextBlockNumber = -2;
}
void write_data (int filenum, int pos, char *data){
    //calculate which block
    int relative_block = pos / BLOCKSIZE;

    //find the block number
    int bn = get_block_num(filenum, relative_block);
    //calculate the offset in the block
    int offset = pos % BLOCKSIZE;
    // write the data
    dbs[bn].data[offset] = (*data);

}
void shortenFile(int bn){
    int nn = dbs[bn].nextBlockNumber;
    if (nn >=0){
        shortenFile(nn);
    }
    dbs[bn].nextBlockNumber = -1;

}
