#include <random>
#include "hash_functions.hpp"
#include "timer.h"

// the lower the better
double match(std::string hash1, std::string hash2) {
    double matches = 0;

    for (int i = 0; i < hash1.length(); i ++)
        if (hash1[i] == hash2[i])
            matches++;

    return (matches / hash1.length() * 100);
}

void test_1(std::string file) {
    std::string hash_1 = getHashOfFileOrString(file);
    std::string hash_2 = getHashOfFileOrString(file);
    std::cout << file << " hash codes:\n" 
              << hash_1 << " Length: " << hash_1.length() << "\n" 
              << hash_2 << " Length: " << hash_2.length()
              << "\nMatch: " << match(hash_1, hash_2) << "%\n";
}

double test_2() {
    std::string line, hash;
    Timer T;
    double duration = 0;

    std::ifstream in ("konstitucija.txt");
    while (std::getline(in, line)) {
        T.set();
        hash = getHashOfString(line);
        duration += T.elapsed();
    }
    in.close();
    return duration;
}

void generatePairsFile() {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(97, 122);
    std::string s1, s2;
    int lengths[4] = {10, 100, 500, 1000};

    std::ofstream out ("3.txt");
    for (int l = 0; l < 4; l++) {
        for (int i = 0; i < 25000; i ++) {
            s1 = s2 = "";
            for (int j = 0; j < lengths[l]; j ++) {
                s1 += random10(mt);
                s2 += random10(mt);
            }
            out << s1 << " " << s2 << "\n";
        }
    }
    out.close();
}

int main() {
    
    std::cout << "Files with one symbol\n";
    test_1("1_1_1.txt");
    test_1("1_1_2.txt");

    std::cout << "____________________\n\nDifferent files with >1000 symbols\n";
    test_1("1_2_1.txt");
    test_1("1_2_2.txt");
    test_1("1_2_3.txt");
    test_1("1_2_4.txt");

    std::cout << "____________________\n\nSimilar files with >1000 symbols\n";
    test_1("1_3_1.txt");
    test_1("1_3_2.txt");
    
    std::cout << "____________________\n\nEmpty file\n";
    test_1("1_4.txt");

    std::cout << "Konstitucijos eiluciu hash'inimas uztruko: " << test_2();

    return 0;
}

// g++ -c tester.cpp hash_functions.cpp
// g++ -o t tester.o hash_functions.o