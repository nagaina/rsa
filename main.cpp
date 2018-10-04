#include "rsa.hpp"

#include <iostream>

int main()
{
        int p, q, n; //check prime numbers
        std::cout << "input p-> ";
        std::cin >> p;
        std::cout << "input q-> ";
        std::cin >> q;
        // add checking -> if user inputs e and d, are they multiplicative inverse.
        private_key priv_key {p, q};
        n = p * q;
        public_key pub_key {n, priv_key.e};

        RSA_engine engine;
        int m;
        std::cout << "input message-> ";
        std::cin >> m;
        mpz_class message {m};
        std::cout << std::endl;
        mpz_class encrypted = engine.encrypt(message, pub_key);
        std::cout << "encrypted-> "<< encrypted << std::endl;
        mpz_class decrypted = engine.decrypt(encrypted, priv_key);
        std::cout << "decrypted-> "<< decrypted << std::endl;
}
