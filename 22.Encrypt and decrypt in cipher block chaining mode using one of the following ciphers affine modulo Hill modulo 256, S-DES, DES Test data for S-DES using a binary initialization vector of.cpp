#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 



uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key);
uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key);
void cbc_encrypt(uint8_t *plaintext, int num_blocks, uint8_t key, uint8_t iv, uint8_t *ciphertext);
void cbc_decrypt(uint8_t *ciphertext, int num_blocks, uint8_t key, uint8_t iv, uint8_t *plaintext);


uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key) {
    return plaintext ^ key; 
}

uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key) {
    return ciphertext ^ key; 
}

void cbc_encrypt(uint8_t *plaintext, int num_blocks, uint8_t key, uint8_t iv, uint8_t *ciphertext) {
    uint8_t prev_block = iv;
    for (int i = 0; i < num_blocks; i++) {
        uint8_t input_block = plaintext[i] ^ prev_block; 
        ciphertext[i] = sdes_encrypt(input_block, key);
        prev_block = ciphertext[i]; 
    }
}

void cbc_decrypt(uint8_t *ciphertext, int num_blocks, uint8_t key, uint8_t iv, uint8_t *plaintext) {
    uint8_t prev_block = iv;
    for (int i = 0; i < num_blocks; i++) {
        uint8_t decrypted_block = sdes_decrypt(ciphertext[i], key);
        plaintext[i] = decrypted_block ^ prev_block;
        prev_block = ciphertext[i];
    }
}
uint8_t binary_to_uint8(const char *binary) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result <<= 1;
        if (binary[i] == '1') {
            result |= 1;
        }
    }
    return result;
}

void uint8_to_binary(uint8_t value, char *binary) {
    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = (value & (1 << i)) ? '1' : '0';
    }
    binary[8] = '\0';
}

int main() {
    const char *plaintext_binary[] = {"00000001", "00100011"};
    const char *key_binary = "0111111101";
    const char *iv_binary = "10101010";

    uint8_t plaintext[2], ciphertext[2], decrypted[2];
    uint8_t key = binary_to_uint8(key_binary);
    uint8_t iv = binary_to_uint8(iv_binary);
    int num_blocks = 2;

    for (int i = 0; i < num_blocks; i++) {
        plaintext[i] = binary_to_uint8(plaintext_binary[i]);
    }

    cbc_encrypt(plaintext, num_blocks, key, iv, ciphertext);

    cbc_decrypt(ciphertext, num_blocks, key, iv, decrypted);

    printf("Original Plaintext:\n");
    for (int i = 0; i < num_blocks; i++) {
        char binary[9];
        uint8_to_binary(plaintext[i], binary);
        printf("Block %d: %s\n", i + 1, binary);
    }

    printf("\nCiphertext:\n");
    for (int i = 0; i < num_blocks; i++) {
        char binary[9];
        uint8_to_binary(ciphertext[i], binary);
        printf("Block %d: %s\n", i + 1, binary);
    }

    printf("\nDecrypted Plaintext:\n");
    for (int i = 0; i < num_blocks; i++) {
        char binary[9];
        uint8_to_binary(decrypted[i], binary);
        printf("Block %d: %s\n", i + 1, binary);
    }

    return 0;
}
