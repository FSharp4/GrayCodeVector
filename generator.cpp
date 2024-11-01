//
// Created by jakep on 11/1/2024.
//
#include <iostream>
#include <ranges>
#include <vector>
#include "generator.h"

#include <numeric>

#define FALLBACK_N_ARGS 5

/**
 * Checks a bit for a number to see if it is set.
 * @param number Number to check bit of
 * @param bit Bit index to check (small bit = small number)
 * @return True if bit is set, false if not
 */
bool isBitSet(const int number, const int bit) {
    return (number & (1 << bit)) != 0;
}

int main(const int argc, char* argv[]) {
    // Parse the length of required gray code
    long nVar = FALLBACK_N_ARGS;
    if (argc > 1) {
        nVar = std::stoi(argv[1]);
    }

    // -- Print vector file header --
    // Define radix (all ones)
    std::cout << "radix";
    for (int i = 0; i < nVar; i++) {
        // There are certainly smarter ways to do this. But, this is readable.
        std::cout << " 1";
    }
    std::cout << std::endl;

    // Define io (all ones)
    std::cout << "io";
    for (int i = 0; i < nVar; i++) {
        std::cout << " i";
    }
    std::cout << std::endl;

    // Define vnames (very generic)
    std::cout << "vname";
    char c = 'A';
    for (int i = 0; i < nVar; i++) {
        std::cout << " " << c;
        c++;
    }
    std::cout << std::endl;

    std::cout << "tunit ns" << std::endl;
    std::cout << "trise 0.01" << std::endl;
    std::cout << "tfall 0.01" << std::endl;
    std::cout << "vih 1.0" << std::endl;
    std::cout << "vil 0.0" << std::endl;

    // -- Calculate the vector --
    // Figure out size & declare
    const int vecLen = (1 << nVar) + 1;
    std::vector<int> vec(vecLen);
    std::vector<std::vector<bool>> codes(vecLen, std::vector<bool>(nVar, false));
    std::iota(vec.begin(), vec.end(), 0); // 0...(2<<nVar)+1
    // codes start at all false (0s)

    // Run iteration (it actually starts at j = 1. The first iteration is known correct)
    for (int i = 0; i < vecLen - 1; i++) {
        const int j = i + 1;
        for (int b = 0; b < nVar; b++) {
            // If this bit is 0 and the next bit is 1, we flip the next corresponding code bit.
            if (!isBitSet(vec[i], b) && isBitSet(vec[j], b)) {
                codes[j][b] = !codes[i][b];
            } else { // otherwise the bit is propagated
                codes[j][b] = codes[i][b];
            }
        }

        std::cout << vec[i];
        for (int b = nVar - 1; b >= 0; b--) {
            std::cout << " " << codes[i][b];
        }
        std::cout << std::endl;
    }

    // Small off-by-one handler: the last code needs to have its most significant bit set to 0.
    codes[vecLen - 1][nVar - 1] = false;
    // Then we can print it
    std::cout << vecLen;
    for (int b = 0; b < nVar; b++) {
        std::cout << " " << codes[vecLen - 1][b];
    }
    return 0;
}