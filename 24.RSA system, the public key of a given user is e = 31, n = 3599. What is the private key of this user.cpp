#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to find the modular multiplicative inverse using the Extended Euclidean Algorithm
int modInverse(int e, int phi_n) {
    int t1 = 0, t2 = 1, r1 = phi_n, r2 = e;
    while (r2 > 0) {
        int quotient = r1 / r2;
        int t = t1 - quotient * t2;
        int r = r1 - quotient * r2;
        
        t1 = t2;
        t2 = t;
        r1 = r2;
        r2 = r;
    }
    if (r1 == 1) {
        if (t1 < 0) {
            t1 = t1 + phi_n;  // Make the result positive
        }
        return t1;
    } else {
        return -1;  // Inverse doesn't exist
    }
}

int main() {
    int n = 3599;
    int e = 31;

    // Step 1: Trial and error to find p and q such that n = p * q
    int p, q;
    for (p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Step 2: Compute f(n) = (p - 1) * (q - 1)
    int phi_n = (p - 1) * (q - 1);

    // Step 3: Find the modular inverse of e modulo f(n)
    int d = modInverse(e, phi_n);

    // Step 4: Output the results
    printf("Given n = %d, e = %d\n", n, e);
    printf("Found prime factors: p = %d, q = %d\n", p, q);
    printf("Euler's totient function f(n) = %d\n", phi_n);
    if (d != -1) {
        printf("The private key d is: %d\n", d);
    } else {
        printf("No modular inverse exists for e = %d mod f(n)\n", e);
    }

    return 0;
}
