// Homework1RSA.cpp : RSA Implementation
// 

/*
CS 7081 Advanced Algorithms I
Homework Assignment 1

Group 13:
Philip Tallo
Christopher Ochs
Solomon Lazarus

Due : February 6, 2018
*/

#include <iostream>
#include <string>
#include <time.h>

const int MONTE_CARLO_REPS = 8; // number of repetitions for the Miller-Rabin primality test

unsigned long long int stringToInt(std::string inputStr) {
    // Converts a string from BEARCATII to a single integer
    // Raises an error if the string is not in BEARCATII

    unsigned long long int D = 0; // decimal representation of the input
    int ch; // holds the currently read character
    unsigned long long int pow27 = 1; // store powers of 27, starting with 27^0 = 1

    // loop through all characters from right to left
    for (int i = inputStr.length() - 1; i >= 0; i--) {

        // Read current character and convert to BEARCATII
        ch = inputStr.at(i);

        if (ch == 32) { //space
            ch = 0;
        } else if (ch >= 97 && ch <= 122) { // a to z
            ch = ch - 96;
        } else {
            std::cout << "Error: string contains a non-BEARCATII character. Use only lowercase letters and spaces.\n";
            return -1;
        }

        // Incorporate this character into D
        D += (ch * pow27);

        // Update pow27
        pow27 = pow27 * 27;
    }

    return D;
}

std::string intToString(unsigned long long int D) {
    // Converts an integer to the BEARCATII string it represents

    int intVal;
    char ch = ' ';
    std::string result = "";

    while (D > 0) {
        // Get current character int value and update D
        intVal = D % 27;
        D = D / 27;

        // Convert the character int value to a character and prepend it to the front of the result
        if (intVal == 0) {
            ch = ' ';
        } else if (intVal >= 1 && intVal <= 26) {
            ch = intVal + 96;
        }
        result = ch + result;
    }

    return result;
}

