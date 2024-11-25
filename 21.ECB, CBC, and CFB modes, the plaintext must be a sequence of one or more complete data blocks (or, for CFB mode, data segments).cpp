#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK_SIZE 8 
void encrypt_block(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void decrypt_block(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext);
void pad_message(uint8_t *message, int *message_len);
void remove_padding(uint8_t *message, int *message_len);

void ecb_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *ciphertext);
void ecb_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *plaintext);

void cbc_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext);
void cbc_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext);

void cfb_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext);
void cfb_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext);

void encrypt_block(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

void decrypt_block(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i]; 
    }
}

void pad_message(uint8_t *message, int *message_len) {
    int pad_len = BLOCK_SIZE - (*message_len % BLOCK_SIZE);
    for (int i = 0; i < pad_len; i++) {
        message[*message_len + i] = (i == 0) ? 0x80 : 0x00; 
    }
    *message_len += pad_len;
}

void remove_padding(uint8_t *message, int *message_len) {
    int i = *message_len - 1;
    while (i >= 0 && message[i] == 0x00) {
        i--;
    }
    if (i >= 0 && message[i] == 0x80) {
        *message_len = i; 
    }
}

void ecb_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *ciphertext) {
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        encrypt_block(plaintext + i, key, ciphertext + i);
    }
}

void ecb_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *plaintext) {
    for (int i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        decrypt_block(ciphertext + i, key, plaintext + i);
    }
}

void cbc_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        uint8_t current_block[BLOCK_SIZE];
        for (int j = 0; j < BLOCK_SIZE; j++) {
            current_block[j] = plaintext[i + j] ^ prev_block[j];
        }
        encrypt_block(current_block, key, ciphertext + i);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cbc_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext) {
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        uint8_t current_block[BLOCK_SIZE];
        decrypt_block(ciphertext + i, key, current_block);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = current_block[j] ^ prev_block[j];
        }
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        uint8_t encrypted_feedback[BLOCK_SIZE];
        encrypt_block(feedback, key, encrypted_feedback);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ encrypted_feedback[j];
            feedback[j] = ciphertext[i + j];
        }
    }
}

void cfb_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        uint8_t encrypted_feedback[BLOCK_SIZE];
        encrypt_block(feedback, key, encrypted_feedback);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = ciphertext[i + j] ^ encrypted_feedback[j];
            feedback[j] = ciphertext[i + j];
        }
    }
}

int main() {
    uint8_t plaintext[256] = "This is a test message for encryption!";
    int plaintext_len = strlen((char *)plaintext);
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t iv[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    uint8_t ciphertext[256] = {0};
    uint8_t decrypted_text[256] = {0};

    printf("Original Plaintext: %s\n", plaintext);

    pad_message(plaintext, &plaintext_len);

    ecb_encrypt(plaintext, plaintext_len, key, ciphertext);
    ecb_decrypt(ciphertext, plaintext_len, key, decrypted_text);
    remove_padding(decrypted_text, &plaintext_len);
    printf("ECB Decrypted: %s\n", decrypted_text);

    cbc_encrypt(plaintext, plaintext_len, key, iv, ciphertext);
    cbc_decrypt(ciphertext, plaintext_len, key, iv, decrypted_text);
    remove_padding(decrypted_text, &plaintext_len);
    printf("CBC Decrypted: %s\n", decrypted_text);

    cfb_encrypt(plaintext, plaintext_len, key, iv, ciphertext);
    cfb_decrypt(ciphertext, plaintext_len, key, iv, decrypted_text);
    remove_padding(decrypted_text, &plaintext_len);
    printf("CFB Decrypted: %s\n", decrypted_text);

    return 0;
}
