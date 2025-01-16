#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_TRANSACTIONS 10
#define TRANSACTION_SIZE 256

typedef struct Block {
    int index;
    char timestamp[20];
    int transaction_count;
    char transactions[MAX_TRANSACTIONS][TRANSACTION_SIZE];
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

Block* create_block(int index, const char* previous_hash) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->index = index;
    new_block->transaction_count = 0;
    strcpy(new_block->previous_hash, previous_hash);

    get_timestamp(new_block->timestamp);

    strcpy(new_block->hash, "");
    new_block->next = NULL;
    return new_block;
}

void add_transaction(Block* block, const char* transaction) {
    if (block->transaction_count < MAX_TRANSACTIONS) {
        strcpy(block->transactions[block->transaction_count], transaction);
        block->transaction_count++;
    } else {
        printf("Block is full. Cannot add more transactions.\n");
    }
}

void finalize_block(Block* block) {
    char input[1024] = {0};
    snprintf(input, sizeof(input), "%d%s", block->index, block->timestamp);

    for (int i = 0; i < block->transaction_count; i++) {
        strcat(input, block->transactions[i]);
    }

    strcat(input, block->previous_hash);

    compute_hash(input, block->hash);
}

Blockchain* initialize_blockchain() {
    Blockchain* blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->head = create_block(0, "0");
    finalize_block(blockchain->head);
    return blockchain;
}

void add_block(Blockchain* blockchain) {
    Block* current = blockchain->head;
    while (current->next != NULL) {
        current = current->next;
    }

    Block* new_block = create_block(current->index + 1, current->hash);
    current->next = new_block;
}

int validate_blockchain(Blockchain* blockchain) {
    Block* current = blockchain->head;
    while (current->next != NULL) {
        Block* next_block = current->next;

        char calculated_hash[65];
        char input[1024] = {0};
        snprintf(input, sizeof(input), "%d%s", current->index, current->timestamp);

        for (int i = 0; i < current->transaction_count; i++) {
            strcat(input, current->transactions[i]);
        }
        strcat(input, current->previous_hash);
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
        printf("Transactions:\n");
        for (int i = 0; i < current->transaction_count; i++) {
            printf("  - %s\n", current->transactions[i]);
        }
        printf("Previous Hash: %s\n", current->previous_hash);
        printf("Hash: %s\n\n", current->hash);
        current = current->next;
    }
}

int main() {
    Blockchain* blockchain = initialize_blockchain();

    add_transaction(blockchain->head, "Ezekiel pays Magot 10 coins");
    add_transaction(blockchain->head, "Joshua pays Samuel 20 coins");
    finalize_block(blockchain->head);

    add_block(blockchain);
    add_transaction(blockchain->head->next, "Magot pays Joshua 15 coins");
    finalize_block(blockchain->head->next);

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
