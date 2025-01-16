#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Block {
    int index;
    char timestamp[64];
    char data[256];
    char previous_hash[64];
    char hash[64];
    struct Block *next;
} Block;

typedef struct Blockchain {
    Block *head;
} Blockchain;

void calculate_hash(Block *block);
Block* create_block(int index, const char* data, const char* previous_hash);
Blockchain* create_blockchain();
void add_block(Blockchain *chain, Block *new_block);
int save_blockchain(Blockchain *chain, const char *filename);
int load_blockchain(Blockchain *chain, const char *filename);
int validate_blockchain(Blockchain *chain);

#endif
