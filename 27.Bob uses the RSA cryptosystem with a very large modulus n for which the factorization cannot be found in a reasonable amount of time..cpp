#include <stdio.h>
#include <math.h>

int mod_exp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int rsa_encrypt_decrypt(int msg, int key, int n) {
    return mod_exp(msg, key, n);
}

int main() {
    int e = 17;   
    int d = 2753;     
    int n = 3233;    

    char message[] = "HELLO";
    int encrypted_message[sizeof(message)];
    int decrypted_message[sizeof(message)];

    printf("Original Message: %s\n", message);
    for (int i = 0; message[i] != '\0'; i++) {
        int char_as_int = message[i] - 'A';  
        encrypted_message[i] = rsa_encrypt_decrypt(char_as_int, e, n);
    }

    printf("Encrypted Message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        printf("%d ", encrypted_message[i]);
    }
    printf("\n");
    for (int i = 0; message[i] != '\0'; i++) {
        decrypted_message[i] = rsa_encrypt_decrypt(encrypted_message[i], d, n) + 'A';
    }

    printf("Decrypted Message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        printf("%c", decrypted_message[i]);
    }
    printf("\n");

    return 0;
}
