#include <stdio.h>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void affineEncrypt(char* plaintext, int a, int b, char* ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char p = plaintext[i];
        if (p >= 'A' && p <= 'Z') {
            ciphertext[i] = ((a * (p - 'A') + b) % 26) + 'A';
        } else if (p >= 'a' && p <= 'z') {
            ciphertext[i] = ((a * (p - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = p;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void affineDecrypt(char* ciphertext, int a, int b, char* plaintext) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Multiplicative inverse of %d does not exist under modulo 26.\n", a);
        return;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = (a_inv * ((c - 'A' - b + 26) % 26) % 26) + 'A';
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = (a_inv * ((c - 'a' - b + 26) % 26) % 26) + 'a';
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[] = "HELLO";
    char ciphertext[100];
    char decrypted[100];
    int a = 5; // 'a' must be coprime with 26
    int b = 8;

    affineEncrypt(plaintext, a, b, ciphertext);
    printf("Encrypted: %s\n", ciphertext);

    affineDecrypt(ciphertext, a, b, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
