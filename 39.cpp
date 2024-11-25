#include <stdio.h>
#include <string.h>

// English letter frequency (approximation)
float englishFrequencies[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15, 1.97, 0.07
};

// Function to perform letter frequency analysis
void letterFrequencyAnalysis(char *ciphertext, float *frequencies) {
    int length = strlen(ciphertext);
    int counts[26] = {0};

    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            counts[ciphertext[i] - 'A']++;
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            counts[ciphertext[i] - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        frequencies[i] = (float)counts[i] / length * 100;
    }
}

// Function to decrypt using a given shift
void decryptWithShift(char *ciphertext, int shift, char *plaintext) {
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = ((c - 'A' - shift + 26) % 26) + 'A';
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = ((c - 'a' - shift + 26) % 26) + 'a';
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[length] = '\0';
}

// Function to find the best shifts based on letter frequency
void findBestShifts(float *ciphertextFrequencies, int *bestShifts, int numShifts) {
    float minDifference;
    for (int i = 0; i < 26; i++) {
        bestShifts[i] = -1;
        minDifference = 1000.0;  // Initialize with a large value
        for (int j = 0; j < 26; j++) {
            float difference = 0;
            for (int k = 0; k < 26; k++) {
                difference += (englishFrequencies[(k + j) % 26] - ciphertextFrequencies[k]) *
                              (englishFrequencies[(k + j) % 26] - ciphertextFrequencies[k]);
            }
            if (difference < minDifference) {
                minDifference = difference;
                bestShifts[i] = j;
            }
        }
    }
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG"; // Example ciphertext
    char plaintext[100];
    float ciphertextFrequencies[26];
    int bestShifts[10];

    letterFrequencyAnalysis(ciphertext, ciphertextFrequencies);

    findBestShifts(ciphertextFrequencies, bestShifts, 10);

    printf("Top 10 possible plaintexts:\n");
    for (int i = 0; i < 10; i++) {
        decryptWithShift(ciphertext, bestShifts[i], plaintext);
        printf("Shift %d: %s\n", bestShifts[i], plaintext);
    }

    return 0;
}
