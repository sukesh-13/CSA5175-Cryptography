#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8  
#define NUM_BLOCKS 3  
 
uint8_t sdes_encrypt(uint8_t input, uint8_t key);
void ctr_encrypt(uint8_t *plaintext, int num_blocks, uint8_t key, uint8_t counter, uint8_t *ciphertext);
void ctr_decrypt(uint8_t *ciphertext, int num_blocks, uint8_t key, uint8_t counter, uint8_t *plaintext);
 
uint8_t sdes_encrypt(uint8_t input, uint8_t key) { 
    return input ^ key;  
}
 
void ctr_encrypt(uint8_t *plaintext, int num_blocks, uint8_t key, uint8_t counter, uint8_t *ciphertext) {
    for (int i = 0; i < num_blocks; i++) {
        uint8_t keystream = sdes_encrypt(counter, key); 
        ciphertext[i] = plaintext[i] ^ keystream;        
        counter++;                                       
    }
}
 
void ctr_decrypt(uint8_t *ciphertext, int num_blocks, uint8_t key, uint8_t counter, uint8_t *plaintext) {
    for (int i = 0; i < num_blocks; i++) {
        uint8_t keystream = sdes_encrypt(counter, key);  
        plaintext[i] = ciphertext[i] ^ keystream;       
        counter++;                                      
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
    const char *plaintext_binary[] = {"00000001", "00000010", "00000100"};
    const char *key_binary = "0111111101";
    const char *counter_binary = "00000000";

    uint8_t plaintext[NUM_BLOCKS], ciphertext[NUM_BLOCKS], decrypted[NUM_BLOCKS];
    uint8_t key = binary_to_uint8(key_binary);
    uint8_t counter = binary_to_uint8(counter_binary);
  
    for (int i = 0; i < NUM_BLOCKS; i++) {
        plaintext[i] = binary_to_uint8(plaintext_binary[i]);
    }
 
    ctr_encrypt(plaintext, NUM_BLOCKS, key, counter, ciphertext);
 
    ctr_decrypt(ciphertext, NUM_BLOCKS, key, counter, decrypted);
 
    printf("Original Plaintext:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        char binary[9];
        uint8_to_binary(plaintext[i], binary);
        printf("Block %d: %s\n", i + 1, binary);
    }

    printf("\nCiphertext:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        char binary[9];
        uint8_to_binary(ciphertext[i], binary);
        printf("Block %d: %s\n", i + 1, binary);
    }

    printf("\nDecrypted Plaintext:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        char binary[9];
        uint8_to_binary(decrypted[i], binary);
        printf("Block %d: %s\n", i + 1, binary);
    }

    return 0;
}
