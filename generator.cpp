#include <iostream>
#include <fstream>

std::string getHashOfString(std::string input) {
    std::string hash = input + 'a';     // todo: write valid hash generator
    return hash;
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
        std::cout << getHashOfFileOrString(argv[i]) << std::endl;
        i++;
        argc --;
    }

    std::cout << "End";
    return 0;
}