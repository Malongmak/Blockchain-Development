#include "blockchain.h"

int main() {
    Blockchain *chain = create_blockchain();

    Block *genesis_block = create_block(0, "Genesis Block", "0");
    add_block(chain, genesis_block);
    
    Block *second_block = create_block(1, "Second Block", genesis_block->hash);
    add_block(chain, second_block);
    
    if (save_blockchain(chain, "blockchain.dat") == 0) {
        printf("Blockchain saved successfully.\n");
    }

    Blockchain *loaded_chain = create_blockchain();
    if (load_blockchain(loaded_chain, "blockchain.dat") == 0) {
        printf("Blockchain loaded successfully.\n");
    }

    if (validate_blockchain(loaded_chain) == 0) {
        printf("Blockchain validation passed.\n");
    }

    return 0;
}
