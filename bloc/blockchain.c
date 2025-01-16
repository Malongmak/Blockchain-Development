#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> 

#define MAX_DATA_SIZE 256
#define HASH_SIZE 65 

typedef struct Block {
    int index;
    char timestamp[30];
    char data[MAX_DATA_SIZE];
    char previous_hash[HASH_SIZE];
    char hash[HASH_SIZE];
} Block;

void calculate_hash(Block *block, char *output_hash) {
    char input[MAX_DATA_SIZE + HASH_SIZE + 50];
    snprintf(input, sizeof(input), "%d%s%s%s", block->index, block->timestamp, block->data, block->previous_hash);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }
    output_hash[HASH_SIZE - 1] = '\0';
}

void get_current_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

Block create_block(int index, const char *data, const char *previous_hash) {
    Block block;
    block.index = index;
    get_current_timestamp(block.timestamp, sizeof(block.timestamp));
    strncpy(block.data, data, MAX_DATA_SIZE);
    strncpy(block.previous_hash, previous_hash, HASH_SIZE);
    calculate_hash(&block, block.hash);

    return block;
}

void display_block(const Block *block) {
    printf("Block Index: %d\n", block->index);
    printf("Timestamp: %s\n", block->timestamp);
    printf("Data: %s\n", block->data);
    printf("Previous Hash: %s\n", block->previous_hash);
    printf("Hash: %s\n", block->hash);
}

int main() {
    Block genesis_block = create_block(0, "Genesis Block", "0");
    display_block(&genesis_block);

    return 0;
}
