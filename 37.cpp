#include <stdio.h>
#include <string.h>

// English letter frequency (approximation)
float englishFrequencies[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15, 1.97, 0.07
};

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

void letterFrequencyAttack(char *ciphertext, char *plaintext) {
    float frequencies[26];
    letterFrequencyAnalysis(ciphertext, frequencies);

    char mapping[26];
    int used[26] = {0};
    for (int i = 0; i < 26; i++) {
        int maxIndex = -1;
        float maxFrequency = -1.0;
        for (int j = 0; j < 26; j++) {
            if (frequencies[j] > maxFrequency && !used[j]) {
                maxFrequency = frequencies[j];
                maxIndex = j;
            }
        }
        used[maxIndex] = 1;
        mapping[maxIndex] = 'A' + i;
    }

    for (int i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = mapping[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = mapping[ciphertext[i] - 'a'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG"; // Example ciphertext
    char plaintext[100];

    letterFrequencyAttack(ciphertext, plaintext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
