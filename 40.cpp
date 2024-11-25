#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Approximate frequency of letters in the English language
float englishFrequencies[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15, 1.97, 0.07
};

// Function to perform letter frequency analysis
void letterFrequencyAnalysis(char *text, float *frequencies) {
    int length = strlen(text);
    int counts[26] = {0};

    for (int i = 0; i < length; i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z') {
            counts[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            counts[c - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        frequencies[i] = (float)counts[i] / length * 100;
    }
}

// Function to find the best letter mappings based on frequency analysis
void findBestMappings(float *ciphertextFrequencies, char *mapping) {
    int used[26] = {0};

    for (int i = 0; i < 26; i++) {
        float minDifference = 1000.0;
        int bestMatch = -1;
        for (int j = 0; j < 26; j++) {
            if (!used[j]) {
                float difference = abs(englishFrequencies[j] - ciphertextFrequencies[i]);
                if (difference < minDifference) {
                    minDifference = difference;
                    bestMatch = j;
                }
            }
        }
        used[bestMatch] = 1;
        mapping[i] = 'A' + bestMatch;
    }
}

// Function to decrypt the ciphertext using the provided mapping
void decryptWithMapping(char *ciphertext, char *mapping, char *plaintext) {
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = mapping[c - 'A'];
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = mapping[c - 'a'];
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[length] = '\0';
}

// Function to sort plaintexts by likelihood based on frequency analysis
void sortPlaintexts(char plaintexts[][100], int *likelihoods, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (likelihoods[i] < likelihoods[j]) {
                int tempLikelihood = likelihoods[i];
                likelihoods[i] = likelihoods[j];
                likelihoods[j] = tempLikelihood;

                char temp[100];
                strcpy(temp, plaintexts[i]);
                strcpy(plaintexts[i], plaintexts[j]);
                strcpy(plaintexts[j], temp);
            }
        }
    }
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG"; // Example ciphertext
    char plaintext[100];
    float ciphertextFrequencies[26];
    char mapping[26];

    // Perform letter frequency analysis
    letterFrequencyAnalysis(ciphertext, ciphertextFrequencies);

    // Find the best letter mappings
    findBestMappings(ciphertextFrequencies, mapping);

    // Decrypt the ciphertext using the best mapping
    decryptWithMapping(ciphertext, mapping, plaintext);
    printf("Most likely plaintext: %s\n", plaintext);

    // Generate and sort multiple plaintexts
    char plaintexts[10][100];
    int likelihoods[10];
    for (int i = 0; i < 10; i++) {
        findBestMappings(ciphertextFrequencies, mapping);
        decryptWithMapping(ciphertext, mapping, plaintexts[i]);
        likelihoods[i] = 0; // You can refine this part to calculate likelihoods
    }

    sortPlaintexts(plaintexts, likelihoods, 10);

    printf("Top 10 possible plaintexts:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d: %s\n", i + 1, plaintexts[i]);
    }

    return 0;
}
