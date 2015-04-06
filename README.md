# parallel_lcm
Quick parallel LCM (Least Commom Multiple) calculator
##What is this?
This is just a very simple program to calculate the LCM of a given number of numbers. The calculation is done in several threads (as many as the CPU is capable of) in parallel.

##How does it work?
One way of finding the LCM is using the unique factorization theorem, which tells us that we should factor primes for each number to computer. Then find the highest ammount of ocurrence of those numbers, and compute accordingly (I will not explain all the math behind, really).

We should not forget that prime factorization is an NP-complete problem. Anyway, there are a number of ways to speed up the process of finding primes.

First of all, we will generate a small number of well known primes, and using wheel factorization, we generate a bigger set of primes. Once we receive a number, our first attempt will be to use these sets, which will hugely increase overall speed.

If the number is big, we will proceed an factorize it using the Pollard's rho algorithm. Not ideal, but overall it will give preatty good results.

##What do I need?
The code is written in C++11 style, so you will need a compiler that supports it. Also, you need thread support (well, that comes in every operating system, so not a big deal), and GMP library, which will be used for optimized arithmetic operations.

##How do I compile it?
A simple CMake file is supplied. You can just compile it as
>cmake .
>make

Alternatively, you can compile it like
><g++ or clang++>  -std=gnu++11 -Wall -Wextra -pedantic -pthread math.cpp parallel_lcm.cpp queue.cpp worker.cpp -o test -lgmp -lgmpxx
