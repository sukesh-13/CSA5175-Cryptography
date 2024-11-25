#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
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

int main() {
    int p = 61; 
    int q = 53; 
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = 17; 
    int d = 0;
    for (int i = 1; i < phi; i++) {
        if ((e * i) % phi == 1) {
            d = i;
            break;
        }
    }

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    int message = 42; 
    int encrypted_message = mod_exp(message, e, n);
    int decrypted_message = mod_exp(encrypted_message, d, n);

    printf("Original Message: %d\n", message);
    printf("Encrypted Message: %d\n", encrypted_message);
    printf("Decrypted Message: %d\n", decrypted_message);

    return 0;
}
