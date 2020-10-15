#include "hash_functions.hpp"

int main (int argc, char* argv []) {
    if (argc == 1)
        std::cout << "No arguments passed\n";

    int i = 1;
    while (argc != 1) { // get hash codes of all passed arguments
        std::cout << argv[i] << ": " << getHashOfFileOrString(argv[i]) << "\n";
        i++;
        argc --;
    }

    std::cout << "End";
    return 0;
}

// g++ -c generator.cpp hash_functions.cpp
// g++ -o g generator.o hash_functions.o