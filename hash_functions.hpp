#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

struct int256
{
    uint16_t bits[16];
};

std::string getHashOfString(std::string input);
std::string getHashOfFileOrString(std::string input);