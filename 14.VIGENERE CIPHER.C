#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt using the one-time pad Vigenère cipher
void encrypt(char plaintext[], int key[], int key_length, char ciphertext[]) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            // Convert to uppercase and shift based on the key
            ciphertext[i] = ((toupper(plaintext[i]) - 'A' + key[i % key_length]) % 26) + 'A';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext string
}

// Function to decrypt using the one-time pad Vigenère cipher
void decrypt(char ciphertext[], int key[], int key_length, char plaintext[]) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            // Convert to uppercase and reverse the shift based on the key
            plaintext[i] = ((toupper(ciphertext[i]) - 'A' - key[i % key_length] + 26) % 26) + 'A';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[i] = '\0'; // Null-terminate the plaintext string
}

// Function to generate a key for part (b)
void generateKeyForDecryption(char ciphertext[], char target_plaintext[], int key[], int key_length) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i]) && isalpha(target_plaintext[i])) {
            key[i] = (toupper(ciphertext[i]) - toupper(target_plaintext[i]) + 26) % 26;
        } else {
            key[i] = 0; // Non-alphabetic characters have no key
        }
    }
}

int main() {
    // Part (a) Encrypt
    char plaintext[] = "send more money";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_length = sizeof(key_stream) / sizeof(key_stream[0]);
    char ciphertext[100];

    encrypt(plaintext, key_stream, key_length, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    // Part (b) Decrypt to find new key for target plaintext
    char target_plaintext[] = "cash not needed";
    int new_key[100];
    generateKeyForDecryption(ciphertext, target_plaintext, new_key, key_length);

    printf("New Key for Decryption: ");
    for (int i = 0; target_plaintext[i] != '\0'; i++) {
        if (isalpha(target_plaintext[i])) {
            printf("%d ", new_key[i]);
        }
    }
    printf("\n");

    return 0;
}
