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
    for(i=0; i< sb.numInodes; i++){
        inodes[i].size = -1;
        inodes[i].firstBlock = -1;
        strcpy(inodes[i].name, "") ;
    }
    dbs = malloc(sizeof (struct block) * sb.numBlocks);
    for(i=0; i< sb.numBlocks; i++){
        dbs[i].nextBlockNumber = -1;
    }

}

void mountFileSystem()
{
    FILE *file;
    file = fopen("fs_data", "w+");

    //SUPERBLOCK
    fread (&sb, sizeof(struct superblock), 1, file);

    //INODES
    int i;

    //write inodes
    for(i=0; i< sb.numInodes; i++) {
        fread(&(inodes[i]), sizeof(struct inode), 1, file);
    }

    //write db
    for(i=0; i< sb.numBlocks; i++)
    {
        fread(&(dbs[i]), sizeof (struct block), 1, file);
    }

    fclose(file);
}

void syncFileSystem()
{
    FILE *file;
    file = fopen("fs_data", "w+");

    // SUPERBLOCK
    fwrite (&sb, sizeof(struct superblock), 1, file);

    // inodes
    int i;
    for(i=0; i< sb.numInodes; i++) {
        fwrite (&(inodes[i]), sizeof(struct inode), 1, file);
    }

    for(i=0; i<sb.numBlocks; i++)
    {
        fwrite(&(dbs[i]), sizeof(struct block), 1, file);
    }
    //closing file
    fclose(file);

} //SYNC FILE SYSTEM

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