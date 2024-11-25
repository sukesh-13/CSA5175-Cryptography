#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

void diffie_hellman(mpz_t shared_secret, mpz_t a, mpz_t x, mpz_t q) {
    mpz_powm(shared_secret, a, x, q);
}

int main() {
    mpz_t a, q, x_A, x_B, A, B, shared_secret_A, shared_secret_B;
    mpz_inits(a, q, x_A, x_B, A, B, shared_secret_A, shared_secret_B, NULL);

    // Public values
    mpz_set_str(a, "5", 10);
    mpz_set_str(q, "23", 10);

    // Private values
    mpz_set_str(x_A, "6", 10);
    mpz_set_str(x_B, "15", 10);

    // Alice and Bob compute their public values
    mpz_powm(A, a, x_A, q);
    mpz_powm(B, a, x_B, q);

    // Shared secret computation
    mpz_powm(shared_secret_A, B, x_A, q);
    mpz_powm(shared_secret_B, A, x_B, q);

    gmp_printf("Shared Secret (Alice): %Zd\n", shared_secret_A);
    gmp_printf("Shared Secret (Bob): %Zd\n", shared_secret_B);

    mpz_clears(a, q, x_A, x_B, A, B, shared_secret_A, shared_secret_B, NULL);
    return 0;
}
