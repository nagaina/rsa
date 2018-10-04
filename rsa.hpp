#ifndef RSA_HPP
#define RSA_HPP

#include <gmpxx.h>

struct private_key
{
        private_key(const mpz_class& p, const mpz_class& q);

        mpz_class p;
        mpz_class q;
        mpz_class d;
        // move from here
        mpz_class n;
        mpz_class e;
};

struct public_key
{
        public_key(const mpz_class& n, const mpz_class e) :
                n(n), e(e) {}

        mpz_class n;
        mpz_class e;
};

class RSA_engine
{
public:

        mpz_class encrypt(const mpz_class& message, const public_key& key);

        mpz_class decrypt(const mpz_class& message, const private_key& key);
};

#endif
