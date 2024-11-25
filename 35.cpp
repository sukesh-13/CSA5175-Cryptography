#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_random_key(int *key, size_t length) {
    srand(time(NULL));
    for (size_t i = 0; i < length; i++) {
        key[i] = rand() % 27; // Random number between 0 and 26
    }
}

void encrypt(char *plaintext, int *key, char *ciphertext, size_t length) {
    for (size_t i = 0; i < length; i++) {
        char plain_char = plaintext[i];
        if (plain_char >= 'A' && plain_char <= 'Z') {
            ciphertext[i] = ((plain_char - 'A' + key[i]) % 26) + 'A';
        } else if (plain_char >= 'a' && plain_char <= 'z') {
            ciphertext[i] = ((plain_char - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plain_char;
        }
    }
    ciphertext[length] = '\0';
}

void decrypt(char *ciphertext, int *key, char *plaintext, size_t length) {
    for (size_t i = 0; i < length; i++) {
        char cipher_char = ciphertext[i];
        if (cipher_char >= 'A' && cipher_char <= 'Z') {
            plaintext[i] = ((cipher_char - 'A' - key[i] + 26) % 26) + 'A';
        } else if (cipher_char >= 'a' && cipher_char <= 'z') {
            plaintext[i] = ((cipher_char - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = cipher_char;
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[] = "HELLO";
    size_t length = strlen(plaintext);

    int key[length];
    char ciphertext[length + 1];
    char decrypted_text[length + 1];

    generate_random_key(key, length);
    
    printf("Key: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    encrypt(plaintext, key, ciphertext, length);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted_text, length);
    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}
