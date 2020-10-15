#include "hash_functions.hpp"

std::string getHashOfString(std::string input) {
    int256 hash;

    for (int i = 0; i < 16; i ++) {
        hash.bits[i] = 4096 + (i+1) * pow(2, input.length()%10) * 9719;
    }

    // read every symbol from input and modify the hash
    for(int i = 0; i < input.length(); i++)
    {
        hash.bits[0] = hash.bits[0] * 7213 + 1327 * pow(input[i]%10,3) + input[i];
        for (int j = 1; j < 16; j ++) {
            hash.bits[j] = hash.bits[j] * hash.bits[j-1] + input[i];
        }
    }
    
    // append all hash values to one string
    std::ostringstream hashStream; 
    for (int j = 0; j < 16; j ++) {
        char fill = '0' + hash.bits[j]%10; // get the last digit as char
        hashStream << std::setfill(fill) << std::setw(4) << std::hex << hash.bits[j]; 
    }
    std::string hashString = hashStream.str(); 
    return hashString;
}

std::string getHashOfFileOrString(std::string input) {
    std::string hash;

    std::ifstream in (input);
    if(in) {    // file exists
        if (in.peek() == std::ifstream::traits_type::eof()) {   // file's empty
            hash = getHashOfString("");
        } else {
            std::string line, newHash;
            std::getline(in, line);             // read a line
            hash = getHashOfString(line);       // get a hash of the line

            while (std::getline(in, line)) {
                newHash = getHashOfString(line);// read another line
                hash += newHash;                // add the former and the newer hashes together
                hash = getHashOfString(hash);   // get a new hash from summed up hashes
            }
        }
        in.close();
    }
    else {      // treat input as a string
        hash = getHashOfString(input);
    }
    return hash;
}