#include <stdio.h>
#include <stdint.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

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
            t1 = t1 + phi_n; 
        }
        return t1;
    } else {
        return -1;
    }
}

int main() {
    int n = 3599;  
    int e = 31;   
    int M = 59;   

    int gcd_value = gcd(M, n);
    
    if (gcd_value > 1) {
        printf("Common factor found: %d\n", gcd_value);

        int p = gcd_value;
        int q = n / p;

        int phi_n = (p - 1) * (q - 1);

        int d = modInverse(e, phi_n);

        printf("Private key d is: %d\n", d);
    } else {
        printf("No common factor found.\n");
    }

    return 0;
}
