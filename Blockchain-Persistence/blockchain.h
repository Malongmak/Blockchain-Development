#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block {
    int index;
    char timestamp[20];
    char data[256];
    char previous_hash[65];
    char hash[65];
    struct Block *next;
} Block;

typedef struct Blockchain {
    Block *head;
} Blockchain;

Blockchain* create_blockchain();
Block* create_block(int index, const char* data, const char* previous_hash);
void add_block(Blockchain *chain, Block *new_block);
void calculate_hash(Block *block);
int save_blockchain(Blockchain *chain, const char *filename);
int load_blockchain(Blockchain *chain, const char *filename);

#endif
