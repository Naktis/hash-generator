#include <random>
#include <bitset>
#include "hash_functions.hpp"
#include "timer.h"

// the lower the better
double matchHex(std::string hash1, std::string hash2) {
    double matches = 0;

    for (int i = 0; i < hash1.length(); i ++)
        if (hash1[i] == hash2[i])
            matches++;

    return (matches / hash1.length() * 100);
}

double matchBin(std::string hash1, std::string hash2) {
    double matches = 0;
    std::bitset<8> bitset1, bitset2;

    for (int i = 0; i < hash1.length(); i ++) {
        bitset1 = std::bitset<8>(hash1[i]);
        bitset2 = std::bitset<8>(hash2[i]);
        for (int bit = 0; bit < 8; bit ++)
            if (bitset1[bit] == bitset2[bit])
                matches++;
    }

    return (matches / (hash1.length() * 8) * 100);
}

void test_1(std::string file) {
    std::string hash_1 = getHashOfFileOrString(file);
    std::string hash_2 = getHashOfFileOrString(file);
    std::cout << file << " hash codes:\n" 
              << hash_1 << " Length: " << hash_1.length() << "\n" 
              << hash_2 << " Length: " << hash_2.length()
              << "\nDo hashes match?: ";
    hash_1 == hash_2 ? std::cout << "Yes\n" : std::cout << "No\n";
    std::cout << "Are lengths the same? ";
    hash_1.length() == hash_2.length() ? std::cout << "Yes\n" : std::cout << "No\n";
}

void test_2() {
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
    std::cout << "Konstitucijos eiluciu hash'inimas uztruko: " << duration << "\n";
}

void generateTest3File() {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> randomLetter(97, 122);
    std::string s1, s2;
    int lengths[4] = {10, 100, 500, 1000};

    std::ofstream out ("3.txt");
    for (int l = 0; l < 4; l++) {
        for (int i = 0; i < 25000; i ++) {
            s1 = s2 = "";
            for (int j = 0; j < lengths[l]; j ++) {
                s1 += randomLetter(mt);
                s2 += randomLetter(mt);
            }
            out << s1 << " " << s2 << "\n";
        }
    }
    out.close();
}

void test_3() {
    std::string s1, s2;
    int collisions = 0;
    std::ifstream in ("3.txt");
    while (in >> s1) {
        in >> s2;
        if (getHashOfString(s1) == getHashOfString(s2))
            collisions ++;
    }
    in.close();
    std::cout << "Poru koliziju suma: " << collisions << "\n";
}

void generateTest4File() {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> randomLetter(97, 122);
    std::string s1, s2;
    int lengths[4] = {10, 100, 500, 1000};
    int position;

    std::ofstream out ("4.txt");
    for (int l = 0; l < 4; l++) {
        std::uniform_int_distribution<int> randomPosition(0, lengths[l]-1);
        position = randomPosition(mt);
        for (int i = 0; i < 25000; i ++) {
            s1 = "";
            for (int j = 0; j < lengths[l]; j ++) {
                s1 += randomLetter(mt);
            }
            s2 = s1;
            s2[position] = randomLetter(mt);
            out << s1 << " " << s2 << "\n";
        }
    }
    out.close();
}

void setMinMax(double& min, double& max, double value) {
    if (value > max)
        max = value;

    if (value < min)
        min = value;
}

void test_4() {
    std::string s1, s2, hash1, hash2;
    double maxMatchHex = 0, maxMatchBin = 0;
    double minMatchHex = 100, minMatchBin = 100;
    double tempMatchHex, tempMatchBin;
    double sumMatchHex = 0, sumMatchBin = 0;
    int pairCount = 0;

    std::ifstream in ("4.txt");
    while (in >> s1) {
        in >> s2;

        tempMatchHex = matchHex(getHashOfString(s1), getHashOfString(s2));
        tempMatchBin = matchBin(getHashOfString(s1), getHashOfString(s2));

        setMinMax(minMatchHex, maxMatchHex, tempMatchHex);
        setMinMax(minMatchBin, maxMatchBin, tempMatchBin);

        sumMatchHex += tempMatchHex;
        sumMatchBin += tempMatchBin;
        pairCount ++;
    }
    in.close();

    double avgMatchHex = sumMatchHex / pairCount;
    double avgMatchBin = sumMatchBin / pairCount;

    std::cout << "\t| Min\t| Max\t| Avg\n"
              << "Hex\t| " << std::fixed << std::setprecision(1) << minMatchHex << "\t| " << maxMatchHex << "\t| " << avgMatchHex
              << "\nBin\t| " << minMatchBin << "\t| " << maxMatchBin << "\t| " << avgMatchBin << "\n";
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
    
    test_2();
    test_3();
    test_4();

    return 0;
}

// g++ -c tester.cpp hash_functions.cpp
// g++ -o t tester.o hash_functions.o