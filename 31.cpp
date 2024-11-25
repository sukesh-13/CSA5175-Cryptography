#include <stdio.h>
#include <stdint.h>
#include <string.h>

void print_block(uint8_t* block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X", block[i]);
    }
    printf("\n");
}

void left_shift(uint8_t* block, int size) {
    int carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        int new_carry = (block[i] & 0x80) ? 1 : 0;
        block[i] = (block[i] << 1) | carry;
        carry = new_carry;
    }
}

void xor_with_constant(uint8_t* block, int size, uint8_t constant) {
    block[size - 1] ^= constant;
}

void generate_subkeys(uint8_t* key, int block_size, uint8_t* K1, uint8_t* K2) {
    uint8_t L[block_size];
    memset(L, 0, block_size);

    // Apply the block cipher to the zero block (using the key as a simple example)
    memcpy(L, key, block_size);

    // Derive K1
    memcpy(K1, L, block_size);
    left_shift(K1, block_size);

    uint8_t R = (block_size == 8) ? 0x1B : 0x87; // R constants for 64 and 128 bits
    if (L[0] & 0x80) {
        xor_with_constant(K1, block_size, R);
    }

    // Derive K2
    memcpy(K2, K1, block_size);
    left_shift(K2, block_size);
    if (K1[0] & 0x80) {
        xor_with_constant(K2, block_size, R);
    }
}

int main() {
    int block_size = 16; // Example for 128-bit block size
    uint8_t key[block_size];
    uint8_t K1[block_size];
    uint8_t K2[block_size];

    memset(key, 0xAB, block_size); // Example key

    generate_subkeys(key, block_size, K1, K2);

    printf("K1: ");
    print_block(K1, block_size);
    printf("K2: ");
    print_block(K2, block_size);

    return 0;
}
