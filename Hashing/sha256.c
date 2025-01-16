#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void compute_sha256(const char *input, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

void print_hash(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    const char *input = "Blockchain Cryptography";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Input: %s\n", input);
    compute_sha256(input, hash);

    printf("SHA-256 Hash: ");
    print_hash(hash);

    return 0;
}