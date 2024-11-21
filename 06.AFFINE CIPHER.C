#include <stdio.h>
#define ALPHABET_SIZE 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}
int main() {
    char mostFrequentCiphertext = 'B'; 
    char secondMostFrequentCiphertext = 'U'; 
    char assumedMostFrequentPlaintext = 'E';
    char assumedSecondMostFrequentPlaintext = 'T';
    int C1 = mostFrequentCiphertext - 'A'; // C1 = 1
    int C2 = secondMostFrequentCiphertext - 'A'; // C2 = 20
    int P1 = assumedMostFrequentPlaintext - 'A'; // P1 = 4
    int P2 = assumedSecondMostFrequentPlaintext - 'A'; // P2 = 19
    for (int a = 1; a < ALPHABET_SIZE; a++) {
        if (modInverse(a, ALPHABET_SIZE) != -1) { 
            int b = (C1 - (a * P1) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
            if ((C2 - (a * P2) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE == b) {
                printf("Possible keys found:\n");
                printf("a = %d, b = %d\n", a, b);
            }
        }
    }
    return 0;
}
