#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

void pad(uint8_t *block, size_t blockSize, size_t length) {
    size_t paddingLength = blockSize - length % blockSize;
    block[length] = 0x80; // 1 bit followed by zeros
    for (size_t i = 1; i < paddingLength; i++) {
        block[length + i] = 0x00;
    }
}

void ecb_encrypt(uint8_t *plaintext, size_t length, uint8_t *key, uint8_t *ciphertext) {
    uint8_t block[BLOCK_SIZE];
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        // Encrypt block with key
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= key[j]; // Simplified example
        }
        memcpy(ciphertext + i, block, BLOCK_SIZE);
    }
}

void ecb_decrypt(uint8_t *ciphertext, size_t length, uint8_t *key, uint8_t *plaintext) {
    uint8_t block[BLOCK_SIZE];
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, ciphertext + i, BLOCK_SIZE);
        // Decrypt block with key
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= key[j]; // Simplified example
        }
        memcpy(plaintext + i, block, BLOCK_SIZE);
    }
}

int main() {
    uint8_t plaintext[] = "HELLO WORLD"; // Example plaintext
    size_t length = strlen((char *)plaintext);
    uint8_t key[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1}; // Example key
    uint8_t ciphertext[sizeof(plaintext)];
    uint8_t decrypted[sizeof(plaintext)];

    pad(plaintext, BLOCK_SIZE, length);
    ecb_encrypt(plaintext, sizeof(plaintext), key, ciphertext);
    printf("Ciphertext: ");
    for (size_t i = 0; i < sizeof(ciphertext); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    ecb_decrypt(ciphertext, sizeof(ciphertext), key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
