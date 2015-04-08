#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <deque>
#include <time.h>

class primes {
public:
  primes();
  ~primes(){
    gmp_randclear (m_r_state);
  };

  std::vector <uint64_t> factor_primes (uint64_t number);

private:
  void init();

  mpz_class fnuc(const mpz_class &y, const mpz_class &c, const mpz_class &mod);
  void gcd(mpz_class &x, mpz_class &y, mpz_class &z);
  bool isPrime(mpz_class &x);
  void random(mpz_class &x, mpz_class &n);
  mpz_class &min(mpz_class &x, mpz_class &y);
  void abs1(mpz_class &ret, mpz_class &x);
  mpz_class pollard_rho(mpz_class &n);
  mpz_class bigPrimeFactorer(mpz_class &n);
  void sieveOfEratosthenes();
  void logq(mpz_class log, const mpz_class q, const mpz_class n);
  mpz_class pollard_p1(mpz_class &n);
  mpz_class pollard_brent(mpz_class &n);
  bool smallPrimeFactorer(mpz_class &n, std::vector<mpz_class> &factors);
  void factor(mpz_class &n, std::vector<mpz_class> &factors);


  std::vector<mpz_class> m_smallPrimes;
  std::vector<mpz_class> m_primes;
  int m_primetest;
  unsigned int m_numBrents;
  gmp_randstate_t m_r_state;
  int m_pollardLimit;
  int m_seed;
  // mpz_class m_ONE;
};
#endif // MATH_H