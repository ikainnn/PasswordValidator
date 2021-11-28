#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#include "pswd/security.hpp"

// sketchy password validator i did for fun.

extern const std::size_t pswd::g_minLength = 6;
extern const std::size_t pswd::g_maxLength = 24;

int main() 
{
    std::string password;
    std::double_t passwordEntropy;

    do {
        std::cin >> password;
    } while(!(passwordEntropy = pswd::validate_password(password)));
    
    //clear console output(unix)
    std::cout << "\x1B[2J\x1B[H";

    std::cout << password << " has an entropy of [" << passwordEntropy << "]";
    std::cout << "\nwhich is considered: " << pswd::parse_entropy(passwordEntropy) << '\n';
}