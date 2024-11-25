#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int matrix[2][2] = {{3, 3}, {2, 5}}; // Key matrix (2x2)

void hillEncrypt(char *plaintext, char *ciphertext) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i += 2) {
        ciphertext[i] = ((matrix[0][0] * (plaintext[i] - 'A') + matrix[0][1] * (plaintext[i + 1] - 'A')) % 26) + 'A';
        ciphertext[i + 1] = ((matrix[1][0] * (plaintext[i] - 'A') + matrix[1][1] * (plaintext[i + 1] - 'A')) % 26) + 'A';
    }
    ciphertext[length] = '\0';
}

void hillDecrypt(char *ciphertext, char *plaintext) {
    int length = strlen(ciphertext);
    int determinant = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    if (determinant < 0) determinant += 26;
    int determinant_inv = -1;
    for (int i = 0; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            determinant_inv = i;
            break;
        }
    }
    if (determinant_inv == -1) {
        printf("Determinant inverse does not exist.\n");
        return;
    }

    int inverse_matrix[2][2] = {
        {(matrix[1][1] * determinant_inv) % 26, (-matrix[0][1] * determinant_inv + 26) % 26},
        {(-matrix[1][0] * determinant_inv + 26) % 26, (matrix[0][0] * determinant_inv) % 26}
    };

    for (int i = 0; i < length; i += 2) {
        plaintext[i] = ((inverse_matrix[0][0] * (ciphertext[i] - 'A') + inverse_matrix[0][1] * (ciphertext[i + 1] - 'A')) % 26) + 'A';
        plaintext[i + 1] = ((inverse_matrix[1][0] * (ciphertext[i] - 'A') + inverse_matrix[1][1] * (ciphertext[i + 1] - 'A')) % 26) + 'A';
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[] = "HI";
    char ciphertext[100];
    char decrypted[100];

    hillEncrypt(plaintext, ciphertext);
    printf("Encrypted: %s\n", ciphertext);

    hillDecrypt(ciphertext, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
