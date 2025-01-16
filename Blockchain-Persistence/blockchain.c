#include "blockchain.h"

void calculate_hash(Block *block) {
    char input[512];
    snprintf(input, sizeof(input), "%d%s%s%s", block->index, block->timestamp, block->data, block->previous_hash);
    
    unsigned long hash = 0;
    for (int i = 0; i < strlen(input); i++) {
        hash = hash * 31 + input[i];
    }
    
    snprintf(block->hash, sizeof(block->hash), "%lx", hash);
}

Block* create_block(int index, const char* data, const char* previous_hash) {
    Block *new_block = (Block*)malloc(sizeof(Block));
    new_block->index = index;
    snprintf(new_block->timestamp, sizeof(new_block->timestamp), "%ld", time(NULL));
    snprintf(new_block->data, sizeof(new_block->data), "%s", data);
    snprintf(new_block->previous_hash, sizeof(new_block->previous_hash), "%s", previous_hash);
    new_block->next = NULL;
    
    calculate_hash(new_block);
    
    return new_block;
}

Blockchain* create_blockchain() {
    Blockchain *chain = (Blockchain*)malloc(sizeof(Blockchain));
    chain->head = NULL;
    return chain;
}

void add_block(Blockchain *chain, Block *new_block) {
    if (chain->head == NULL) {
        chain->head = new_block;
    } else {
        Block *current = chain->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_block;
    }
}

int save_blockchain(Blockchain *chain, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Unable to open file for saving blockchain");
        return -1;
    }
    
    Block *current = chain->head;
    while (current != NULL) {
        fwrite(current, sizeof(Block), 1, file);
        current = current->next;
    }
    
    fclose(file);
    return 0;
}

int load_blockchain(Blockchain *chain, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open file for loading blockchain");
        return -1;
    }
    
    Block *new_block = malloc(sizeof(Block));
    Block *previous_block = NULL;
    
    while (fread(new_block, sizeof(Block), 1, file)) {
        if (previous_block != NULL) {
            if (strcmp(new_block->previous_hash, previous_block->hash) != 0) {
                printf("Blockchain integrity compromised!\n");
                fclose(file);
                return -1;
            }
        }
        
        if (chain->head == NULL) {
            chain->head = new_block;
        } else {
            previous_block->next = new_block;
        }
        
        previous_block = new_block;
        new_block = malloc(sizeof(Block));
    }
    
    fclose(file);
    return 0;
}

int validate_blockchain(Blockchain *chain) {
    Block *current = chain->head;
    while (current != NULL && current->next != NULL) {
        char previous_hash[64];
        snprintf(previous_hash, sizeof(previous_hash), "%s", current->hash);
        
        Block *next_block = current->next;
        if (strcmp(next_block->previous_hash, previous_hash) != 0) {
            printf("Blockchain integrity compromised at block %d!\n", current->index + 1);
            return -1;
        }
        
        char input[512];
        snprintf(input, sizeof(input), "%d%s%s%s", current->index, current->timestamp, current->data, current->previous_hash);
        unsigned long hash = 0;
        for (int i = 0; i < strlen(input); i++) {
            hash = hash * 31 + input[i];
        }
        char computed_hash[64];
        snprintf(computed_hash, sizeof(computed_hash), "%lx", hash);
        
        if (strcmp(current->hash, computed_hash) != 0) {
            printf("Hash mismatch at block %d!\n", current->index);
            return -1;
        }

        current = current->next;
    }
    
    printf("Blockchain integrity validated successfully.\n");
    return 0;
}