unsigned long long int gcd(unsigned long long int a, unsigned long long int b) {
    // Returns the GCD of a and b, using the Euclidean algorithm

    unsigned long long int remainder;

    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

void extendedEuclidGCD(unsigned long long int a, unsigned long long int b, unsigned long long int &g, int &s, int &t) {
    // Given a and b, will output (by reference) g = gcd(a,b), and integers s and t such that sa+tb=g
    int stemp, remainder, quotient;

    if (b == 0) {
        g = a;
        s = 1;
        t = 0;
    } else {
        remainder = a % b;
        quotient = a / b;
        extendedEuclidGCD(b, remainder, g, s, t);
        stemp = s;
        s = t;
        t = stemp - (t * quotient);
    }
}

unsigned long long int multiplicativeInverse(unsigned long long int x, unsigned long long int n) {
    // Computes the modulo n multiplicative inverse of x
    // This result is the s value returned by extendedEuclidGCD, such that sx + tn = gcd(x, n) = 1
    // However, s can be negative. If this is the case, add n to the value of s for the correct
    // result in the modular finite field arithmetic.

    unsigned long long int g = 0;
    int s = 0, t = 0;
    extendedEuclidGCD(x, n, g, s, t);

    if (s < 0)
        return n + s;
    else
        return s;
}

unsigned long long int modPowers(unsigned long long int x, unsigned long long int m, unsigned long long int n) {
    // Computes (x ^ m) mod n
    if (m == 0) {
        return 1;
    } else if (m == 1) {
        return x;
    } else if (m % 2 == 0) { // if m is even
        return modPowers((x * x) % n, m / 2, n) % n;
    } else { // m is odd
        return x * modPowers((x * x) % n, (m - 1) / 2, n) % n;
    }
}

bool millerRabinPrimalityTest(int n) {
    // Implementation of the Miller-Rabin primality test.

    // Hard-coded results for n < 5
    if (n == 0 || n == 1 || n == 4) return false;
    if (n == 2 || n == 3) return true;

    // Generate a random value for a on interval 2 to n-2
    int a = rand() % (n - 3); // a is a random number between 0 and n-4
    a = a + 2; // now a is a random number between 2 and n-2

    // Find positive integers k,m such that n-1 = (2^k)*m and m is odd
    int k = 0;
    int m = n - 1;
    while (m % 2 == 0) {
        k++;
        m = m / 2;
    }

    // Initialize b = (a^m) mod n
    unsigned long long int b = modPowers(a, m, n);

    // Loop to update b and see if a result can be returned
    for (int j = 1; j <= k; j++) {
        if (b != 1 && b != n - 1)
            return false;
        else if (b == n - 1)
            return true;
        b = b * b % n;
    }

    // Return a result
    if (b != 1)
        return false;
    else
        return true;
}

bool isPrime(int n) {
    // Runs the Miller-Rabin primality test multiple times.
    // If this returns false, then x is composite
    // If this returns true, then there is a high probability that n is prime

    for (int i = 0; i <= MONTE_CARLO_REPS; i++) {
        if (millerRabinPrimalityTest(n) == false) {
            return false;
        }
    }
    return true;
}

int generatePrime() {
    // Generates a random prime number
    int n;

    do {
        n = rand();
    } while (!isPrime(n));

    return n;
}

unsigned long long int readInt() {
    // Reads an integer value from the user
    unsigned long long int x;
    std::cin >> x;

    while (std::cin.fail()) {
        std::cout << "Error: Not a positive integer, please reinput.\n";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }

    return x;
}

int main() {
    // Seed the RNG
    srand(time(NULL));

    std::cout << millerRabinPrimalityTest(15487469) << std::endl;

    // Read the input message from the user
    std::string M;

    std::cout << "Enter your input message: \n";
    std::getline(std::cin, M);

    if (M.length() < 1) {
        std::cout << "Error: message length is 0.\n";
        return -1;
    } else if (M.length() > 4) {
        std::cout << "Error: maximum message length is 4.\n";
        return -1;
    }

    // Get integer representation of the string
    unsigned long long int D = stringToInt(M);
    if (D == -1) {
        // quit if there was an error
        return -1;
    }

    // Generate random primes p and q, and compute n = p * q and totient_n = (p-1)*(q-1)
    // Ensure that 14,348,906 < n < 4,294,967,297
    unsigned long long int p, q, n, totient_n;
    n = 0;
    while (n <= 14348906 || n >= 4294967297) {
        p = generatePrime();
        q = generatePrime();
        n = p * q;
        totient_n = (p - 1) * (q - 1);
    }

    // Prompt the user for a public key, e, until the user picks one that is coprime with totient_n
    std::cout << "Choose a public key, a positive integer that is coprime with " << totient_n << ": \n";
    unsigned long long int e = readInt();
    while (gcd(e, totient_n) != 1) {
        std::cout << "Values are not coprime, choose another positive integer for the public key:\n";
        e = readInt();
    }

    // Generate the private key, d
    // This is the multiplicative inverse of e modulo totient_n
    unsigned long long int d = multiplicativeInverse(e, totient_n);

    // Generate ciphertext integer C = (D ^ e) mod n
    unsigned long long int C = modPowers(D, e, n);

    // Generate plaintext integer P = (C ^ d) mod n
    unsigned long long int P = modPowers(C, d, n);

    // Output the results
    std::cout << "\np: " << p << "\n";
    std::cout << "q: " << q << "\n";
    std::cout << "n: " << n << "\n";
    std::cout << "M (string representation): " << M << "\n";
    std::cout << "M (integer representation): " << D << "\n";
    std::cout << "C (string representation): " << intToString(C) << "\n";
    std::cout << "C (integer representation): " << C << "\n";
    std::cout << "P (string representation): " << intToString(P) << "\n";
    std::cout << "P (integer representation): " << P << "\n";

    return 0;
}


