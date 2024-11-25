#include <stdio.h>
#include <stdint.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

void generate_keys(mpz_t p, mpz_t q, mpz_t g, mpz_t x, mpz_t y) {
    // DSA Key generation
    // Example primes and generator
    mpz_set_str(p, "23", 10);  // Example prime p
    mpz_set_str(q, "11", 10);  // Example prime q
    mpz_set_str(g, "2", 10);   // Example generator g

    // Select private key x
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_urandomm(x, state, q); // Generate random x < q

    // Compute public key y
    mpz_powm(y, g, x, p);

    gmp_randclear(state);
}

void sign_message(mpz_t r, mpz_t s, const mpz_t message, const mpz_t p, const mpz_t q, const mpz_t g, const mpz_t x) {
    mpz_t k, k_inv, h, xr;
    mpz_inits(k, k_inv, h, xr, NULL);

    // Generate random k < q
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    mpz_urandomm(k, state, q);

    // Compute r = (g^k mod p) mod q
    mpz_powm(r, g, k, p);
    mpz_mod(r, r, q);

    // Compute k^-1 mod q
    mpz_invert(k_inv, k, q);

    // Compute s = k^-1 * (H(m) + xr) mod q
    mpz_mul(xr, x, r);
    mpz_add(h, message, xr);
    mpz_mul(s, k_inv, h);
    mpz_mod(s, s, q);

    gmp_randclear(state);
    mpz_clears(k, k_inv, h, xr, NULL);
}

int verify_signature(const mpz_t r, const mpz_t s, const mpz_t message, const mpz_t p, const mpz_t q, const mpz_t g, const mpz_t y) {
    mpz_t w, u1, u2, v, gu1, yu2;
    mpz_inits(w, u1, u2, v, gu1, yu2, NULL);

    // Compute w = s^-1 mod q
    mpz_invert(w, s, q);

    // Compute u1 = (H(m) * w) mod q
    mpz_mul(u1, message, w);
    mpz_mod(u1, u1, q);

    // Compute u2 = (r * w) mod q
    mpz_mul(u2, r, w);
    mpz_mod(u2, u2, q);

    // Compute v = ((g^u1 * y^u2) mod p) mod q
    mpz_powm(gu1, g, u1, p);
    mpz_powm(yu2, y, u2, p);
    mpz_mul(v, gu1, yu2);
    mpz_mod(v, v, p);
    mpz_mod(v, v, q);

    int result = (mpz_cmp(v, r) == 0);

    mpz_clears(w, u1, u2, v, gu1, yu2, NULL);
    return result;
}

int main() {
    mpz_t p, q, g, x, y;
    mpz_inits(p, q, g, x, y, NULL);

    generate_keys(p, q, g, x, y);

    mpz_t message, r, s;
    mpz_inits(message, r, s, NULL);
    mpz_set_str(message, "19", 10); // Example message hash

    sign_message(r, s, message, p, q, g, x);

    gmp_printf("Signature (r, s): (%Zd, %Zd)\n", r, s);

    int valid = verify_signature(r, s, message, p, q, g, y);
    printf("Signature is %s\n", valid ? "valid" : "invalid");

    mpz_clears(p, q, g, x, y, message, r, s, NULL);
    return 0;
}
