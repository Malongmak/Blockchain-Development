# Blockchain Implementation

This project demonstrates the basic implementation of a blockchain in C, covering four tasks to create and manage blocks, build a blockchain, simulate transactions, and persist the blockchain to a file.

## Tasks Overview

### Task 1: Defining the Block Structure

**Objective**: Implement a Block structure that will act as the basic unit in the blockchain.

- **Instructions**: 
  - Define a `Block` structure in C that includes attributes such as `index`, `timestamp`, `data` (or transactions), `previous hash`, and the hash of the current block.
  - Implement a function to display block information.
  - Test by creating and displaying a single block.

- **Outcome**: A `Block` structure is created and displayed, forming the foundation for further blockchain functionality.

### Task 2: Creating a Blockchain

**Objective**: Implement a linked list to manage blocks in the blockchain.

- **Instructions**:
  - Develop functions to add a block to the blockchain, ensuring that each new block correctly stores the hash of the previous block.
  - Implement the SHA-256 hashing function to generate hashes for each block.
  - Write a function to validate the integrity of the blockchain by ensuring the chain of hashes is consistent throughout the blockchain.

- **Outcome**: The blockchain is managed as a linked list, with each block correctly storing the hash of its predecessor, and the blockchain’s integrity is validated.

### Task 3: Simulating Transactions

**Objective**: Simulate transaction data within blocks.

- **Instructions**:
  - Modify the `Block` structure to include a list of transactions (which could be simple strings or more complex structures).
  - Implement a function to add transactions to a block.
  - Ensure that changes in transaction data reflect accurately in the block’s hash.

- **Outcome**: Each block can store transaction data, and any modification in the transaction data results in a change in the block’s hash, ensuring the blockchain reflects accurate data.

### Task 4: Blockchain Persistence

**Objective**: Save the blockchain to a file and load it back into the application.

- **Instructions**:
  - Write functions to save the entire blockchain to a file and load it from the file.
  - Ensure the integrity of the blockchain upon loading by re-validating the hashes.

- **Outcome**: The blockchain can be saved to and loaded from a file while ensuring its integrity is maintained through hash re-validation.

## Project Details

## Features

- **Block Structure**: Each block contains essential data including `index`, `timestamp`, `transactions`, `previous_hash`, `hash`, and a pointer to the next block.
- **Blockchain**: The blockchain is implemented as a linked list of blocks, where each block contains a reference to the previous block's hash.
- **SHA-256 Hashing**: The `SHA-256` hashing function is used to generate secure hashes for each block, ensuring data integrity.
- **Transactions**: Simulate basic transaction data within each block. Changes in transactions automatically reflect in the block’s hash.
- **Persistence**: The blockchain can be saved to and loaded from a file while maintaining its integrity through hash validation.

## Compilation and Usage

### Compilation

To compile the project, use the following command:

gcc -o blockchain main.c blockchain.c -lssl -lcrypto

### Running the Program

To run the program, use the following command:

./blockchain

### Additional Information

- **C Language**: C language is used in the project.
## Code Structure

- **main.c**: Entry point of the program, handles block creation, blockchain construction, transaction simulation, and persistence.
- **blockchain.c**: Contains the implementation of blockchain functionality such as adding blocks, hashing, and saving/loading from a file.
- **blockchain.h**: Header file containing function declarations and the `Block` structure definition.

## Challenges and Solutions

- **Memory Management**: Proper memory management was required to allocate and deallocate memory for blocks and the blockchain.
- **Hashing**: Using `SHA-256` ensured a secure hashing mechanism. Implementing this function required knowledge of the OpenSSL library.
- **File Operations**: Managing file reading and writing with the blockchain involved handling binary data. The blockchain is serialized for saving and deserialized for loading.

## Analysis of Data Structures and Blockchain Operations

### Block Structure

Each block in the blockchain contains a unique `index`, a `timestamp`, transaction data, the `previous_hash`, and its own `hash`. This structure ensures that each block is uniquely identifiable, contains a timestamp, and maintains the integrity of the blockchain with references to the previous block's hash.

### Blockchain Integrity

The blockchain is stored as a linked list, where each block contains a pointer to the next block. The hash of each block is computed based on the data in the block, including the `previous_hash`. When loading the blockchain, each block’s hash is re-validated to ensure the chain’s integrity. This mechanism simulates how a real-world blockchain ensures data consistency and security.

### Transactions

Simulating transactions within each block demonstrates how a blockchain can store and manage transaction data. The hash of the block changes whenever the transaction data is modified, ensuring the blockchain’s immutability and integrity.

## License

This project is licensed under the [MIT License](LICENSE).
