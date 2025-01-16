#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h> 
#include <time.h>

typedef struct Block {
    int index;
    char timestamp[20];
    char data[256];
    char previous_hash[65]; 
    char hash[65];
    struct Block* next;
} Block;

typedef struct Blockchain {
    Block* head; 
} Blockchain;

void get_timestamp(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", t);
}

void compute_hash(const char* input, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
}

Block* create_block(int index, const char* data, const char* previous_hash) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->index = index;
    strcpy(new_block->data, data);
    strcpy(new_block->previous_hash, previous_hash);

    get_timestamp(new_block->timestamp);

    char input[512];
    snprintf(input, sizeof(input), "%d%s%s%s", new_block->index, new_block->timestamp, new_block->data, new_block->previous_hash);

    compute_hash(input, new_block->hash);

    new_block->next = NULL;
    return new_block;
}

Blockchain* initialize_blockchain() {
    Blockchain* blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->head = create_block(0, "Genesis Block", "0");
    return blockchain;
}

void add_block(Blockchain* blockchain, const char* data) {
    Block* current = blockchain->head;

    while (current->next != NULL) {
        current = current->next;
    }

    Block* new_block = create_block(current->index + 1, data, current->hash);
    current->next = new_block;
}

int validate_blockchain(Blockchain* blockchain) {
    Block* current = blockchain->head;
    while (current->next != NULL) {
        Block* next_block = current->next;

        char calculated_hash[65];
        char input[512];
        snprintf(input, sizeof(input), "%d%s%s%s", current->index, current->timestamp, current->data, current->previous_hash);
        compute_hash(input, calculated_hash);

        if (strcmp(current->hash, calculated_hash) != 0) {
            printf("Block %d has an invalid hash.\n", current->index);
            return 0;
        }

        if (strcmp(next_block->previous_hash, current->hash) != 0) {
            printf("Block %d has an invalid previous hash.\n", next_block->index);
            return 0;
        }

        current = next_block;
    }
    return 1;
}

void print_blockchain(Blockchain* blockchain) {
    Block* current = blockchain->head;
    while (current != NULL) {
        printf("Block %d:\n", current->index);
        printf("Timestamp: %s\n", current->timestamp);
        printf("Data: %s\n", current->data);
        printf("Previous Hash: %s\n", current->previous_hash);
        printf("Hash: %s\n\n", current->hash);
        current = current->next;
    }
}

int main() {
    Blockchain* blockchain = initialize_blockchain();

    add_block(blockchain, "Block 1 Data");
    add_block(blockchain, "Block 2 Data");
    add_block(blockchain, "Block 3 Data");

    print_blockchain(blockchain);

    if (validate_blockchain(blockchain)) {
        printf("Blockchain is valid.\n");
    } else {
        printf("Blockchain is invalid.\n");
    }

    Block* current = blockchain->head;
    while (current != NULL) {
        Block* next = current->next;
        free(current);
        current = next;
    }
    free(blockchain);

    return 0;
}
