#include "rsa.hpp"

#include <iostream>

private_key::private_key(const mpz_class& p, const mpz_class& q)
        : p(p), q(q)
{
        e = mpz_class(2);
        mpz_t one;
        mpz_init(one);
        mpz_set_si(one, 1);
        mpz_t phi;
        mpz_init(phi);
        mpz_t p1;
        mpz_init(p1);
        mpz_t q1;
        mpz_init(q1);
        mpz_sub(p1, p.get_mpz_t(), one);
        mpz_sub(q1, q.get_mpz_t(), one);
        mpz_lcm(phi, p1, q1);
        mpz_t out;
        mpz_init(out);
        mpz_t ee;
        mpz_init(ee);
        mpz_set_si(ee, 2);
        while (mpz_cmp(ee, phi) < 0) {
                mpz_gcd(out, ee, phi);
                if (mpz_cmp(out, one) == 0)  {
                        break;
                }
                mpz_add(ee, ee, one);
        }
        e = mpz_class(ee);
        mpz_t dd;
        mpz_init(dd);
        mpz_invert(dd, ee, phi);
        d = mpz_class(dd);
        mpz_clear(out);
        mpz_clear(phi);
}

mpz_class RSA_engine::encrypt(const mpz_class& message, const public_key& key)
{
        mpz_t encrypted;
        mpz_init(encrypted);
        mpz_powm(encrypted, message.get_mpz_t(), key.e.get_mpz_t(), key.n.get_mpz_t());
        mpz_class out {encrypted};
        mpz_clear(encrypted);
        return out;
}

mpz_class RSA_engine::decrypt(const mpz_class& message, const private_key& key)
{
        mpz_t dencrypted;
        mpz_init(dencrypted);
        mpz_t n;
        mpz_init(n);
        mpz_mul(n, key.p.get_mpz_t(), key.q.get_mpz_t());
        mpz_powm(dencrypted, message.get_mpz_t(), key.d.get_mpz_t(), n);
        mpz_class out {dencrypted};
        mpz_clear(dencrypted);
        mpz_clear(n);
        return out;
}
