#include "blockchain.h"

int main() {
    Blockchain *chain = create_blockchain();
    
    Block *block1 = create_block(1, "First Block", "0");
    add_block(chain, block1);
    
    Block *block2 = create_block(2, "Second Block", block1->hash);
    add_block(chain, block2);
    
    save_blockchain(chain, "blockchain.dat");
    
    Blockchain *loaded_chain = create_blockchain();
    load_blockchain(loaded_chain, "blockchain.dat");
    
    Block *current = loaded_chain->head;
    while (current != NULL) {
        printf("Block %d: %s\n", current->index, current->data);
        current = current->next;
    }
    
    return 0;
}
