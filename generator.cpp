#include <iostream>
#include <fstream>
#include <sstream>

struct int256
{
    uint16_t bits[16];
};

std::string getHashOfString(std::string input) {
    int256 hash;

    // base
    for (int i = 0; i < 16; i ++) {
        hash.bits[i] = 4096 + (i * input.length());
    }

    // read every symbol from input and modify the hash
    for(std::size_t i = 0; i < input.length(); i++)
    {
        hash.bits[0] = (hash.bits[0] * 7417 * input[i] + input[i]); // todo: different hashes for similar inputs
        for (int j = 1; j < 16; j ++) {
            hash.bits[j] = hash.bits[j] + hash.bits[j-1] + input[i];
        }
    }

    // append all hash values to one string
    std::ostringstream hashStream; 
    for (int j = 1; j < 16; j ++)
        hashStream << std::hex << hash.bits[j]; 
    std::string hashString = hashStream.str(); 
    return hashString;
}

std::string getHashOfFileOrString(std::string input) {
    std::string hash;

    std::ifstream in (input);
    if(in) {    // file exists
        std::string firstWord;          // todo: read all file
        in >> firstWord;
        hash = getHashOfString(firstWord);
        in.close();
    }
    else {      // treat input as a string
        hash = getHashOfString(input);
    }
    return hash;
}

int main (int argc, char* argv []) {
    if (argc == 1)
        std::cout << "No arguments passed\n"; // todo: immediate kill

    int i = 1;
    while (argc != 1) { // get hash codes of all passed arguments
        std::cout << argv[i] << ": " << getHashOfFileOrString(argv[i]) << "\n";
        i++;
        argc --;
    }

    std::cout << "End";
    return 0;
}